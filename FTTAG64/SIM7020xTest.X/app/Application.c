#include "libcomp.h"
#include "Application.h"

#define HOST_IP             "45.79.112.203"
#define HOST_PORT           "4242"

#define SECTION_INTERVAL    1 // ms
#define APP_COUNT           10
#define TEST_DATA_SIZE      512

#define Cell_Next()         do{CellCxt.ToDo=CellCxt.Backup=CellCxt.DoNext; \
                            CellCxt.DoNext++; CellCxt.Flag=0;}while(0)

#define Main_Next()         do{MainCxt.ToDo=MainCxt.Backup=MainCxt.DoNext; \
                            MainCxt.DoNext++; MainCxt.Flag=0;}while(0)

#define Cell_New(now)       do{CellCxt.ToDo=CellCxt.Backup=CellCxt.DoNext; \
                            CellCxt.DoNext=now; CellCxt.Flag=0;}while(0)

#define Main_New(now)       do{MainCxt.ToDo=MainCxt.Backup=MainCxt.DoNext; \
                            MainCxt.DoNext=now; MainCxt.Flag=0;}while(0)

typedef enum
{
    APP_WAIT=1,
    APP_ECHO_OFF,
    APP_ERR_REPORT,
    APP_NO_FLOW_CTRL,
    APP_GET_MODULE_NAME,
    APP_GET_IMEI,
    APP_GET_CIMI,
    APP_GET_CCID,
    APP_CHECK_NETWORK,
    APP_READ_PDP,
    APP_CREATE_SOCKET,
    APP_OPEN_SOCKET,
    APP_SET_RF_REPORT,
    APP_GET_RF_REPORT,
    APP_SEND_DATA,
    APP_CLOSE_SOCKET,
    APP_REBOOT
} apptask_t;

typedef struct
{
    int32_t Rsrp;
    int32_t Rsrq;
    int32_t Rssi;
    int32_t Count;
} signal_t;

typedef enum
{
    MAIN_WAIT=0,
    MAIN_INIT,
    MAIN_TRIG_OFF,
    MAIN_TRIG_ON,
    MAIN_TEST_MODE,
    MAIN_AT_MODE
} main_task_t;

static struct
{
    apptask_t DoNext;
    apptask_t ToDo;
    apptask_t Backup;
    tick_timer_t Tick;
    tick_t Wait;
    uint8_t Flag;
} CellCxt;

static struct
{
    bool Mode;
    main_task_t DoNext;
    main_task_t ToDo;
    main_task_t Backup;
    tick_timer_t Tick;
    tick_t Wait;
    uint8_t Flag;
} MainCxt={
    0,
    MAIN_INIT,
    MAIN_INIT,
    MAIN_INIT,
    {1, 0, 0},
    1000,
    0
};

private uint8_t Buff1[ATCMD_BUFFER_SIZE]; // Tx buffer
private uint8_t Buff2[ATCMD_BUFFER_SIZE]; // Rx buffer

private buff_t TxBuff;
private buff_t RxBuff;

private tick_t Begin;
private int TestCount;
private signal_t RfCxt;
private uint8_t *AppCellTac=&Buff2[0];
private uint8_t *AppCellId=&Buff2[16];

#define AppSerial       RxBuff.pData
#define AppCcid         RxBuff.pData
#define AppCimi         RxBuff.pData
#define AppModuleName   RxBuff.pData
#define AppIp           RxBuff.pData

static const char HwInfo[]={
    "\n\nNB-IOT DEMO"
    "\nBuild: " __TIME__ "-" __DATE__ "\n"
};

static void App_Wait(tick_t wait, apptask_t donext) // <editor-fold defaultstate="collapsed" desc="Delay before to do a new task">
{
    if(donext!=CellCxt.DoNext)
        CellCxt.Flag=0;

    CellCxt.Backup=CellCxt.DoNext;
    CellCxt.DoNext=APP_WAIT;
    CellCxt.ToDo=donext;
    CellCxt.Wait=wait;
    Tick_Timer_Reset(CellCxt.Tick);
} // </editor-fold>

