#include "AppMain.h"
#include "VCP_ATC.h"
#include "VCP_Debug.h"
#include "PID_Controller.h"
#include "common/Utils.h"
#include "UPDI.h"

static char buff[64];
static tick_timer_t Tick;

/* ************************************************************************** */
#define PK3_VDD_ON  1
#define PK3_VDD_OFF 0
#define PK3_VDD_GET 2

bool PK3_VDD_Control(uint8_t mode) // <editor-fold defaultstate="collapsed" desc="Power control">
{
    if(mode==PK3_VDD_ON)
    {
        VDD_PUMP_SetHigh();
        VDD_GND_SetLow();
        SUPPY_PWR_SetLow();
        __dbs("\r\nPK3 Power on");
        return 1;
    }

    if(mode==PK3_VDD_OFF)
    {
        VDD_GND_SetHigh();
        SUPPY_PWR_SetHigh();
        __dbs("\r\nPK3 Power off");
        return 0;
    }

    if((VDD_GND_GetValue()==0) &&(SUPPY_PWR_GetValue()==0))
        return 1;

    return 0;
} // </editor-fold>

/* ************************************************************************** */
#define PK3_VUSB_ON 1
#define PK3_VUSB_OFF 0
#define PK3_VUSB_GET 2

bool PK3_VUSB_Control(uint8_t mode) // <editor-fold defaultstate="collapsed" desc="VUSB control">
{
    if(mode==PK3_VUSB_ON)
    {
        USB_ON_SetHigh();
        __dbs("\r\nPK3 VUSB on");
        return 1;
    }

    if(mode==PK3_VUSB_OFF)
    {
        USB_ON_SetLow();
        __dbs("\r\nPK3 VUSB off");
        return 0;
    }

    if(USB_ON_GetValue())
        return 1;

    return 0;
} // </editor-fold>

/* ************************************************************************** */
#define PK3_VPP_ON  1
#define PK3_VPP_OFF 0

void PK3_VPP_Control(bool ena) // <editor-fold defaultstate="collapsed" desc="VPP control">
{
    VPP_GND_SetLow();

    if(ena==PK3_VPP_ON)
    {
        VPP_ON_SetHigh();
        __dbs("\r\nVPP on");
    }
    else
    {
        VPP_ON_SetLow();
        __dbs("\r\nVPP off");
    }
} // </editor-fold>

/* ************************************************************************** */
#define PK3_MCLR_ON  1
#define PK3_MCLR_OFF 0

void PK3_MCLR_Control(bool ena) // <editor-fold defaultstate="collapsed" desc="MCLR control">
{
    VPP_ON_SetLow();

    if(ena==PK3_MCLR_ON)
    {
        VPP_GND_SetHigh();
        __dbs("\r\nMCLR on");
    }
    else
    {
        VPP_GND_SetLow();
        __dbs("\r\nMCLR off");
    }
} // </editor-fold>

/* ************************************************************************** */
#define PK3_PWR_VDD 0
#define PK3_PWR_VPP 1

uint16_t PK3_PWR_Get(uint8_t Channel) // <editor-fold defaultstate="collapsed" desc="Get voltage">
{
    uint16_t conversion;
    uint32_t voltage;
    ADC1_CHANNEL adcChannel;

    if(Channel==PK3_PWR_VDD)
        adcChannel=VDD_FBACK;
    else if(Channel==PK3_PWR_VPP)
        adcChannel=VPP_FBACK;
    else
        return 0;

    ADC1_Enable();
    ADC1_ChannelSelect(adcChannel);
    ADC1_SoftwareTriggerEnable();
    __delay_us(20);
    ADC1_SoftwareTriggerDisable();

    while(!ADC1_IsConversionComplete(adcChannel));
    conversion=ADC1_ConversionResultGet(adcChannel);

    ADC1_Disable();

    // ADC Vref=2500mV
    // ADC Reso=1024
    voltage=conversion;

    if(Channel==PK3_PWR_VDD)
    {
        /* Rt=10k, Rb=2.2k
         VDD_FBACK=(ADC*Vref)/Reso=ADC*2500/1024=ADC*625/256
         VDD=(VDD_FBACK/Rb)*(Rb+Rt)=(ADC*625/(256*2.2))*(3.9+2.2)
         =ADC*38125/5632         */
        voltage*=38125;
        voltage/=5632;
    }
    else if(Channel==PK3_PWR_VPP)
    {
        /* Rt=10k, Rb=2.2k
         VDD_FBACK=(ADC*Vref)/Reso=ADC*2500/1024=ADC*625/256
         VDD=(VDD_FBACK/Rb)*(Rb+Rt)=(ADC*625/(256*2.2))*(10+2.2)
         =ADC*76250/5632         */
        voltage*=76250;
        voltage/=5632;
    }

    return (uint16_t) voltage;
} // </editor-fold>

/* ************************************************************************** */

void DataVisualize(int16_t pwm, int16_t vol) // <editor-fold defaultstate="collapsed" desc="Data visualize">
{
    uint8_t i, dvBuff[6];

    dvBuff[0]=0x03;
    dvBuff[1]=(uint8_t) pwm;
    dvBuff[2]=(uint8_t) (pwm>>8);
    dvBuff[3]=(uint8_t) vol;
    dvBuff[4]=(uint8_t) (vol>>8);
    dvBuff[5]=0xFC;

    for(i=0; i<6; i++)
    {
        while(!VCP_ATC_IsTxReady())
            TaskManager();

        VCP_ATC_Write(dvBuff[i]);
    }

    while(!VCP_ATC_IsTxDone())
        TaskManager();
} // </editor-fold>

