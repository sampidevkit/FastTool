#include "libcomp.h"
#include "Application.h"

#define HOST_IP             "45.79.112.203"
#define HOST_PORT           "4242"
#define SECTION_INTERVAL    1 // ms
#define APP_COUNT           10

#define Next_Task()         do{AppCxt.ToDo=AppCxt.Backup=AppCxt.DoNext; \
                            AppCxt.DoNext++; AppCxt.Flag=0;}while(0)

#define New_Task(now)       do{AppCxt.ToDo=AppCxt.Backup=AppCxt.DoNext; \
                            AppCxt.DoNext=now; AppCxt.Flag=0;}while(0)

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
    APP_READ_PDP,
    APP_CREATE_SOCKET,
    APP_OPEN_SOCKET,
    APP_SEND_DATA,
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
    uint8_t Flag;
} AppCxt;

private uint8_t Buff1[1024]; // Tx buffer
private uint8_t Buff2[1024]; // Rx buffer

private buff_t TxBuff;
private buff_t RxBuff;
private uint32_t AppCount=0;
private uint8_t AppSerial[24];
private uint8_t AppCcid[24];
private uint8_t AppCimi[24];
private uint8_t AppModuleName[24];
private uint8_t AppIp[40];

static const char HwInfo[]={
    "\n\nNB-IOT DEMO"
    "\nBuild: " __TIME__ "-" __DATE__ "\n"
};

static void Wait_Task(tick_t wait, apptask_t donext)
{
    if(donext!=AppCxt.DoNext)
        AppCxt.Flag=0;
    
    AppCxt.Backup=AppCxt.DoNext;
    AppCxt.DoNext=APP_IDLE;
    AppCxt.ToDo=donext;
    AppCxt.Wait=wait;
    Tick_Timer_Reset(AppCxt.Tick);
}