static void Main_Wait(tick_t wait, main_task_t donext) // <editor-fold defaultstate="collapsed" desc="Delay before to do a new task">
{
    if(donext!=MainCxt.DoNext)
        MainCxt.Flag=0;

    MainCxt.Backup=MainCxt.DoNext;
    MainCxt.DoNext=MAIN_WAIT;
    MainCxt.ToDo=donext;
    MainCxt.Wait=wait;
    Tick_Timer_Reset(MainCxt.Tick);
} // </editor-fold>

static int8_t CellTasks(void) // <editor-fold defaultstate="collapsed" desc="MQTT Application">
{
    int8_t rslt;

    switch(CellCxt.DoNext)
    {
        case APP_WAIT: // <editor-fold defaultstate="collapsed" desc="Idle state">
            if(Tick_Timer_Is_Over_Ms(CellCxt.Tick, CellCxt.Wait))
            {
                if(CellCxt.ToDo==APP_WAIT)
                    return APP_WAIT;
                else
                {
                    CellCxt.Backup=CellCxt.DoNext;
                    CellCxt.DoNext=CellCxt.ToDo;
                }
            } // </editor-fold>
            break;

        case APP_ECHO_OFF: // <editor-fold defaultstate="collapsed" desc="Echo off">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("ATE0\r", RES_OK, 500, 250, 10);

            if(rslt==RESULT_DONE)
                Cell_Next();
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nEcho off error");
            } // </editor-fold>
            break;

        case APP_ERR_REPORT: // <editor-fold defaultstate="collapsed" desc="Enable error report">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT+CMEE=2\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
                Cell_Next();
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nEnable error report error");
            } // </editor-fold>
            break;

        case APP_NO_FLOW_CTRL: // <editor-fold defaultstate="collapsed" desc="No flow control">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT&K0\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
                Cell_Next();
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nSet no HW flow control error");
            } // </editor-fold>
            break;

        case APP_GET_MODULE_NAME: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nProduct: ");
            }

            rslt=ATCMD_SendGetAck("AT+CGMM\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\nME310G1-WW\r\n\r\nOK\r\n
                str_sub_between(AppModuleName, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppModuleName);
                Cell_Next();
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_IMEI: // <editor-fold defaultstate="collapsed" desc="Request product serial number identification">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nSerial:  ");
            }

            rslt=ATCMD_SendGetAck("AT+CGSN\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n359206100023282\r\n\r\nOK\r\n
                str_sub_between(AppSerial, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppSerial);
                Cell_Next();
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_CIMI: // <editor-fold defaultstate="collapsed" desc="International Mobile Subscriber Identity">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nCIMI:    ");
            }

            rslt=ATCMD_SendGetAck("AT+CIMI\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n452019173922312\r\n\r\nOK\r\n
                str_sub_between(AppCimi, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppCimi);
                Cell_Next();
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_CCID: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nCCID:    ");
            }

            rslt=ATCMD_SendGetAck("AT+CCID\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n8984012105502006430\r\n\r\nOK\r\n
                str_sub_between(AppCcid, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppCcid);
                Cell_Next();
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nLTE:     ");
            }

            rslt=ATCMD_SendGetAck("AT+CEREG?\r", "+CEREG: 0,1", 1000, 250, 30);

            if(rslt==RESULT_DONE)
            {
                Cell_New(APP_READ_PDP);
                __dbs("Registered");
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("Un-Registered");
            } // </editor-fold>
            break;

        case APP_READ_PDP: // <editor-fold defaultstate="collapsed" desc="Read PDP">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                __dbs("\nIP:      ");
            }

            rslt=ATCMD_SendGetAck("AT+CGCONTRDP=1\r", RES_OK, 5000, 2000, 3);

            if(rslt==RESULT_DONE)
            {
                if(findSString(&ATCMD_GetRxBuffer(0), "+CGCONTRDP:"))
                {
                    Cell_Next();
                    //\r\n+CGCONTRDP: 1,5,"m-wap","10.222.81.159.255.255.255.0",,"10.53.120.254","10.51.40.254",,,,,1500\r\n\r\nOK\r\n
                    str_sub(AppIp, &ATCMD_GetRxBuffer(0), ',', 3, 2, '.', 4, -1);
                    __dbs(AppIp);
                    __dbsi(" - Wait: ", Tick_Dif_Ms(Tick_Get(), Begin));
                }
                else if(++CellCxt.Flag>3)
                {
                    Cell_New(APP_REBOOT);
                    __dbs("not achieve");
                }
                else
                {
                    App_Wait(1000, APP_READ_PDP);
                    //__dbsi("wait ", CellCxt.Flag);
                }
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_CREATE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Create socket">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT+CSOC=1,1,1\r", RES_OK, 5000, 250, 3);

            if(rslt==PROC_DONE)
                Cell_Next();
            else if(rslt==PROC_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nOpen socket error");
            } // </editor-fold>
            break;

        case APP_OPEN_SOCKET: // <editor-fold defaultstate="collapsed" desc="Open socket">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                TestCount=0;
                sprintf(TxBuff.pData, "AT+CSOCON=0,%s,\"%s\"\r", HOST_PORT, HOST_IP);
                __dbss("\nConnect: ", HOST_IP);
                __dbss(":", HOST_PORT);
                Begin=Tick_Get();
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RES_OK, 30000, 250, 3);

            if(rslt==PROC_DONE)
            {
                Cell_Next();
                __dbsi(" - Wait: ", Tick_Dif_Ms(Tick_Get(), Begin));
            }
            else if(rslt==PROC_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_SET_RF_REPORT: // <editor-fold defaultstate="collapsed" desc="Set RF report">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT+CENG=0\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                Cell_Next();
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nSet RF report error");
            } // </editor-fold>
            break;

        case APP_GET_RF_REPORT: // <editor-fold defaultstate="collapsed" desc="Get RF report">
            if(CellCxt.Flag==0)
            {
                CellCxt.Flag=1;
                RfCxt.Count=0;
                RfCxt.Rsrp=0;
                RfCxt.Rsrq=0;
                RfCxt.Rssi=0;
            }

            rslt=ATCMD_SendGetAck("AT+CENG?\r", RES_OK, 5000, 2000, 3);

            if(rslt==RESULT_DONE)
            {
                if(findSString(&ATCMD_GetRxBuffer(0), "+CENG:"))
                {
                    int32_t idx, tmp;

                    // \r\n+CENG: 1410,3,308,"01BF9A17",-77,-10,-68,32,3,"5EAD",0,,-66\r\n\r\nOK\r\n
                    //__dbss("\nRX: ", &ATCMD_GetRxBuffer(0));
                    idx=str_n_index(&ATCMD_GetRxBuffer(0), ',', 4)+1;
                    tmp=IntParse(&ATCMD_GetRxBuffer(idx));
                    RfCxt.Rsrp+=tmp;
                    //__dbsi("\nRSRP: ", tmp);

                    idx=str_n_index(&ATCMD_GetRxBuffer(0), ',', 5)+1;
                    tmp=IntParse(&ATCMD_GetRxBuffer(idx));
                    RfCxt.Rsrq+=tmp;
                    //__dbsi("\nRSRQ: ", tmp);

                    idx=str_n_index(&ATCMD_GetRxBuffer(0), ',', 6)+1;
                    tmp=IntParse(&ATCMD_GetRxBuffer(idx));
                    RfCxt.Rssi+=tmp;
                    //__dbsi("\nRSSI: ", tmp);

                    if(++RfCxt.Count>=5)
                    {
                        Cell_Next();
                        str_sub(AppCellId, &ATCMD_GetRxBuffer(0), ',', 3, 2, '\"', 1, -1);
                        str_sub(AppCellTac, &ATCMD_GetRxBuffer(0), ',', 9, 2, '\"', 1, -1);
                        RfCxt.Rsrp/=RfCxt.Count;
                        RfCxt.Rsrq/=RfCxt.Count;
                        RfCxt.Rssi/=RfCxt.Count;

                        __dbss("\n\nRF:      TAC=", AppCellTac);
                        __dbss(", CID=", AppCellId);
                        __dbsi(", RSRP=", RfCxt.Rsrp);
                        __dbsi(", RSRQ=", RfCxt.Rsrq);
                        __dbsi(", RSSI=", RfCxt.Rssi);
                    }
                    else
                        App_Wait(1000, APP_GET_RF_REPORT);
                }
                else if(++CellCxt.Flag>3)
                {
                    Cell_New(APP_REBOOT);
                    __dbs("not achieve");
                }
                else
                {
                    App_Wait(1000, APP_READ_PDP);
                    //__dbsi("wait ", CellCxt.Flag);
                }
            }
            else if(rslt==RESULT_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_SEND_DATA: // <editor-fold defaultstate="collapsed" desc="Send data">
            if(CellCxt.Flag==0)
            {
                uint8_t Rnd[TEST_DATA_SIZE];

                CellCxt.Flag=1;
                srand(Tick_Get());
                random8(Rnd, (TEST_DATA_SIZE-1), ' ', '~');
                Rnd[TEST_DATA_SIZE-1]='\n';
                RxBuff.Len=Array2AHex(RxBuff.pData, Rnd, TEST_DATA_SIZE);
                sprintf(TxBuff.pData, "AT+CSOSEND=0,%d,\"%s\"\r", RxBuff.Len, RxBuff.pData);
                TxBuff.Len=slen(TxBuff.pData);
                // Remove '\n'
                RxBuff.pData[--RxBuff.Len]=0;
                RxBuff.pData[--RxBuff.Len]=0;
                __dbsi("\nSend:    ", ++TestCount);
                __dbsi(" - ", (RxBuff.Len+2)/2);
                __dbs(" (bytes)");
                //__dbss(" (bytes) ", RxBuff.pData);
                Begin=Tick_Get();
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RxBuff.pData, 30000, 30000, 1);

            if(rslt==PROC_DONE)
            {
                //App_Wait(5000, APP_SEND_DATA);
                Cell_New(APP_GET_RF_REPORT);
                __dbsi("\n    --> matched - Wait: ", Tick_Dif_Ms(Tick_Get(), Begin));
            }
            else if(rslt==PROC_ERR)
            {
                Cell_Next();
                __dbsi("\n    --> error - Wait: ", Tick_Dif_Ms(Tick_Get(), Begin));
                __dbsi("\nRX ", ATCMD_GetRxLen());
                __dbss(" (bytes): ", &ATCMD_GetRxBuffer(0));
            } // </editor-fold>
            break;

        case APP_CLOSE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Close socket">
            if(CellCxt.Flag==0)
                CellCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT+CSOCL=0\r", RES_OK, 5000, 250, 3);

            if(rslt==PROC_DONE)
                Cell_Next();
            else if(rslt==PROC_ERR)
            {
                Cell_New(APP_REBOOT);
                __dbs("\nClose socket error");
            } // </editor-fold>
            break;

        case APP_REBOOT:
        default: // <editor-fold defaultstate="collapsed" desc="Software reset">
            return RESULT_REBOOT; // </editor-fold>
    }

    return RESULT_BUSY;
} // </editor-fold>

