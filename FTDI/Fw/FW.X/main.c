#include "libcomp.h"

private const char HwInfo[]={"\n\nSAMM-FTDI V1.0"
    "HwID: SAMM-FTDI_REV1.0\n"
    "MCU: AVR16DD20\n"
    "Fw Rel: " __DATE__ "-" __TIME__ "\n"
    "Repo: https://github.com/sampidevkit/FastTool.git\n"
    "Branch: feature/ftdi\n"};

private led_cxt_t LedCxt[2]={
    {
        LED_OFF,
        {1, 0, 0}
    },
    {
        LED_OFF,
        {1, 0, 0}
    }
};

private cfg_cxt_t CfgCxt;
private uint16_t VolBuf[4];
private uint32_t IirBuf[4]={0, 0, 0, 0};

static void LED_SetLogic(uint8_t LedIdx, uint8_t LedCxt) // <editor-fold defaultstate="collapsed" desc="Set LED logic">
{
    led_t *p=(led_t *)&LedCxt;

    switch(LedIdx)
    {
        case 0:
            if(p->red==0)
                RLED1_N_SetHigh();
            else if(p->red==1)
                RLED1_N_SetLow();
            else
                RLED1_N_Toggle();

            if(p->blue==0)
                BLED1_N_SetHigh();
            else if(p->blue==1)
                BLED1_N_SetLow();
            else
                BLED1_N_Toggle();
            break;

        case 1:
            if(p->red==0)
                RLED2_N_SetHigh();
            else if(p->red==1)
                RLED2_N_SetLow();
            else
                RLED2_N_Toggle();

            if(p->blue==0)
                BLED2_N_SetHigh();
            else if(p->blue==1)
                BLED2_N_SetLow();
            else
                BLED2_N_Toggle();
            break;

        default:
            break;
    }
} // </editor-fold>

public new_simple_task_t(LED_Tasks) // <editor-fold defaultstate="collapsed" desc="LED task">
{
    switch(LedCxt[0].state)
    {
        default:
        case LED_OFF:
            LED_SetLogic(0, 0b0000);
            break;

        case RED_ON:
            LED_SetLogic(0, 0b0001);
            break;

        case RED_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[0].tk, 500))
                LED_SetLogic(0, 0b0011);
            break;

        case BLUE_ON:
            LED_SetLogic(0, 0b0100);
            break;

        case BLUE_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[0].tk, 500))
                LED_SetLogic(0, 0b1100);
            break;

        case MAGENTA_ON:
            LED_SetLogic(0, 0b0101);
            break;

        case MAGENTA_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[0].tk, 500))
                LED_SetLogic(0, 0b1111);
            break;
    }

    switch(LedCxt[1].state)
    {
        default:
        case LED_OFF:
            LED_SetLogic(1, 0b0000);
            break;

        case RED_ON:
            LED_SetLogic(1, 0b0001);
            break;

        case RED_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[1].tk, 500))
                LED_SetLogic(1, 0b0011);
            break;

        case BLUE_ON:
            LED_SetLogic(1, 0b0100);
            break;

        case BLUE_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[1].tk, 500))
                LED_SetLogic(1, 0b1100);
            break;

        case MAGENTA_ON:
            LED_SetLogic(1, 0b0101);
            break;

        case MAGENTA_BLINK:
            if(Tick_Timer_Is_Over_Ms(LedCxt[1].tk, 500))
                LED_SetLogic(1, 0b1111);
            break;
    }

    Task_Done();
} // </editor-fold>

static void LED_SetState(uint8_t LedIdx, led_state_t state) // <editor-fold defaultstate="collapsed" desc="Set LED state">
{
    if(LedCxt[LedIdx].state!=state)
    {
        LedCxt[LedIdx].state=state;
        Tick_Timer_Reset(LedCxt[LedIdx].tk);
    }
} // </editor-fold>

