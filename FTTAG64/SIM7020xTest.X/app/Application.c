#include "libcomp.h"
#include "Application.h"

#define HOST_IP_DEFAULT             "45.79.112.203"
#define HOST_PORT_DEFAULT           "4242"
#define NETWORK_APN_DEFAULT         "v-internet"
#define SECTION_INTERVAL_DEFAULT    1 // ms
#define APP_DELAY_DEFAULT           1 // s
#define APP_COUNT_DEFAULT           10

#define Next_Task()             do{AppCxt.ToDo=AppCxt.Backup=AppCxt.DoNext; AppCxt.DoNext++; \
                                AppCxt.Flag=0;TryCount=0;}while(0)

#define New_Task(now)           do{AppCxt.ToDo=AppCxt.Backup=AppCxt.DoNext; AppCxt.DoNext=now;\
                                AppCxt.Flag=0;TryCount=0;}while(0)

#define Wait_Task(wait, donext) do{AppCxt.Backup=AppCxt.DoNext; AppCxt.DoNext=APP_IDLE; \
                                AppCxt.ToDo=donext; AppCxt.Wait=wait; AppCxt.Flag=0; \
                                Tick_Timer_Reset(AppCxt.Tick);}while(0)

typedef enum
{
    APP_IDLE=1,
    APP_ECHO_OFF,
    APP_ERR_REPORT,
    APP_NO_FLOW_CTRL,
    APP_GET_MODULE_NAME,
    APP_GET_IMEI,
    APP_GET_CIMI,
    APP_GET_CCID,
    APP_CHECK_NETWORK,
    APP_ALT_CHECK_NETWORK,
    APP_DEACTIVE_PDP,
    APP_SET_APN,
    APP_ACTIVE_PDP,
    APP_READ_PDP,
    APP_GET_RTCC,
    APP_CREATE_SOCKET,
    APP_OPEN_SOCKET,
    APP_SEND_DATA,
    APP_CLOSE_SECTION,
    APP_CLOSE_SOCKET,
    APP_REBOOT
} apptask_t;

static struct
{
    apptask_t DoNext;
    apptask_t ToDo;
    apptask_t Backup;
    tick_timer_t Tick;
    uint32_t Wait;
    bool Flag;
} AppCxt;

private uint8_t Buff1[512]; // Tx buffer
private uint8_t Buff2[64]; // Rx buffer

static struct tm SysRtc={
    .tm_wday=2, // Tuesday
    .tm_mday=1, // 1st
    .tm_mon=1, // Jan
    .tm_year=80, // 1980
    .tm_hour=0,
    .tm_min=0,
    .tm_sec=0,
};

private buff_t TxBuff;
private buff_t RxBuff;
private uint32_t AppCount=0;
private uint8_t AppSerial[24];
private uint8_t AppCcid[24];
private uint8_t AppCimi[24];
private uint8_t AppModuleName[24];
private uint8_t AppIp[40];

typedef struct
{
    uint8_t BkArr[64];
    uint8_t Ip[64];
    uint8_t Port[8];
    uint8_t Apn[16];
    uint32_t BkVal;
    uint32_t MsgDelay; // ms
    uint32_t AppDelay; // sec
    uint32_t AppCount;
    uint32_t Crc32;
} __attribute_packed__ cfg_t;

static const uint8_t __attribute((space(prog), aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS))) UserConfig[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS];

static const cfg_t DefaultConfig={
    .Ip=HOST_IP_DEFAULT,
    .Port=HOST_PORT_DEFAULT,
    .Apn=NETWORK_APN_DEFAULT,
    .MsgDelay=SECTION_INTERVAL_DEFAULT,
    .AppDelay=APP_DELAY_DEFAULT,
    .AppCount=APP_COUNT_DEFAULT
};

static const char HwInfo[]={
    "\n\nHWP070 REV2.0"
    "\nBuild: " __TIME__ "-" __DATE__ "\n"
};

