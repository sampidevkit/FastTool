#include "libcomp.h"
#include "crc32.h"
#include "AtCmd.h"
#include "Indicator.h"
#include "Application.h"

#define HOST_IP_DEFAULT             "45.79.112.203"
#define HOST_PORT_DEFAULT           "4242"
#define NETWORK_APN_DEFAULT         "v-internet"
#define SECTION_INTERVAL_DEFAULT    1 // ms
#define APP_DELAY_DEFAULT           60 // s
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
    APP_GET_IMEI,
    APP_GET_MODULE_NAME,
    APP_GET_CIMI,
    APP_GET_CCID,
    APP_CHECK_NETWORK,
    APP_DEACTIVE_PDP,
    APP_SET_APN,
    APP_ACTIVE_PDP,
    APP_GET_PDP,
    ///////////////////////////////////////////////////////////////// ME310 only
    APP_AUTO_TIMEZONE_UPDATE,
    APP_NET_ID_TIMEZONE,
    APP_CLOCK_MODE,
    ////////////////////////////////////////////////////////////////////////////
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

static uint8_t Buff1[128];
static uint8_t Buff2[128];
static uint8_t Buff3[128];

static struct tm SysRtc={
    .tm_wday=2, // Tuesday
    .tm_mday=1, // 1st
    .tm_mon=1, // Jan
    .tm_year=80, // 1980
    .tm_hour=0,
    .tm_min=0,
    .tm_sec=0,
};

static buff_t TxBuff;
static buff_t RxBuff;
static uint32_t AppCount=0;
static uint8_t AppSerial[24];
static uint8_t AppCcid[24];
static uint8_t AppCimi[24];
static uint8_t AppModuleName[24];

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

static void DataDisplay(uint8_t *pD, size_t len) // <editor-fold defaultstate="collapsed" desc="Data display">
{
    while(len>0)
    {
        if((*pD>=' ')&&(*pD<='~'))
            __db("%c", *pD);
        else
            __db("<%02X>", *pD);

        pD++;
        len--;
    }
} // </editor-fold>

static void TaskDisplay(apptask_t taskCode) // <editor-fold defaultstate="collapsed" desc="Error display">
{
    switch(taskCode)
    {
        case APP_ECHO_OFF:
            __db("APP_ECHO_OFF");
            break;

        case APP_ERR_REPORT:
            __db("APP_ERR_REPORT");
            break;

        case APP_NO_FLOW_CTRL:
            __db("APP_NO_FLOW_CTRL");
            break;

        case APP_CHECK_NETWORK:
            __db("APP_CHECK_NETWORK");
            break;

        case APP_DEACTIVE_PDP:
            __db("APP_DEACTIVE_PDP");
            break;

        case APP_ACTIVE_PDP:
            __db("APP_ACTIVE_PDP");
            break;

        case APP_OPEN_SOCKET:
            __db("APP_OPEN_SOCKET");
            break;

        case APP_SEND_DATA:
            __db("APP_SEND_DATA");
            break;

        case APP_REBOOT:
            __db("APP_REBOOT");
            break;

        default:
            __db("Unknown: %02X", taskCode);
            break;
    }
} // </editor-fold>

