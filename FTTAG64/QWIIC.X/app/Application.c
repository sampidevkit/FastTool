#include "libcomp.h"
#include "Application.h"

#define RTChart_Putc(c) _mon_putc(c)

static int16_t Data[2];
static bool i2c_error=1;

static void RTChart(int16_t *pD, uint8_t len) // <editor-fold defaultstate="collapsed" desc="Plot integer data">
{
    uint8_t c;
    uint32_t i, j;
    int16_t tmp;

    RTChart_Putc(0xFE);

    for(i=0; i<len; i++)
    {
        tmp=*pD++;

        for(j=0; j<2; j++)
        {
            c=((uint8_t *) (&tmp))[j];

            switch(c)
            {
                case 0xFC:
                case 0xFD:
                case 0xFE:
                    RTChart_Putc(0xFD);
                    RTChart_Putc(c^0x20);
                    break;

                default:
                    RTChart_Putc(c);
                    break;
            }
        }
    }

    RTChart_Putc(0xFC);
} // </editor-fold>

static void I2C_Master_writeNBytes(uint8_t slvaddr, void* data, size_t len) // <editor-fold defaultstate="collapsed" desc="I2C master write">
{
    i2c_error=0;

    uint32_t Tk=Tick_Get();

    while(!i2c_open(slvaddr)) // sit here until we get the bus..
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
            i2c_reset();
            i2c_error=1;
            __db("\nI2C Write: Get bus error");
            return;
        }
    }

    i2c_setBuffer(data, len);
    i2c_setAddressNACKCallback(i2c_restartWrite, NULL); //NACK polling?
    i2c_masterWrite();
    Tk=Tick_Get();

    while(I2C_BUSY==i2c_close()) // sit here until finished.
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
            i2c_reset();
            i2c_error=1;
            __db("\nI2C Write: Close bus error");
            return;
        }
    }
} // </editor-fold>

static void I2C_Master_readNBytes(uint8_t slvaddr, void *data, size_t len) // <editor-fold defaultstate="collapsed" desc="I2C master read">
{
    if(i2c_error==1)
        return;

    uint32_t Tk=Tick_Get();

    while(!i2c_open(slvaddr)) // sit here until we get the bus..
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
            i2c_reset();
            i2c_error=1;
            __db("\nI2C Read: Get bus error");
            return;
        }
    }

    i2c_setBuffer(data, len);
    i2c_masterRead();
    Tk=Tick_Get();

    while(I2C_BUSY==i2c_close()) // sit here until finished.
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
            i2c_reset();
            i2c_error=1;
            __db("\nI2C Read: Close bus error");
            return;
        }
    }
} // </editor-fold>

static bool AT30TS74_Process(uint8_t SlvAddr, int16_t *pRslt) // <editor-fold defaultstate="collapsed" desc="AT30TS74 process">
{
#define AT30TS74_TEMPER_REG 0x00 // Temperature Register
#define AT30TS74_CONFIG_REG 0x01 // Configuration Register
#define AT30TS74_TLOW_REG   0x02 // TLOW Limit Register
#define AT30TS74_THIGH_REG  0x03 // THIGH Limit Register

    static uint8_t DoNext1=0, DoNext2=0;
    float tmp;
    uint8_t *DoNext, Buff[16];
    int16_t rslt;

    if(SlvAddr==0x4B)
        DoNext=&DoNext1;
    else if(SlvAddr==0x4F)
        DoNext=&DoNext2;

    switch(*DoNext)
    {
        case 0: // Shutdown
            Buff[0]=AT30TS74_CONFIG_REG;
            Buff[1]=0x01;
            Buff[2]=0x00;
            I2C_Master_writeNBytes(SlvAddr, Buff, 3);

            if(i2c_error==1)
            {
                __db("\nAT30TS74: %02X not found\n", SlvAddr);
                break;
            }

            *DoNext=*DoNext+1;
            break;

        case 1: // Configure
            Buff[0]=AT30TS74_CONFIG_REG;
            Buff[1]=0xFE;
            Buff[2]=0x00;
            I2C_Master_writeNBytes(SlvAddr, Buff, 3);

            if(i2c_error==1)
            {
                *DoNext=0;
                break;
            }

            *DoNext=*DoNext+1;
            break;

        case 2:
            Buff[0]=AT30TS74_CONFIG_REG;
            Buff[1]=0x02;
            Buff[2]=0x00;
            I2C_Master_writeNBytes(SlvAddr, Buff, 3);

            if(i2c_error==1)
            {
                *DoNext=0;
                break;
            }

            *DoNext=*DoNext+1;
            __db("\nAT30TS74: %02X initialized\n", SlvAddr);
            break;

        case 3:
            Buff[0]=AT30TS74_TEMPER_REG;
            I2C_Master_writeNBytes(SlvAddr, Buff, 1);
            I2C_Master_readNBytes(SlvAddr, Buff, 2);

            if(i2c_error==1)
            {
                *DoNext=0;
                break;
            }

            rslt=Buff[0];
            rslt<<=8;
            rslt|=Buff[1];
            rslt>>=7;

            if(rslt&0x8000)
                rslt-=512;

            tmp=rslt;
            tmp*=0.5f;
            rslt=(int16_t) tmp;
            *pRslt=rslt;
            return 1;

        default:
            break;
    }

    return 0;
} // </editor-fold>

static void ButtonCallback(void) // <editor-fold defaultstate="collapsed" desc="Button callback function">
{
    i2c_reset();
    USBDeviceDetach();
    while(1);
} // </editor-fold>

void Application_Init(void) // <editor-fold defaultstate="collapsed" desc="Application initialize">
{
    MOD_Button_SetSinglePress_Event(ButtonCallback);
} // </editor-fold>

void Application_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Application task">
{
    static uint8_t DoNext=0;
    static tick_t Tick={1, 0, 0};

    switch(DoNext)
    {
        case 20:
            DoNext++;
            USBDeviceAttach();
        default:
            if(Tick_Is_Over_Ms(&Tick, 100))
            {
                DoNext++;
                ST_LED_Toggle();
                TX_LED_Toggle();
                RX_LED_Toggle();
            }
            break;

        case 30:
            DoNext++;
            __db("\nRUNNING\n");
        case 31:
            if(Tick_Is_Over_Ms(&Tick, 300))
            {
                ST_LED_Toggle();
                TX_LED_SetHigh();
                RX_LED_SetHigh();

                if(AT30TS74_Process(0x4B, &Data[0])==1)
                {
                    TX_LED_SetLow();

                    if(AT30TS74_Process(0x4F, &Data[1])==1)
                    {
                        RX_LED_SetLow();
                        RTChart(Data, 2);
                    }
                }
            }
            break;
    }
} // </editor-fold>