/* ************************************************************************** */
volatile int32_t VppFback=0, VppFbackBk=0;
volatile uint16_t Pwm=0, PwmBk=0;
bool VppReady=0;

void VPP_Regulator(void) // <editor-fold defaultstate="collapsed" desc="VPP regulator">
{
    int i;
    uint32_t tmp;

    for(i=0, tmp=0; i<4; i++)
        tmp+=PK3_PWR_Get(PK3_PWR_VPP);

    VppFback=tmp>>2;

    Pwm=PID_Task(VppFback);
    OC1_PrimaryValueSet(Pwm);
    ClrWdt();
} // </editor-fold>

/* ************************************************************************** */

enum
{
    CMD_IDLE=0,
    CMD_INFO,
    CMD_VPP_ON,
    CMD_VPP_OFF,
    CMD_HVP_ENTRY,
    CMD_ERROR
};

uint8_t cmdCode=CMD_IDLE;
size_t cmpCxt[4]={0, 0, 0, 0};

void VCP_Debug_Cmd(const uint8_t *pStr, uint8_t len) // <editor-fold defaultstate="collapsed" desc="Debug cmd">
{
    while(len>0)
    {
        uint8_t c=UpperCase(*pStr);

        if(FindString(c, &cmpCxt[0], "INFO\r"))
        {
            cmdCode=CMD_INFO;
            break;
        }

        if(FindString(c, &cmpCxt[1], "VPP=ON\r"))
        {
            cmdCode=CMD_VPP_ON;
            break;
        }

        if(FindString(c, &cmpCxt[2], "VPP=OFF\r"))
        {
            cmdCode=CMD_VPP_OFF;
            break;
        }

        if(FindString(c, &cmpCxt[3], "HVP\r"))
        {
            cmdCode=CMD_HVP_ENTRY;
            break;
        }

        if(c=='\r')
            cmdCode=CMD_ERROR;

        pStr++;
        len--;
    }
} // </editor-fold>

/* ************************************************************************** */

void AppMain_Init(void) // <editor-fold defaultstate="collapsed" desc="App init">
{
    VCP_Debug_SetRxCallback(VCP_Debug_Cmd);
    PK3_VUSB_Control(PK3_VUSB_ON);
    __delay_ms(100);

    if(!USB_GOOD_GetValue())
        __dbs("\r\nNo USB power");

    Tick_Timer_Reset(Tick);
    PK3_VDD_Control(PK3_VDD_ON);
    PID_Init(9000);
    VppReady=0;
    OC1_PrimaryValueSet(0);
    TMR4_Stop();
    TMR4_SetInterruptHandler(VPP_Regulator);
    __dbs("\r\nAppMain init done\r\n");
} // </editor-fold>

void AppMain_Tasks(void) // <editor-fold defaultstate="collapsed" desc="App tasks">
{
    if((VppFbackBk!=VppFback)||(PwmBk!=Pwm))
    {
        VppFbackBk=VppFback;
        PwmBk=Pwm;
        DataVisualize(PwmBk, VppFbackBk);
    }

    if(VppFback>=PercentOf(PID_GetSetpoint(), 95))
    {
        VppReady=1;
        LED_RESET_SetHigh();
    }
    else
    {
        VppReady=0;
        LED_RESET_SetLow();
    }

    switch(cmdCode)
    {
        case CMD_INFO:
        {
            if(USB_GOOD_GetValue())
                __dbs("\r\nUSB power ready");
            else
                __dbs("\r\nNo USB power");

            sprintf(buff, "\r\nVDD=%d", PK3_PWR_Get(PK3_PWR_VDD));
            __dbs(buff);

            sprintf(buff, "\r\nVPP=%d", PK3_PWR_Get(PK3_PWR_VPP));
            __dbs(buff);

            cmdCode=CMD_IDLE;
            break;
        }

        case CMD_VPP_ON:
        {
            PID_Init(9000);
            VppFback=0;
            TMR4_Start();
            __dbs("\r\nVPP on");
            cmdCode=CMD_IDLE;
            break;
        }

        case CMD_VPP_OFF:
        {
            TMR4_Stop();
            VppFback=0;
            __dbs("\r\nVPP off");
            cmdCode=CMD_IDLE;
            break;
        }

        case CMD_HVP_ENTRY:
        {
            if(VppReady==1)
            {
                if(PK3_PWR_Get(PK3_PWR_VDD)>=PercentOf(5000, 95))
                {
                    PK3_MCLR_Control(PK3_MCLR_ON);
                    LED_HALT_SetHigh();

                    __dbs("\r\nHVP entry");
                    __delay_ms(10);
                    PK3_VPP_Control(PK3_VPP_ON);
                    __delay_us(100);
                    PK3_MCLR_Control(PK3_MCLR_OFF);
                    PK3_VPP_Control(PK3_VPP_OFF);
                    __dbsu("\r\nData=", UPDI_ReadData(0));
                    DATA_EN_SetLow(); // RX enable
                    LED_HALT_SetLow();
                }
                else
                    __dbs("\r\nVDD is not ready");
            }
            else
                __dbs("\r\nVPP is not ready");

            cmdCode=CMD_IDLE;
            break;
        }

        case CMD_ERROR:
        {
            __dbs("\r\nERROR\r\n");
            break;
        }

        case CMD_IDLE:
        default:
            break;
    }
} // </editor-fold>