static const uint8_t Help[]={
    "\nAT command protocol:     AT+<CMD>=<Parameters><\\r>"
    "\nSet host IP:             AT+IP=<IP or domain>"
    "\nSet host port:           AT+PORT=<Port>"
    "\nSet APN:                 AT+APN=<APN string>"
    "\nSet message delay (ms):  AT+MSGDELAY=<time>"
    "\nSet app delay (sec):     AT+APPDELAY=<time>"
    "\nSet app reset count:     AT+APPCOUNT=<time>"
    "\nSave config & reboot:    AT&W"
    "\nLoad default config:     AT&F"
    "\nDisplay current config:  AT&V"
    "\nDisplay helper:          AT\n"
};

static void ConfigDisplay(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="Config display">
{
    __dbss("\nHost:               ", pConfig->Ip);
    __dbss("\nPort:               ", pConfig->Port);
    __dbss("\nAPN:                ", pConfig->Apn);
    __dbsi("\nMessage delay (ms): ", pConfig->MsgDelay);
    __dbsi("\nApp delay (sec):    ", pConfig->AppDelay);
    __dbsi("\nApp reset count:    ", pConfig->AppCount);
    __dbsh("\nCRC32:              ", pConfig->Crc32);
} // </editor-fold>

static void RestCodeDisplay(void) // <editor-fold defaultstate="collapsed" desc="Reset code display">
{
    __dbsh("\nReset control register: ", RCON);

    if(RCONbits.PORIO)
        __dbs("\n-->PORIO: A Power-on Reset has occurred due to VDD voltage");

    if(RCONbits.PORCORE)
        __dbs("\n-->PORCORE: A Power-on Reset has occurred due to core voltage");

    if(RCONbits.BCFGERR)
        __dbs("\n-->BCFGERR: An error occurred during a read of the Primary Configuration registers");

    if(RCONbits.BCFGFAIL)
        __dbs("\n-->BCFGFAIL: An error occurred during a read of the Primary and Alternate Configuration registers");

    if(RCONbits.CMR)
        __dbs("\n-->CMR: Configuration Mismatch Reset has occurred");

    if(RCONbits.EXTR)
        __dbs("\n-->EXTR:  Master Clear (pin) Reset has occurred");

    if(RCONbits.SWR)
        __dbs("\n-->SWR: Software Reset was executed");

    if(RCONbits.WDTO)
        __dbs("\n-->WDTO: Watchdog Timer Time-out Flag bit");

    if(RCONbits.SLEEP)
        __dbs("\n-->SLEEP: Device was in Sleep mode");

    if(RCONbits.IDLE)
        __dbs("\n-->IDLE: Device was in Idle mode");

    if(RCONbits.BOR)
        __dbs("\n-->BOR: Brown-out Reset has occurred");

    if(RCONbits.POR)
        __dbs("\n-->POR: Power-on Reset has occurred");

    RCON&=0xFFFFFF20; // Clear bit 7,6,4,3,2,1,0
} // </editor-fold>

static int8_t CellTasks(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="MQTT Application">
{
    static uint8_t TryCount=0;
    static uint32_t Start, Stop;
    int8_t rslt;

    switch(AppCxt.DoNext)
    {
        case APP_IDLE: // <editor-fold defaultstate="collapsed" desc="Idle state">
            if(Tick_Timer_Is_Over_Ms(AppCxt.Tick, AppCxt.Wait))
            {
                if(AppCxt.ToDo==APP_IDLE)
                    return APP_IDLE;
                else
                {
                    AppCxt.Backup=AppCxt.DoNext;
                    AppCxt.DoNext=AppCxt.ToDo;
                    AppCxt.Flag=0;
                }
            } // </editor-fold>
            break;

        case APP_ECHO_OFF: // <editor-fold defaultstate="collapsed" desc="Echo off">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbsi("\nEcho off: ", TryCount);
            }

            rslt=ATCMD_SendGetAck("ATE0\r", "\r\nOK\r\n", 500, 250);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                if(++TryCount>=40)
                {
                    New_Task(APP_REBOOT);
                    __dbs("\nEcho off error");
                }
                else
                    Wait_Task(250, APP_ECHO_OFF);
            } // </editor-fold>
            break;

        case APP_ERR_REPORT: // <editor-fold defaultstate="collapsed" desc="Enable error report">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbs("\nEnable error report");
            }

            rslt=ATCMD_SendGetAck("AT+CMEE=2\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nEnable error report error");
            } // </editor-fold>
            break;

        case APP_NO_FLOW_CTRL: // <editor-fold defaultstate="collapsed" desc="No flow control">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbs("\nSet no HW flow control");
            }

            rslt=ATCMD_SendGetAck("AT&K0\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nSet no HW flow control error");
            } // </editor-fold>
            break;

        case APP_GET_MODULE_NAME: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nProduct");
            }

            rslt=ATCMD_SendGetAck("AT+CGMM\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
            {
                //\r\nME310G1-WW\r\n\r\nOK\r\n
                str_sub_between(AppModuleName, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbss(": ", AppModuleName);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_GET_IMEI: // <editor-fold defaultstate="collapsed" desc="Request product serial number identification">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nSerial");
            }

            rslt=ATCMD_SendGetAck("AT+CGSN\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
            {
                //\r\n\r\n359206100023282\r\n\r\nOK\r\n
                str_sub_between(AppSerial, &ATCMD_GetRxBuffer(0), '\n', 2, '\r', 1);
                __dbss(":  ", AppSerial);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_GET_CIMI: // <editor-fold defaultstate="collapsed" desc="International Mobile Subscriber Identity">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nCIMI");
            }

            rslt=ATCMD_SendGetAck("AT+CIMI\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
            {
                //\r\n452019173922312\r\n\r\nOK\r\n
                str_sub_between(AppCimi, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbss(":    ", AppCimi);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_GET_CCID: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nCCID");
            }

            rslt=ATCMD_SendGetAck("AT+CCID\r", "\r\nOK\r\n", 250, 250);

            if(rslt==RESULT_DONE)
            {
                //\r\n\r\n8984012105502006430\r\n\r\nOK\r\n
                str_sub_between(AppCcid, &ATCMD_GetRxBuffer(0), '\n', 2, '\r', 1);
                __dbss(":    ", AppCcid);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbsi("\nNetwork registration: ", TryCount);
            }

            rslt=ATCMD_SendGetAck("AT+CEREG?\r", "+CEREG: 0,1", 1000, 250);

            if(rslt==RESULT_DONE)
            {
                New_Task(APP_DEACTIVE_PDP);
                //__dbs(": Registered");
            }
            else if(rslt==RESULT_ERR)
            {
                Next_Task();
            } // </editor-fold>
            break;

        case APP_ALT_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbsi("\nNetwork registration: ", TryCount);
            }

            rslt=ATCMD_SendGetAck("AT+CREG?\r", "+CREG: 0,1", 1000, 250);

            if(rslt==RESULT_DONE)
            {
                Next_Task();
                //__dbs(": Registered");
            }
            else if(rslt==RESULT_ERR)
            {
                if(++TryCount>=30)
                {
                    New_Task(APP_REBOOT);
                    __dbs("\nNetwork registration error");
                }
                else
                    Wait_Task(1000, APP_CHECK_NETWORK);
            } // </editor-fold>
            break;

        case APP_DEACTIVE_PDP: // <editor-fold defaultstate="collapsed" desc="Deactive PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbs("\nDe-active PDP");
            }

            rslt=ATCMD_SendGetAck("AT+CFUN=0\r", "\r\n+CPIN: NOT READY\r\n", 3000, 250);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nDe-active PDP error");
            } // </editor-fold>
            break;

        case APP_SET_APN: // <editor-fold defaultstate="collapsed" desc="Set APN">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                sprintf(TxBuff.pData, "AT*MCGDEFCONT=\"IP\",\"%s\"\r", pConfig->Apn);
                //__dbs("\nSet APN");
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, "\r\nOK\r\n", 1000, 250);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nSet APN error");
            } // </editor-fold>
            break;

        case APP_ACTIVE_PDP: // <editor-fold defaultstate="collapsed" desc="Active PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbs("\nActive PDP");
            }

            rslt=ATCMD_SendGetAck("AT+CFUN=1\r", "\r\n+CPIN: READY\r\n", 5000, 2000);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nActive PDP error");
            } // </editor-fold>
            break;

        case APP_READ_PDP: // <editor-fold defaultstate="collapsed" desc="Read PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                //__dbs("\nActive PDP");
            }

            rslt=ATCMD_SendGetAck("AT+CGCONTRDP=1\r", "\r\nOK\r\n", 5000, 2000);

            if(rslt==RESULT_DONE)
            {
                if(findSString(&ATCMD_GetRxBuffer(0), ATCMD_GetRxBufferSize(), "+CGCONTRDP:"))
                {
                    Next_Task();
                    //\r\n+CGCONTRDP: 1,5,"m-wap","10.222.81.159.255.255.255.0",,"10.53.120.254","10.51.40.254",,,,,1500\r\n\r\nOK\r\n
                    str_sub(AppIp, &ATCMD_GetRxBuffer(0), ',', 3, 1, '.', 4, -1);
                    __dbss("\nIP:      ", AppIp);
                }
                else if(++TryCount>=5)
                {
                    New_Task(APP_REBOOT);
                    __dbs("\nActive PDP error");
                }
                else
                    Wait_Task(1000, APP_READ_PDP);
            }
            else if(rslt==RESULT_ERR)
            {
                if(++TryCount>=5)
                {
                    New_Task(APP_REBOOT);
                    __dbs("\nActive PDP error");
                }
                else
                    Wait_Task(1000, APP_ACTIVE_PDP);
            } // </editor-fold>
            break;

        case APP_GET_RTCC: // <editor-fold defaultstate="collapsed" desc="Get RTC">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nGet RTCC");
            }

            rslt=ATCMD_SendGetAck("AT+CCLK?\r", "\r\nOK\r\n", 1000, 250);

            if(rslt==PROC_DONE)
            {
                //\r\n#CCLK: "22/12/28,09:52:41+28,0"\r\n\r\nOK\r\n
                __dbs(": ");
                __dbdata(&ATCMD_GetRxBuffer(0), ATCMD_GetRxBufferSize());

                if(strstr(&ATCMD_GetRxBuffer(0), "80/01/06")==NULL)
                {
                    int first=1+str_1st_index(&ATCMD_GetRxBuffer(0), '"');

                    SysRtc.tm_year=UIntParse(&ATCMD_GetRxBuffer(first));
                    SysRtc.tm_mon=UIntParse(&ATCMD_GetRxBuffer(first+3));
                    SysRtc.tm_mday=UIntParse(&ATCMD_GetRxBuffer(first+6));
                    SysRtc.tm_hour=UIntParse(&ATCMD_GetRxBuffer(first+9));
                    SysRtc.tm_min=UIntParse(&ATCMD_GetRxBuffer(first+12));
                    SysRtc.tm_sec=UIntParse(&ATCMD_GetRxBuffer(first+15));
                    RTCC_TimeSet(&SysRtc);
                    __dbstime("\nRTCC Set: ", SysRtc);
                    __dbsdate(", ", SysRtc);

                    Next_Task();
                }
                else
                    Wait_Task(1000, APP_GET_RTCC);
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": Error");
            } // </editor-fold>
            break;

        case APP_CREATE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Create socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nCreate socket");
            }

            rslt=ATCMD_SendGetAck("AT+CSOC=1,1,1\r", "\r\nOK\r\n", 5000, 250);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                __dbs(": ");
                __dbdata(&ATCMD_GetRxBuffer(0), ATCMD_GetRxBufferSize());
            }
            else if(rslt==PROC_ERR)
            {
                if(++TryCount>=5)
                {
                    New_Task(APP_REBOOT);
                    __dbs(": Error");
                }
                else
                    Wait_Task(1000, APP_CREATE_SOCKET);
            } // </editor-fold>
            break;

        case APP_OPEN_SOCKET: // <editor-fold defaultstate="collapsed" desc="Open socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                sprintf(TxBuff.pData, "AT+CSOCON=0,%s,\"%s\"\r", pConfig->Port, pConfig->Ip);

                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbss("] Open socket: ", pConfig->Ip);
                __dbss(":", pConfig->Port);
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, "\r\nOK\r\n", 30000, 250);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                AppCount=1;
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": Error");
            } // </editor-fold>
            break;

        case APP_SEND_DATA: // <editor-fold defaultstate="collapsed" desc="Send data">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                TxBuff.Len=sprintf(TxBuff.pData, "AT+CSOSEND=0,0,\"\n%s-%s-%s:%d.%d\"\r", AppSerial, AppCimi, AppCcid, AppCount, TryCount);
                //sprintf(RxBuff.pData, "\n%s-%s-%s:%d.%d", AppSerial, AppCimi, AppCcid, AppCount);
                strcpy(RxBuff.pData, &TxBuff.pData[16]);
                Start=Tick_Timer_Read();

                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbsi("] TX %d (byte): ", TxBuff.Len);
                __dbsdata(" (byte): ", TxBuff.pData, TxBuff.Len);
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RxBuff.pData, 20000, 1000);

            if(rslt==PROC_DONE)
            {
                TryCount=0;
                AppCount++;
                Stop=Tick_Timer_Read();
                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbs("] RX: Matched");
                __dbsi("\n--> ", (Stop-Start)/TICK_PER_MS);
                __dbs("(ms)\n");

                if(AppCount>pConfig->AppCount)
                    New_Task(APP_REBOOT);
                else
                    Wait_Task(pConfig->MsgDelay, APP_SEND_DATA);
            }
            else if(rslt==PROC_ERR)
            {
                Stop=Tick_Timer_Read();
                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbs("] RX: ");

                if(ATCMD_GetRxBufferSize()>0)
                {
                    __dbdata(&ATCMD_GetRxBuffer(0), ATCMD_GetRxBufferSize());

                    if(strstr(&ATCMD_GetRxBuffer(0), "NO CARRIER")!=NULL)
                        Next_Task();
                }
                else
                    __dbs("<NULL>");

                if(TryCount>=5)
                {
                    New_Task(APP_CLOSE_SOCKET);
                    __dbs("\nError");
                }
                else
                {
                    Wait_Task(500, APP_SEND_DATA);
                    __dbsi("\nRetry %d", ++TryCount);
                }

                __dbsi("\n--> ", (Stop-Start)/TICK_PER_MS);
                __dbs("(ms)\n");
            } // </editor-fold>
            break;

        case APP_CLOSE_SECTION: // <editor-fold defaultstate="collapsed" desc="Close TCP/IP section">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n", SysRtc);
                __dbs("] Close section");
            }

            rslt=ATCMD_SendGetAck("+++\r", "\r\nOK\r\n", 5000, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": Error");
            } // </editor-fold>
            break;

        case APP_CLOSE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Close socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbs("] Close socket");
            }

            rslt=ATCMD_SendGetAck("AT#SH=1\r", "\r\nOK\r\n", 5000, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": Error");
            } // </editor-fold>
            break;

        case APP_REBOOT:
        default: // <editor-fold defaultstate="collapsed" desc="Software reset">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __dbstime("\n[", SysRtc);
                __dbs("] Module reboot");
            }

            rslt=ATCMD_SendGetAck("AT+CRESET\r", "\r\nOK\r\n", 5000, 250);

            if(rslt==PROC_DONE)
            {
                TryCount=0;
                Wait_Task(20000, APP_ECHO_OFF);
            }
            else if(rslt==PROC_ERR)
                return AppCxt.Backup; // </editor-fold>
            break;
    }

    return 0;
} // </editor-fold>