static void ConfigDisplay(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="Config display">
{
    __db("\nHost:               %s", pConfig->Ip);
    __db("\nPort:               %s", pConfig->Port);
    __db("\nAPN:                %s", pConfig->Apn);
    __db("\nMessage delay (ms): %d", pConfig->MsgDelay);
    __db("\nApp delay (sec):    %d", pConfig->AppDelay);
    __db("\nApp reset count:    %d", pConfig->AppCount);
    __db("\nCRC32:              %08X\n", pConfig->Crc32);
} // </editor-fold>

static void RestCodeDisplay(void) // <editor-fold defaultstate="collapsed" desc="Reset code display">
{
#ifdef __XC_PIC32M_H
    __db("\nReset control register: %08X", RCON);

    if(RCONbits.PORIO)
        __db("\n-->PORIO: A Power-on Reset has occurred due to VDD voltage");

    if(RCONbits.PORCORE)
        __db("\n-->PORCORE: A Power-on Reset has occurred due to core voltage");

    if(RCONbits.BCFGERR)
        __db("\n-->BCFGERR: An error occurred during a read of the Primary Configuration registers");

    if(RCONbits.BCFGFAIL)
        __db("\n-->BCFGFAIL: An error occurred during a read of the Primary and Alternate Configuration registers");

    if(RCONbits.CMR)
        __db("\n-->CMR: Configuration Mismatch Reset has occurred");

    if(RCONbits.EXTR)
        __db("\n-->EXTR:  Master Clear (pin) Reset has occurred");

    if(RCONbits.SWR)
        __db("\n-->SWR: Software Reset was executed");

    if(RCONbits.WDTO)
        __db("\n-->WDTO: Watchdog Timer Time-out Flag bit");

    if(RCONbits.SLEEP)
        __db("\n-->SLEEP: Device was in Sleep mode");

    if(RCONbits.IDLE)
        __db("\n-->IDLE: Device was in Idle mode");

    if(RCONbits.BOR)
        __db("\n-->BOR: Brown-out Reset has occurred");

    if(RCONbits.POR)
        __db("\n-->POR: Power-on Reset has occurred");

    RCON&=0xFFFFFF20; // Clear bit 7,6,4,3,2,1,0
#else
#warning "Reset code display doesn't support your device"
#endif
} // </editor-fold>

static int8_t TcpIpApp(cfg_t *pConfig) // <editor-fold defaultstate="collapsed" desc="MQTT Application">
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
                __db("\nEcho off");
            }

            rslt=ATCMD_SendGetAck("ATE0\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                if(++TryCount>=40)
                {
                    New_Task(APP_REBOOT);
                    __db(": Error");
                }
                else
                    Wait_Task(250, APP_ECHO_OFF);
            } // </editor-fold>
            break;

        case APP_ERR_REPORT: // <editor-fold defaultstate="collapsed" desc="Enable error report">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nReport enable");
            }

            rslt=ATCMD_SendGetAck("AT+CMEE=2\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_NO_FLOW_CTRL: // <editor-fold defaultstate="collapsed" desc="No flow control">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nNo flow control");
            }

            rslt=ATCMD_SendGetAck("AT&K0\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_GET_IMEI: // <editor-fold defaultstate="collapsed" desc="Request product serial number identification">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nProduct serial number");
            }

            rslt=ATCMD_SendGetAck("AT+CGSN\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
            {
                //\r\n\r\n359206100023282\r\n\r\nOK\r\n
                memset(AppSerial, 0, sizeof (AppSerial));
                Copy_Str2Break(&ATCMD_GetBkBuffer(4), '\r', AppSerial);
                __db(": %s", AppSerial);
                //DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());
                Next_Task();
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_GET_MODULE_NAME: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nProduct name");
            }

            rslt=ATCMD_SendGetAck("AT+CGMM\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
            {
                //\r\nME310G1-WW\r\n\r\nOK\r\n
                memset(AppModuleName, 0, sizeof (AppModuleName));
                Copy_Str2Break(&ATCMD_GetBkBuffer(2), '\r', AppModuleName);
                __db(": %s", AppModuleName);
                //DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());
                Next_Task();
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_GET_CIMI: // <editor-fold defaultstate="collapsed" desc="International Mobile Subscriber Identity">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nCIMI");
            }

            rslt=ATCMD_SendGetAck("AT+CIMI\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
            {
                //\r\n\r\n452019173922312\r\n\r\nOK\r\n
                memset(AppCimi, 0, sizeof (AppCimi));
                Copy_Str2Break(&ATCMD_GetBkBuffer(4), '\r', AppCimi);
                __db(": %s", AppCimi);
                Next_Task();
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_GET_CCID: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nCCID");
            }

            rslt=ATCMD_SendGetAck("AT+CCID\r", "OK", 250, 250);

            if(rslt==PROC_DONE)
            {
                //\r\n+CCID: 8984012105502006430\r\n\r\nOK\r\n
                memset(AppCcid, 0, sizeof (AppCcid));
                Copy_Str2Break(&ATCMD_GetBkBuffer(11), '\r', AppCcid);
                __db(": %s", AppCcid);
                Next_Task();
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nCheck EPS network registration status");
            }

            rslt=ATCMD_SendGetAck("AT+CEREG?\r", "0,1", 250, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                if(++TryCount>=10)
                {
                    New_Task(APP_REBOOT);
                    __db(": Error");
                }
                else
                    Wait_Task(1000, APP_CHECK_NETWORK);
            } // </editor-fold>
            break;

        case APP_DEACTIVE_PDP: // <editor-fold defaultstate="collapsed" desc="Deactive PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nPDP context deactivation");
            }

            Next_Task(); // </editor-fold>
            break;

        case APP_SET_APN: // <editor-fold defaultstate="collapsed" desc="Set APN">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                sprintf(TxBuff.pData, "AT+CGDCONT=1,\"IP\",\"%s\"\r", pConfig->Apn);
                __db("\nAPN config");
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, "OK", 1000, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_ACTIVE_PDP: // <editor-fold defaultstate="collapsed" desc="Actibe PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nPDP context activation");
            }

            rslt=ATCMD_SendGetAck("AT+CGACT?\r", "1,0", 60000, 250);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                __db(": ");
                DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());
            }
            else if(rslt==PROC_ERR)
            {
                if(++TryCount>=5)
                {
                    New_Task(APP_REBOOT);
                    __db(": Error");
                }
                else
                    Wait_Task(1000, APP_ACTIVE_PDP);
            } // </editor-fold>
            break;

        case APP_GET_PDP: // <editor-fold defaultstate="collapsed" desc="Get IP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nProduct name");
            }

            Next_Task(); // </editor-fold>
            break;

        case APP_AUTO_TIMEZONE_UPDATE: // <editor-fold defaultstate="collapsed" desc="Enable automatic time zone update">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nEnable automatic time zone update");
            }

            Next_Task(); // </editor-fold>
            break;

        case APP_NET_ID_TIMEZONE: // <editor-fold defaultstate="collapsed" desc="Network Identity and Time Zone">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nNetwork identity and time zone");
            }

            Next_Task(); // </editor-fold>
            break;

        case APP_CLOCK_MODE: // <editor-fold defaultstate="collapsed" desc="Clock mode">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nSet clock mode");
            }

            Next_Task(); // </editor-fold>
            break;

        case APP_GET_RTCC: // <editor-fold defaultstate="collapsed" desc="Get RTC">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nGet RTCC");
            }

            rslt=ATCMD_SendGetAck("AT+CCLK?\r", "OK", 1000, 250);

            if(rslt==PROC_DONE)
            {
                //\r\n#CCLK: "22/12/28,09:52:41+28,0"\r\n\r\nOK\r\n
                __db(": ");
                DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());

                if(strstr(&ATCMD_GetBkBuffer(0), "80/01/06")==NULL)
                {
                    int first=1+str_1st_index(&ATCMD_GetBkBuffer(0), '"');

                    SysRtc.tm_year=Parse2(&ATCMD_GetBkBuffer(first));
                    SysRtc.tm_mon=Parse2(&ATCMD_GetBkBuffer(first+3));
                    SysRtc.tm_mday=Parse2(&ATCMD_GetBkBuffer(first+6));
                    SysRtc.tm_hour=Parse2(&ATCMD_GetBkBuffer(first+9));
                    SysRtc.tm_min=Parse2(&ATCMD_GetBkBuffer(first+12));
                    SysRtc.tm_sec=Parse2(&ATCMD_GetBkBuffer(first+15));
                    RTCC_TimeSet(&SysRtc);
                    __db("\nRTCC Set: %02d:%02d:%02d, ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                    __db("%02d/%02d/%02d", SysRtc.tm_mday, SysRtc.tm_mon, SysRtc.tm_year);

                    Next_Task();
                }
                else
                    Wait_Task(1000, APP_GET_RTCC);
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_CREATE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Create socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __db("\nCreate socket");
            }

            rslt=ATCMD_SendGetAck("AT+CSOC=1,1,1\r", "OK", 5000, 250);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                __db(": ");
                DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());
            }
            else if(rslt==PROC_ERR)
            {
                if(++TryCount>=5)
                {
                    New_Task(APP_REBOOT);
                    __db(": Error");
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
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("Open socket: %s:%s", pConfig->Ip, pConfig->Port);
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, "OK", 30000, 250);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                AppCount=1;
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
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
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("TX %d (byte): ", TxBuff.Len);
                DataDisplay(TxBuff.pData, TxBuff.Len);
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RxBuff.pData, 20000, 1000);

            if(rslt==PROC_DONE)
            {
                TryCount=0;
                AppCount++;
                Stop=Tick_Timer_Read();
                while(!RTCC_TimeGet(&SysRtc));
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("RX: Matched");
                __db("\n--> %lu (ms)\n", (Stop-Start)/TICK_PER_MS);

                if(AppCount>pConfig->AppCount)
                    New_Task(APP_REBOOT);
                else
                    Wait_Task(pConfig->MsgDelay, APP_SEND_DATA);
            }
            else if(rslt==PROC_ERR)
            {
                Stop=Tick_Timer_Read();
                while(!RTCC_TimeGet(&SysRtc));
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("RX: ");

                if(ATCMD_GetBkBufferSize()>0)
                {
                    DataDisplay(&ATCMD_GetBkBuffer(0), ATCMD_GetBkBufferSize());

                    if(strstr(&ATCMD_GetBkBuffer(0), "NO CARRIER")!=NULL)
                        Next_Task();
                }
                else
                    __db("<NULL>");

                if(TryCount>=5)
                {
                    New_Task(APP_CLOSE_SOCKET);
                    __db("\nError");
                }
                else
                {
                    Wait_Task(500, APP_SEND_DATA);
                    __db("\nRetry %d", ++TryCount);
                }

                __db("\n--> %lu (ms)\n", (Stop-Start)/TICK_PER_MS);
            } // </editor-fold>
            break;

        case APP_CLOSE_SECTION: // <editor-fold defaultstate="collapsed" desc="Close TCP/IP section">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("Close section");
            }

            rslt=ATCMD_SendGetAck("+++\r", "OK", 5000, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_CLOSE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Close socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("Close socket");
            }

            rslt=ATCMD_SendGetAck("AT#SH=1\r", "OK", 5000, 250);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __db(": Error");
            } // </editor-fold>
            break;

        case APP_REBOOT:
        default: // <editor-fold defaultstate="collapsed" desc="Software reset">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                while(!RTCC_TimeGet(&SysRtc));
                __db("\n[%02d:%02d:%02d] ", SysRtc.tm_hour, SysRtc.tm_min, SysRtc.tm_sec);
                __db("Module reboot");
            }

            rslt=ATCMD_SendGetAck("AT#REBOOT\r", "OK", 5000, 250);

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
    __db("\nLOAD CONFIGURE: %d (byte)", sizeof (cfg_t));
    memcpy((void *) pConfig, (void *) UserConfig, sizeof (cfg_t));

    uint32_t crc=crc32((uint8_t *) pConfig, sizeof (cfg_t)-4);

    if(crc!=pConfig->Crc32)
    {
        __db("\nCRC error %08X != %08X", crc, pConfig->Crc32);
        __db("\nUse default config");
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
    __db("\nSAVE CONFIGURE @ %08X, CRC=%08X", flash_storage_address, pConfig->Crc32);

    if(!FLASH_ErasePage(flash_storage_address))
    {
        __db("\nErase error");
        return;
    }

    for(flashOffset=0; flashOffset<sizeof (cfg_t); flashOffset+=8)
    {
        uint32_t Data0=*pData++;
        uint32_t Data1=*pData++;

        //__db("\n%08X: %08X %08X\n", flash_storage_address+flashOffset, Data0, Data1);

        if(!FLASH_WriteDoubleWord(flash_storage_address+flashOffset, Data0, Data1))
        {
            __db("\nWrite error");
            return;
        }
    }

    FLASH_Lock();
    __db("\nDone");
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
    __db("%c", c);

    switch(next)
    {
        default:
            c=UpperCase(c);

            if(FindString(c, &cmdidx[next++], "AT\r"))
            {
                idx=0;
                __db("\nAT COMMAND HELPER%s", Help);
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
                    __db("\nSet IP: %s", pConfig->Ip);
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
                    if(Parse(pConfig->BkArr, idx)<65536)
                    {
                        strcpy(pConfig->Port, pConfig->BkArr);
                        __db("\nSet port: %s", pConfig->Port);
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
                if(idx==0)
                    goto __EXIT_ERR;
                else
                {
                    strcpy(pConfig->Apn, pConfig->BkArr);
                    __db("\nSet APN: %s", pConfig->Apn);
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
                        __db("\nMinimum message delay is 1ms");
                    }

                    pConfig->MsgDelay=pConfig->BkVal;
                    __db("\nSet message delay (ms): %d", pConfig->MsgDelay);
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
                        __db("\nMinimum app delay is 1sec");
                    }

                    pConfig->AppDelay=pConfig->BkVal;
                    __db("\nSet app delay (sec): %d", pConfig->AppDelay);
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
                        __db("\nMinimum app reset count is 5");
                    }

                    pConfig->AppCount=pConfig->BkVal;
                    __db("\nSet reset count: %d", pConfig->AppCount);
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
                    __db("\nLOAD DEFAULT CONFIG");
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
                    __db("\nDISPLAY CURRENT CONFIG");
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
    __db("\nOK\n");
    return 0;

__EXIT_ERR:
    for(idx=0; idx<membersof(cmdidx); idx++)
        cmdidx[idx]=0;

    idx=0;
    next=0;
    __db("\nERROR\n");
    return 0;
} // </editor-fold>

static void Bt_SinglePress_Callback(void)
{
    __db("\nButton is pressed: 1 time");
}

static void Bt_DoublePress_Callback(void)
{
    __db("\nButton is pressed: 2 times");
}

void Application_Init(void)
{
    Indicator_Init();
    RTCC_TimeSet(&SysRtc);
    CELL_RESET_SetHigh();
    CELL_RESET_SetDigitalOutput();
    MOD_Button_SetSinglePress_Event(Bt_SinglePress_Callback);
    MOD_Button_SetDoublePress_Event(Bt_DoublePress_Callback);
}

void Application_Tasks(void)
{
    static cfg_t AppConfig;
    static uint8_t DoNext=0;
    static size_t AccessKey=0;
    static tick_t TickCell={1, 0, 0};
    int8_t rslt;
    bool softResetFlag=0;

    switch(DoNext)
    {
        case 0: // System info display
            DoNext++;
            __db("%s", HwInfo);
            RestCodeDisplay();
            LoadCfg(&AppConfig);
            Indicator_SetState(0, 25, 25, IND_LOOP_FOREVER);
            break;

        case 1: // Disable cellular power
            CELL_RESET_SetHigh();

            if(Tick_Timer_Is_Over_Sec(TickCell, 3))
            {
                DoNext++;
                RTCC_TimeSet(&SysRtc);
                CELL_RESET_SetLow();
                Wait_Task(5000, APP_ECHO_OFF);
                ATCMD_Init();
                TxBuff.pData=Buff1;
                RxBuff.pData=Buff2;
                ATCMD_SetBkBuffer(Buff3);
                Tick_Timer_Reset(AppCxt.Tick);
                Tick_Timer_Reset(TickCell);
                Indicator_SetState(0, 10, 990, IND_LOOP_FOREVER);
                __db("\nApp started");
            }
            break;

        case 2:
            rslt=TcpIpApp(&AppConfig);

            if(rslt>APP_IDLE)
            {
                DoNext--;
                CELL_RESET_SetHigh();
                Tick_Timer_Reset(TickCell);
                Indicator_SetState(0, 25, 25, IND_LOOP_FOREVER);
                __db("\nApp is restarting\n");
            }
            break;

        case 3:
            DoNext++;
            Indicator_SetState(0, 500, 500, IND_LOOP_FOREVER);
            __db("\n\nCONFIGURATION MODE\n%s", Help);
        case 4:
            if(ConfigTask(&AppConfig))
            {
                DoNext++;
                softResetFlag=1;
            }
            break;

        case 5: // Do nothing
            break;

        case 6:
        default:
            if(Tick_Timer_Is_Over_Ms(TickCell, 5000))
                __db("\nPress BTN to start app");
            break;
    }

    if((DoNext<3)||(DoNext==6))
    {
        if(USB_CDC_Debug_Is_RxReady())
        {
            uint8_t c=USB_CDC_Debug_Read();

            if(FindString(c, &AccessKey, "$$$\r"))
            {
                DoNext=3;
                CELL_RESET_SetHigh();
            }
        }
    }

    switch(MOD_Button_GetState())
    {
        case SINGLE_PRESS: // Shutdown module
            __db("\nSINGLE PRESS");
            break;

        case DOUBLE_PRESS: // Configure mode
            __db("\nDOUBLE PRESS");
            DoNext=1;
            break;

        case HOLD_PRESS: // System reboot
            __db("\nHOLD PRESS");
            softResetFlag=1;
            break;

        default:
            break;
    }

    if(softResetFlag==1) // System reboot
    {
        __db("\nSystem is restarting\n");
        WDT_Disable();
        CELL_RESET_SetHigh();
        Indicator_SetHigh(0);

        while(1)
            TaskManager();
    }
}