static void LoadConfigure(void) // <editor-fold defaultstate="collapsed" desc="Load configures">
{
    uint8_t i;
    uint16_t cks;
    uint8_t *pD=(uint8_t*)&CfgCxt;

    __dbs("\nLoad ");

    for(i=0; i<sizeof (cfg_cxt_t); i++)
    {
        *pD=EEPROM_Read(i);
        pD++;
    }

    cks=CalcSum8(pD, sizeof (cfg_cxt_t)-1);

    if(cks==CfgCxt.cks)
        __dbs("user cfg, ");
    else
    {
        __dbs("mft cfg, ");

        CfgCxt.tr25=1000;
        CfgCxt.tr50=4158;
        CfgCxt.tr75=1924;
        CfgCxt.tr100=975;
        CfgCxt.templim=75;
        CfgCxt.vbus=VBUS_5000;
        CfgCxt.vlogic=VLOGIC_3300;
        CfgCxt.cks=CalcSum8(pD, sizeof (cfg_cxt_t)-1);
    }

    __dbs("Cks=");
    __dbh2(CfgCxt.cks);
} // </editor-fold>

static void SaveConfigure(void) // <editor-fold defaultstate="collapsed" desc="Save configures">
{
    uint8_t i;
    uint8_t *pD=(uint8_t*)&CfgCxt;

    __dbs("\nSave cfg ");
    CfgCxt.cks=CalcSum8(pD, sizeof (cfg_cxt_t)-1);

    for(i=0; i<sizeof (cfg_cxt_t); i++)
    {
        EEPROM_Write(i, *pD++);
        while(EEPROM_IsBusy());
    }

    __dbs("Cks=");
    __dbh2(CfgCxt.cks);
} // </editor-fold>

public uint16_t GetVolatge(adc_channel_t channel) // <editor-fold defaultstate="collapsed" desc="Get voltage">
{
    uint32_t tmp;

    switch(channel)
    {
        case CH_VIO_SEN:
            return VolBuf[0];

        case CH_VDD:
            tmp=VolBuf[1];
            tmp*=10;
            return (uint16_t) tmp;

        case CH_VDDIO:
            tmp=VolBuf[2];
            tmp*=10;
            return (uint16_t) tmp;

        case CH_VIO_OUT:
            return VolBuf[3];

        default:
            break;
    }

    return 0;
} // </editor-fold>

public new_delay_task_t(GetVolTask) // <editor-fold defaultstate="collapsed" desc="Get ADC input voltage">
{
    uint32_t tmp;
    uint8_t channel;

    ADC0_Enable();
    Task_Delay(GetVolTask, 10);

    for(channel=0; channel<membersof(VolBuf); channel++)
    {
        switch(channel)
        {
            case 3:
                tmp=ADC0_GetConversion(CH_VIO_OUT);
                break;

            case 2:
                tmp=ADC0_GetConversion(CH_VDDIO);
                break;

            case 1:
                tmp=ADC0_GetConversion(CH_VDD);
                break;

            case 0:
                tmp=ADC0_GetConversion(CH_VIO_SEN);
                break;

            default:
                channel=0;
                goto EXIT;
        }

        tmp*=ADC_VREF;
        tmp/=ADC_RES;
        VolBuf[channel]=iir(&IirBuf[channel], (uint16_t) tmp, 2);
    }

EXIT:
    ADC0_Disable();
    Task_Done();
} // </editor-fold>

static void SetVlogic(uint16_t mV) // <editor-fold defaultstate="collapsed" desc="Set logic voltage">
{
    uint32_t tmp;

    switch(CfgCxt.vlogic)
    {
        case VLOGIC_5000:
            LED_SetState(0, RED_ON);
            tmp=5000;
            break;

        case VLOGIC_3300:
            LED_SetState(0, MAGENTA_ON);
            tmp=3300;
            break;

        case VLOGIC_1800:
            LED_SetState(0, BLUE_ON);
            tmp=1800;
            break;

        default:
            LED_SetState(0, MAGENTA_BLINK);
            tmp=mV;
            break;
    }

    tmp*=DAC_RES;
    tmp/=DAC_VREF;

    if(tmp>=DAC_RES)
        tmp=DAC_RES-1;

    DAC0_SetOutput((dac_resolution_t) tmp);
    __dbsi("\nSet Vlogic= ", mV);
    __dbsi("mV, DAC= ", tmp);
} // </editor-fold>