void Application_Init(void) // <editor-fold defaultstate="collapsed" desc="Application initialize">
{
    Indicator_Init();
    ATCMD_Init();
    RxBuff.pData=Buff1;
    RxBuff.Size=membersof(Buff1);
    TxBuff.pData=Buff2;
    TxBuff.Size=membersof(Buff2);
    Cell_New(MAIN_INIT);
} // </editor-fold>

void Application_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Application tasks">
{
    int8_t rslt;

    switch(MainCxt.DoNext)
    {
        default:
        case MAIN_WAIT:
            if(Tick_Timer_Is_Over_Ms(MainCxt.Tick, MainCxt.Wait))
                MainCxt.DoNext=MainCxt.ToDo;
            break;

        case MAIN_INIT: // System info display
            Main_Next();
            ATCMD_Delay(250);
            CELL_ONOFF_SetLow();

#ifdef CELL_PWR_EN_SetHigh
            CELL_PWR_EN_SetHigh();
#endif

            RLED_Toggle(50, 50);
            __dbs(HwInfo);
            break;

        case MAIN_TRIG_OFF: // Check module off
            if(CELL_ONOFF_GetValue()==1)
                CELL_ONOFF_SetLow();

#ifndef CELL_PWRMON_GetState
            rslt=ATCMD_Test(3|ALL_STATE_OFF);
#else
            if(CELL_PWRMON_GetState()==1)
                rslt=RESULT_DONE;
            else
                rslt=RESULT_ERR;
#endif

            if(rslt==RESULT_ERR) // already ON
            {
                Main_Wait(1000, MAIN_TRIG_OFF);
                CELL_ONOFF_SetHigh();
                __dbs("\nTrigger off");
            }
            else if(rslt==RESULT_DONE) // already OFF
            {
                Main_Wait(1000, MAIN_TRIG_ON);
                CELL_ONOFF_SetHigh();
                Begin=Tick_Get();
                __dbs("\nTrigger on");
            }
            break;

        case MAIN_TRIG_ON: // Check module on
            if(CELL_ONOFF_GetValue()==1)
                CELL_ONOFF_SetLow();

            rslt=ATCMD_Test(10|AT_LEAST_1ON);

#ifdef CELL_PWRMON_GetState
            if(CELL_PWRMON_GetState()==1)
            {
                if(Tick_Timer_Is_Over_Ms(MainCxt.Tick, 10000))
                    rslt=RESULT_ERR;
            }
            else
                Tick_Timer_Reset(MainCxt.Tick);
#endif

            if(rslt==RESULT_DONE) // already ON
            {
                __dbsi("\nBoot: ", Tick_Dif_Ms(Tick_Get(), Begin));
                CELL_ONOFF_SetLow();
                RLED_Toggle(10, 990);
                Tick_Timer_Reset(MainCxt.Tick);

                if(MainCxt.Mode==0)
                {
                    Main_New(MAIN_TEST_MODE);
                    Cell_New(APP_ECHO_OFF);
                    Tick_Timer_Reset(CellCxt.Tick);
                    __dbs("\nTCP/IP Test Mode\n");
                }
                else
                {
                    Main_New(MAIN_AT_MODE);
                    __dbs("\nAT Command Mode\n");
                }
            }
            else if(rslt==RESULT_ERR) // already OFF
            {
                CELL_ONOFF_SetHigh();
                Tick_Timer_Reset(MainCxt.Tick);
                Main_Wait(1000, MAIN_TRIG_ON);
                __dbs("\nTrigger on again");
            }
            break;

        case MAIN_TEST_MODE:
            rslt=CellTasks();

            if(rslt==RESULT_REBOOT)
            {
                Main_New(MAIN_TRIG_OFF);
                RLED_Toggle(50, 50);
                __dbs("\nApp is restarting\n");
            }
            break;

        case MAIN_AT_MODE:
            while(UART2_IsRxReady())
            {
                if(USB_CDC_Debug_Is_TxReady())
                    USB_CDC_Debug_Write(UART2_Read());
                else
                    break;
            }

            while(USB_CDC_Debug_Is_RxReady())
            {
                if(UART2_IsTxReady())
                    UART2_Write(USB_CDC_Debug_Read());
                else
                    break;
            }
            break;
    }

    switch(MOD_Button_GetState())
    {
        case SINGLE_PRESS:
            __dbs("\nReset trigger 100ms\n");
            MCLR_TRIG_OneShot(100);
            break;

        case DOUBLE_PRESS: // Configure mode
            if(MainCxt.Mode==0)
            {
                MainCxt.Mode=1;
                __dbs("\nAT Command Mode\n");
            }
            else
            {
                MainCxt.Mode=0;
                Cell_New(APP_ECHO_OFF);
                Tick_Timer_Reset(CellCxt.Tick);
                Tick_Timer_Reset(MainCxt.Tick);
                __dbs("\nTCP/IP Test Mode\n");
            }
            break;

        case HOLD_PRESS: // System reboot
            __dbs("\nSystem is restarting\n");
            // Disable UART2
            U2STACLR=_U2STA_UTXEN_MASK;
            U2STACLR=_U2STA_URXEN_MASK;
            U2MODECLR=_U2MODE_ON_MASK;
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