static int8_t CellTasks(void) // <editor-fold defaultstate="collapsed" desc="MQTT Application">
{
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
                }
            } // </editor-fold>
            break;

        case APP_ECHO_OFF: // <editor-fold defaultstate="collapsed" desc="Echo off">
            if(AppCxt.Flag==0)
                AppCxt.Flag=1;

            rslt=ATCMD_SendGetAck("ATE0\r", RES_OK, 500, 250, 10);

            if(rslt==RESULT_DONE)
                Next_Task();
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("\nEcho off error");
            } // </editor-fold>
            break;

        case APP_ERR_REPORT: // <editor-fold defaultstate="collapsed" desc="Enable error report">
            if(AppCxt.Flag==0)
                AppCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT+CMEE=2\r", RES_OK, 250, 250, 3);

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
                AppCxt.Flag=1;

            rslt=ATCMD_SendGetAck("AT&K0\r", RES_OK, 250, 250, 3);

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
                __dbs("\nProduct: ");
            }

            rslt=ATCMD_SendGetAck("AT+CGMM\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\nME310G1-WW\r\n\r\nOK\r\n
                str_sub_between(AppModuleName, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppModuleName);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_IMEI: // <editor-fold defaultstate="collapsed" desc="Request product serial number identification">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nSerial: ");
            }

            rslt=ATCMD_SendGetAck("AT+CGSN\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n359206100023282\r\n\r\nOK\r\n
                str_sub_between(AppSerial, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppSerial);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_CIMI: // <editor-fold defaultstate="collapsed" desc="International Mobile Subscriber Identity">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nCIMI: ");
            }

            rslt=ATCMD_SendGetAck("AT+CIMI\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n452019173922312\r\n\r\nOK\r\n
                str_sub_between(AppCimi, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppCimi);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_GET_CCID: // <editor-fold defaultstate="collapsed" desc="Get module name">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nCCID: ");
            }

            rslt=ATCMD_SendGetAck("AT+CCID\r", RES_OK, 250, 250, 3);

            if(rslt==RESULT_DONE)
            {
                //\r\n8984012105502006430\r\n\r\nOK\r\n
                str_sub_between(AppCcid, &ATCMD_GetRxBuffer(0), '\n', 1, '\r', 1);
                __dbs(AppCcid);
                Next_Task();
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nLTE Network: ");
            }

            rslt=ATCMD_SendGetAck("AT+CEREG?\r", "+CEREG: 0,1", 1000, 250, 3);

            if(rslt==RESULT_DONE)
            {
                New_Task(APP_READ_PDP);
                __dbs("Registered");
            }
            else if(rslt==RESULT_ERR)
            {
                Next_Task();
                __dbs("Un-Registered");
            } // </editor-fold>
            break;

        case APP_ALT_CHECK_NETWORK: // <editor-fold defaultstate="collapsed" desc="Check network registration">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nGSM Network: ");
            }

            rslt=ATCMD_SendGetAck("AT+CREG?\r", "+CREG: 0,1", 1000, 250, 3);

            if(rslt==RESULT_DONE)
            {
                Next_Task();
                __dbs("Registered");
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("Un-Registered");
            } // </editor-fold>
            break;

        case APP_READ_PDP: // <editor-fold defaultstate="collapsed" desc="Read PDP">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nIP: ");
            }

            rslt=ATCMD_SendGetAck("AT+CGCONTRDP=1\r", RES_OK, 5000, 2000, 3);

            if(rslt==RESULT_DONE)
            {
                if(findSString(&ATCMD_GetRxBuffer(0), "+CGCONTRDP:"))
                {
                    Next_Task();
                    //\r\n+CGCONTRDP: 1,5,"m-wap","10.222.81.159.255.255.255.0",,"10.53.120.254","10.51.40.254",,,,,1500\r\n\r\nOK\r\n
                    str_sub(AppIp, &ATCMD_GetRxBuffer(0), ',', 3, 2, '.', 4, -1);
                    __dbs(AppIp);
                }
                else if(++AppCxt.Flag>3)
                {
                    New_Task(APP_REBOOT);
                    __dbs("not achieve");
                }
                else
                {
                    Wait_Task(1000, APP_READ_PDP);
                    __dbsi("wait ", AppCxt.Flag);
                }
            }
            else if(rslt==RESULT_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_CREATE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Create socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nOpen socket");
            }

            rslt=ATCMD_SendGetAck("AT+CSOC=1,1,1\r", RES_OK, 5000, 250, 3);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_OPEN_SOCKET: // <editor-fold defaultstate="collapsed" desc="Open socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                sprintf(TxBuff.pData, "AT+CSOCON=0,%s,\"%s\"\r", HOST_PORT, HOST_IP);
                __dbss("\nConnect to ", HOST_IP);
                __dbss(":", HOST_PORT);
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RES_OK, 30000, 250, 3);

            if(rslt==PROC_DONE)
            {
                Next_Task();
                AppCount=1;
                __dbs(": OK");
            }
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_SEND_DATA: // <editor-fold defaultstate="collapsed" desc="Send data">
            if(AppCxt.Flag==0)
            {
                int i;
                uint8_t Rnd[128];
                
                AppCxt.Flag=1;
                srand(Tick_Get());
                
                for(i=0; i<127; i++)
                    Rnd[i]=(uint8_t)rand();
                
                Rnd[i]='\n';
                Array2AHex(TxBuff.pData, );
                TxBuff.Len=sprintf(TxBuff.pData, "AT+CSOSEND=0,0,\"\n%s-%s-%s:%d.%d\"\r", AppSerial, AppCimi, AppCcid, AppCount);
                strcpy(RxBuff.pData, &TxBuff.pData[16]);
                Start=Tick_Timer_Read();
                __dbs("\nSend data: ");
            }

            rslt=ATCMD_SendGetAck(TxBuff.pData, RxBuff.pData, 20000, 1000, 3);

            if(rslt==PROC_DONE)
            {

            }
            else if(rslt==PROC_ERR)
            {
                Next_Task();
                __dbs("error");
            } // </editor-fold>
            break;

        case APP_CLOSE_SOCKET: // <editor-fold defaultstate="collapsed" desc="Close socket">
            if(AppCxt.Flag==0)
            {
                AppCxt.Flag=1;
                __dbs("\nClose socket");
            }

            rslt=ATCMD_SendGetAck("AT+CSOCL=0\r", RES_OK, 5000, 250, 3);

            if(rslt==PROC_DONE)
                Next_Task();
            else if(rslt==PROC_ERR)
            {
                New_Task(APP_REBOOT);
                __dbs(": error");
            } // </editor-fold>
            break;

        case APP_REBOOT:
        default: // <editor-fold defaultstate="collapsed" desc="Software reset">
            return RESULT_REBOOT;// </editor-fold>
    }

    return RESULT_BUSY;
} // </editor-fold>