static void LoadCfg(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="Load config">
{
    __dbsi("\nLOAD CONFIGURE: ", sizeof (cfg_t));
    __dbs("(byte)");
    memcpy((void *) pConfig, (void *) UserConfig, sizeof (cfg_t));

    uint32_t crc=crc32((uint8_t *) pConfig, sizeof (cfg_t)-4);

    if(crc!=pConfig->Crc32)
    {
        __dbsh("\nCRC error ", crc);
        __dbsh(" != ", pConfig->Crc32);
        __dbs("\nUse default config");
        memcpy((void *) pConfig, (void *) &DefaultConfig, sizeof (cfg_t));
    }

    ConfigDisplay(pConfig);
} // </editor-fold>

static void SaveCfg(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="Save config">
{
    uint32_t flash_storage_address, flashOffset;

    pConfig->Crc32=crc32((uint8_t *) pConfig, sizeof (cfg_t)-4);
    ConfigDisplay(pConfig);

    uint32_t *pData=(uint32_t *) pConfig;

    flash_storage_address=(uint32_t) UserConfig;
    FLASH_Unlock(FLASH_UNLOCK_KEY);
    __dbsh("\nSAVE CONFIGURE @ ", flash_storage_address);
    __dbsh(", CRC=", pConfig->Crc32);

    if(!FLASH_ErasePage(flash_storage_address))
    {
        __dbs("\nErase error");
        return;
    }

    for(flashOffset=0; flashOffset<sizeof (cfg_t); flashOffset+=8)
    {
        uint32_t Data0=*pData++;
        uint32_t Data1=*pData++;

        if(!FLASH_WriteDoubleWord(flash_storage_address+flashOffset, Data0, Data1))
        {
            __dbs("\nWrite error");
            return;
        }
    }

    FLASH_Lock();
    __dbs("\nDone");
    LoadCfg(pConfig);
} // </editor-fold>

static bool ConfigTask(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="Configure task">
{
    /* AT command protocol: AT+<CMD>=<Parameters><\r>
     * Set host IP: AT+IP=103.156.0.37 or AT+IP=www.rpc.vn
     * Set host port: AT+PORT=1234
     * Set APN: AT+APN=m-nbiot
     * Set message interval (ms): AT+MSGDELAY=20000
     * Set app delay (ms): AT+APPDELAY=1000
     * Set app reset count: AT+COUNT=10
     * System reboot: AT+REBOOT
     ************************************************************************ */
    static size_t cmdidx[10]={0, 0, 0, 0, 0, 0, 0, 0, 0};
    static uint8_t idx=0, next=0;
    uint8_t c;

    if(!USB_CDC_Debug_Is_RxReady())
        return 0;

    c=USB_CDC_Debug_Read();
    __dbc(c);

    switch(next)
    {
        default:
            c=UpperCase(c);

            if(FindString(c, &cmdidx[next++], "AT\r"))
            {
                idx=0;
                __dbss("\nAT COMMAND HELPER%s", Help);
                goto __EXIT_OK;
            }

            if(FindString(c, &cmdidx[next++], "AT+IP="))
            {
                idx=0;
                memset((void *) &pConfig->BkArr, 0x00, 64);
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT+PORT="))
            {
                idx=0;
                memset((void *) &pConfig->BkArr, 0x00, 64);
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT+APN="))
            {
                idx=0;
                memset((void *) &pConfig->BkArr, 0x00, 64);
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT+MSGDELAY="))
            {
                idx=0;
                pConfig->BkVal=0;
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT+APPDELAY="))
            {
                idx=0;
                pConfig->BkVal=0;
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT+APPCOUNT="))
            {
                idx=0;
                pConfig->BkVal=0;
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT&W"))
            {
                idx=0;
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT&F"))
            {
                idx=0;
                break;
            }

            if(FindString(c, &cmdidx[next++], "AT&V"))
            {
                idx=0;
                break;
            }

            if(c=='\r')
                goto __EXIT_ERR;
            else
                next=0;
            break;

        case 2: // Set IP
            if(c=='\r')
            {
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    strcpy(pConfig->Ip, pConfig->BkArr);
                    __dbss("\nSet IP: ", pConfig->Ip);
                    goto __EXIT_OK;
                }
            }
            else
            {
                pConfig->BkArr[idx++]=c;

                if(idx>=64)
                    idx=0;
            }
            break;

        case 3: // Set port
            if(c=='\r')
            {
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    pConfig->BkArr[idx++]=0;

                    if(UIntParse(pConfig->BkArr)<65536)
                    {
                        strcpy(pConfig->Port, pConfig->BkArr);
                        __dbss("\nSet port: ", pConfig->Port);
                        goto __EXIT_OK;
                    }
                    else
                        goto __EXIT_ERR;
                }
            }
            else
            {
                pConfig->BkArr[idx++]=c;

                if(idx>5)
                    idx=0;
            }
            break;

        case 4: // Set APN
            if(c=='\r')
            {
                pConfig->BkArr[idx++]=0;

                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    strcpy(pConfig->Apn, pConfig->BkArr);
                    __dbss("\nSet APN: ", pConfig->Apn);
                    goto __EXIT_OK;
                }
            }
            else
            {
                pConfig->BkArr[idx++]=c;

                if(idx>16)
                    idx=0;
            }
            break;

        case 5: // Set message interval (ms)
            if(c=='\r')
            {
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    if(pConfig->BkVal==0)
                    {
                        pConfig->BkVal=1;
                        __dbs("\nMinimum message delay is 1ms");
                    }

                    pConfig->MsgDelay=pConfig->BkVal;
                    __dbsi("\nSet message delay (ms): ", pConfig->MsgDelay);
                    goto __EXIT_OK;
                }
            }
            else
            {
                idx++;
                pConfig->BkVal*=10;

                if(str_is_number(c)!=0xFF)
                    pConfig->BkVal+=str_is_number(c);
            }
            break;

        case 6: // Set app delay (sec)
            if(c=='\r')
            {
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    if(pConfig->BkVal==0)
                    {
                        pConfig->BkVal=1;
                        __dbs("\nMinimum app delay is 1sec");
                    }

                    pConfig->AppDelay=pConfig->BkVal;
                    __dbsi("\nSet app delay (sec): ", pConfig->AppDelay);
                    goto __EXIT_OK;
                }
            }
            else
            {
                idx++;
                pConfig->BkVal*=10;

                if(str_is_number(c)!=0xFF)
                    pConfig->BkVal+=str_is_number(c);
            }
            break;

        case 7: // Set app reset count
            if(c=='\r')
            {
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    if(pConfig->BkVal<5)
                    {
                        pConfig->BkVal=5;
                        __dbs("\nMinimum app reset count is 5");
                    }

                    pConfig->AppCount=pConfig->BkVal;
                    __dbsi("\nSet reset count: ", pConfig->AppCount);
                    goto __EXIT_OK;
                }
            }
            else
            {
                idx++;
                pConfig->BkVal*=10;

                if(str_is_number(c)!=0xFF)
                    pConfig->BkVal+=str_is_number(c);
            }
            break;

        case 8: // Save config and reboot
            if(c=='\r')
            {
                if(idx==0)
                {
                    SaveCfg(pConfig);
                    return 1;
                }
                else
                    goto __EXIT_ERR;
            }
            else
                idx++;
            break;

        case 9: // Load default config
            if(c=='\r')
            {
                if(idx==0)
                {
                    __dbs("\nLOAD DEFAULT CONFIG");
                    memcpy((void *) pConfig, (void *) &DefaultConfig, sizeof (cfg_t));
                    goto __EXIT_OK;
                }
                else
                    goto __EXIT_ERR;
            }
            else
                idx++;
            break;

        case 10: // Display current config
            if(c=='\r')
            {
                if(idx==0)
                {
                    __dbs("\nDISPLAY CURRENT CONFIG");
                    ConfigDisplay(pConfig);
                    goto __EXIT_OK;
                }
                else
                    goto __EXIT_ERR;
            }
            else
                idx++;
            break;
    }

    return 0;

__EXIT_OK:
    for(idx=0; idx<membersof(cmdidx); idx++)
        cmdidx[idx]=0;

    idx=0;
    next=0;
    __dbs("\nOK\n");
    return 0;

__EXIT_ERR:
    for(idx=0; idx<membersof(cmdidx); idx++)
        cmdidx[idx]=0;

    idx=0;
    next=0;
    __dbs("\nERROR\n");
    return 0;
} // </editor-fold>

static bool CELL_WaitPwrUp(void) // <editor-fold defaultstate="collapsed" desc="Check power up">
{
    int8_t rslt=ATCMD_SendGetAck("AT\r", "\r\nOK\r\n", 250, 100);

    if(rslt==RESULT_DONE)
        return 1;

    return 0;
} // </editor-fold>

static bool CELL_WaitPwrDown(void) // <editor-fold defaultstate="collapsed" desc="Check power down">
{
    int8_t rslt=ATCMD_SendGetAck("AT\r", "\r\nOK\r\n", 250, 100);

    if(rslt==RESULT_ERR)
        return 1;

    return 0;
} // </editor-fold>

void Application_Init(void) // <editor-fold defaultstate="collapsed" desc="Application initialize">
{
    Indicator_Init();
    RTCC_TimeSet(&SysRtc);
    RxBuff.pData=Buff1;
    RxBuff.Size=membersof(Buff1);
    ATCMD_Init(&RxBuff);

    TxBuff.pData=Buff2;
    TxBuff.Size=membersof(Buff2);
} // </editor-fold>

void Application_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Application tasks">
{
    static cfg_t AppConfig;
    static uint8_t DoNext=0;
    static size_t AccessKey=0;
    static tick_timer_t TickCell={1, 0, 0};
    int8_t rslt;

    switch(DoNext)
    {
        case 0: // System info display
            DoNext++;
            RestCodeDisplay();
            LoadCfg(&AppConfig);
            RLED_Toggle(25, 25);
            __dbss(HwInfo, "\nStarting up...\n");

            if(CELL_WaitPwrUp())
                DoNext++;
            break;

        case 1:
            CELL_ONOFF_SetHigh();

            if(Tick_Timer_Is_Over_Ms(TickCell, 300))
            {
                DoNext++;
                CELL_ONOFF_SetLow();
            }
            break;

        case 2: // Disable cellular power
            if(CELL_WaitPwrUp())
            {
                DoNext++;
                Wait_Task(5000, APP_ECHO_OFF);
                Tick_Timer_Reset(AppCxt.Tick);
                Tick_Timer_Reset(TickCell);
                RLED_Toggle(10, 990);
                __dbs("\nApp started");
            }
            else if(Tick_Timer_Is_Over_Sec(TickCell, 3))
            {
                DoNext--;
                __dbs("\nModule is not working");
            }
            break;

        case 3:
            rslt=CellTasks(&AppConfig);

            if(rslt>APP_IDLE)
            {
                DoNext--;
                Tick_Timer_Reset(TickCell);
                RLED_Toggle(25, 25);
                __dbs("\nApp is restarting\n");
            }
            break;

        case 4:
            DoNext++;
            RLED_Toggle(500, 500);
            __dbss("\n\nCONFIGURATION MODE\n", Help);

        case 5:
            if(ConfigTask(&AppConfig))
            {
                DoNext++;
            }
            break;

        case 6: // Do nothing
        default:
            break;
    }

    if((DoNext<3)||(DoNext==6))
    {
        if(USB_CDC_Debug_Is_RxReady())
        {
            if(FindString(USB_CDC_Debug_Read(), &AccessKey, "$$$\r"))
                DoNext=3;
        }
    }

    switch(MOD_Button_GetState())
    {
        case SINGLE_PRESS:
            __dbs("\nReset trigger 100ms\n");
            MCLR_TRIG_OneShot(100);
            break;

        case DOUBLE_PRESS: // Configure mode
            break;

        case HOLD_PRESS: // System reboot
            __dbs("\nSystem is restarting\n");
            WDT_Disable();
            GLED_SetLow();
            BLED_SetLow();
            MCLR_TRIG_SetLow();

            while(1)
                TaskManager();

        default:
            break;
    }
} // </editor-fold>