static void SetVbus(void) // <editor-fold defaultstate="collapsed" desc="Set VBUS voltage">
{
    switch(CfgCxt.vbus)
    {
        case VBUS_5000:
            LED_SetState(1, RED_ON);
            AP33772_setVoltage(5000);
            AP33772_setMaxCurrent(2000);
            __dbs("\nSet Vbus=5000 mV, Imax=2000 mA");
            break;

        case VBUS_9000:
            LED_SetState(1, MAGENTA_ON);
            AP33772_setVoltage(9000);
            AP33772_setMaxCurrent(1500);
            __dbs("\nSet Vbus=9000 mV, Imax=1500 mA");
            break;

        default:
            LED_SetState(1, BLUE_ON);
            AP33772_setVoltage(12000);
            AP33772_setMaxCurrent(1000);
            __dbs("\nSet Vbus=12000 mV, Imax=1000 mA");
            break;
    }
} // </editor-fold>

int main(void) // <editor-fold defaultstate="collapsed" desc="Main">
{
    tick_timer_t Tick={1, 0, 0};

    SYSTEM_Initialize();
    INTERRUPT_GlobalEnable();
    SystemTick_Init();
    TaskManager_Init(SYSPWR_POWER_DOWN_MODE);

    __dbs(HwInfo);

    WDT_Enable();
    LoadConfigure();
    AP33772_Init();
    AP33772_setNTC(CfgCxt.tr25, CfgCxt.tr50, CfgCxt.tr75, CfgCxt.tr100);
    AP33772_setDeratingTemp(CfgCxt.templim);

    TaskManager_Create_NewSimpleTask(LED_Tasks);
    TaskManager_Create_NewDelayTask(GetVolTask);

    SetVlogic(0);
    SetVbus();

    while(1)
    {
        if(CfgCxt.vlogic==VLOGIC_VIO_SEN)
        {
            uint16_t vio_out=GetVolatge(CH_VIO_OUT);
            uint16_t vio_out_min=(vio_out*9)/10;
            uint16_t vio_out_max=(vio_out*11)/10;

            vio_out=GetVolatge(CH_VIO_SEN);

            if((vio_out<vio_out_min)||(vio_out>vio_out_max))
                SetVlogic(GetVolatge(CH_VIO_SEN));
        }

        switch(MOD_Button_GetState())
        {
            case HOLD_PRESS:
                SaveConfigure();
                _delay_ms(500);
                Reset_AVR();
                break;

            case DOUBLE_PRESS:
                if(++CfgCxt.vbus>=VBUS_OFF)
                    CfgCxt.vbus=VBUS_5000;

                SetVbus();
                break;

            case SINGLE_PRESS:
                if(++CfgCxt.vlogic>=VLOGIC_OFF)
                    CfgCxt.vlogic=VLOGIC_1800;

                SetVlogic(GetVolatge(CH_VIO_SEN));
                break;

            default:
                break;
        }

        if(Tick_Timer_Is_Over_Ms(Tick, 1000))
        {
            __dbsi("\nVbus= ", AP33772_readVoltage());
            __dbsi(" mV, Ibus= ", AP33772_readCurrent());
            __dbsi(" mA, Temp= ", AP33772_readTemp());
            __dbs(" °C");

            __dbs("\nVlogic= ");

            switch(CfgCxt.vlogic)
            {
                case VLOGIC_5000:
                    __dbs("5000");
                    break;

                case VLOGIC_3300:
                    __dbs("3300");
                    break;

                case VLOGIC_1800:
                    __dbs("1800");
                    break;

                default:
                    __dbi(GetVolatge(CH_VIO_OUT));
                    break;
            }

            __dbs(" mV");
        }

        TaskManager();
    }
} // </editor-fold>