void Application_Init(void) // <editor-fold defaultstate="collapsed" desc="Application initialize">
{
    Indicator_Init();
    RxBuff.pData=Buff1;
    RxBuff.Size=membersof(Buff1);
    ATCMD_Init(&RxBuff);

    TxBuff.pData=Buff2;
    TxBuff.Size=membersof(Buff2);
} // </editor-fold>

void Application_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Application tasks">
{
    static bool Mode=0;
    static uint8_t DoNext=0, ToDo=0;
    static tick_timer_t TickCell={1, 0, 0};
    int8_t rslt;

    switch(DoNext)
    {
        default: // ON-OFF trigger
            CELL_ONOFF_SetHigh();

            if(Tick_Timer_Is_Over_Ms(TickCell, 1000))
            {
                CELL_ONOFF_SetLow();
                DoNext=254;
            }
            break;

        case 254:
            if(Tick_Timer_Is_Over_Ms(TickCell, 3000))
                DoNext=ToDo;
            break;

        case 0: // System info display
            DoNext++;
            RLED_Toggle(25, 25);
            __dbs(HwInfo);

        case 1: // Check module off
            rslt=ATCMD_Test(3);

            if(rslt==RESULT_DONE) // already ON
            {
                DoNext=255;
                ToDo=1;
                Tick_Timer_Reset(TickCell);
                __dbs("\nTrigger off");
            }
            else if(rslt==RESULT_ERR) // already OFF
            {
                DoNext=255;
                ToDo=2;
                Tick_Timer_Reset(TickCell);
                __dbs("\nTrigger on");
            }
            break;

        case 2: // Check module on
            rslt=ATCMD_Test(30);

            if(rslt==RESULT_DONE) // already ON
            {
                DoNext++;
                New_Task(APP_ECHO_OFF);
                Tick_Timer_Reset(AppCxt.Tick);
                Tick_Timer_Reset(TickCell);
                RLED_Toggle(10, 990);
                __dbs("\nTCP/IP Test Mode\n");
            }
            else if(rslt==RESULT_ERR) // already OFF
            {
                DoNext=255;
                ToDo=2;
                Tick_Timer_Reset(TickCell);
                __dbs("\nTrigger on again");
            }
            break;

        case 3:
            if(Mode==0)
            {
                rslt=CellTasks();

                if(rslt==RESULT_REBOOT)
                {
                    DoNext=2;
                    Tick_Timer_Reset(TickCell);
                    RLED_Toggle(25, 25);
                    __dbs("\nApp is restarting\n");
                }
            }
            else
            {
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
            if(Mode==0)
            {
                Mode=1;
                RLED_Toggle(500, 500);
                __dbs("\nAT Command Mode\n");
            }
            else
            {
                Mode=0;
                New_Task(APP_ECHO_OFF);
                Tick_Timer_Reset(AppCxt.Tick);
                Tick_Timer_Reset(TickCell);
                RLED_Toggle(10, 990);
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