#include "libcomp.h"
#include "Application.h"

typedef enum
{
    IQS624_SENSOR=0,
    ALS31313_SENSOR,
    END_SENSOR_LIST
} sensor_sel_t;

static tick_t Tick;
static uint8_t DoNext;
static uint8_t Buff[8];
static sensor_sel_t SenSel;

static void I2C_Master_writeNBytes(uint8_t slvaddr, void* data, size_t len) // <editor-fold defaultstate="collapsed" desc="I2C master write">
{
    uint32_t Tk=Tick_Get();

    while(!i2c_open(slvaddr)) // sit here until we get the bus..
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
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
            __db("\nI2C Write: Close bus error");
            return;
        }
    }
} // </editor-fold>

static void I2C_Master_readNBytes(uint8_t slvaddr, void *data, size_t len) // <editor-fold defaultstate="collapsed" desc="I2C master read">
{
    uint32_t Tk=Tick_Get();

    while(!i2c_open(slvaddr)) // sit here until we get the bus..
    {
        if(Tick_Dif_Ms(Tick_Get(), Tk)>100)
        {
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
            __db("\nI2C Read: Close bus error");
            return;
        }
    }
} // </editor-fold>

static void IQS624_Process(void) // <editor-fold defaultstate="collapsed" desc="IQS624 process">
{
#define IQS624_I2C_ADDRESS              0x44
#define IQS624_PRODUCT_NR               67
#define IQS624_VERSION_INFO             0x00
#define IQS624_SYSTEM_FLAGS             0x10
#define IQS624_DEV_SETTINGS 		    0xD0
#define IQS624_HALL_SIN                 0x79
#define IQS624_HALL_COS                 0x7A
#define IQS624_FILTERED_DEGREE_OUTPUT   0x16
    //                                    _________NP segment all
    //                                    |________Enable ULP mode
    //                                    ||_______Disable auto modes
    //                                    |||______Power mode
    //                                    |||||
    //                                    |||||____NP segment rate
    //                                    ||||||||
    //                                    ||||||||
#define IQS624_PMU_SETTINGS_STARTUP     0b00100011
#define IQS624_HALL_SIN_STARTUP         0x63 // sin(degrees/180*pi)*255
#define IQS624_HALL_COS_STARTUP         0xEB // cos(degrees/180*pi)*255

    if(RX_LED_GetValue()==0)
    {
        RX_LED_SetHigh();
        TX_LED_SetLow();
        __db("\nSelect IQS624\n");
    }

    switch(DoNext)
    {
        case 0:
            Buff[0]=IQS624_VERSION_INFO;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(IQS624_I2C_ADDRESS, Buff, 1);

            if(Buff[0]!=IQS624_PRODUCT_NR)
            {
                DoNext=255;
                Tick_Reset(Tick);
                __db("\nIQS624 not found\n");
                break;
            }

            // Fill buffer with first settings
            Buff[0]=IQS624_DEV_SETTINGS;
            Buff[1]=0x48|0x02;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 2);

            Buff[0]=IQS624_DEV_SETTINGS+2;
            Buff[1]=IQS624_PMU_SETTINGS_STARTUP;
            Buff[2]=0x0E; // 15ms Comms report rate
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 3);

            Buff[0]=IQS624_HALL_SIN;
            Buff[1]=IQS624_HALL_SIN_STARTUP;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 2);

            Buff[0]=IQS624_HALL_COS;
            Buff[1]=IQS624_HALL_COS_STARTUP;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 2);

            DoNext++;
            break;

        case 1:
            Buff[0]=IQS624_SYSTEM_FLAGS;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(IQS624_I2C_ADDRESS, Buff, 1);

            if((Buff[0]&(1<<2))==0) // ATI Busy Indicator Bit
                break;

            DoNext++;
            __db("\nIQS624 initialized\n");
            break;

        case 2:
            if(Tick_Is_Over_Ms(&Tick, 500))
            {
                uint16_t Dg;
                uint32_t Tk, dt;

                ST_LED_SetHigh();
                Tk=Tick_Get();
                Buff[0]=IQS624_FILTERED_DEGREE_OUTPUT;
                I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 1);
                I2C_Master_readNBytes(IQS624_I2C_ADDRESS, Buff, 2);
                dt=Tick_Dif_Ms(Tick_Get(), Tk);
                Dg=Buff[1];
                Dg<<=8;
                Dg|=Buff[0];
                __db("\nProcess time: %d ms", dt);
                __db("\nDegree position: %d\n", Dg);
                ST_LED_SetLow();
            }
            break;

        default:
            if(Tick_Is_Over_Ms(&Tick, 1000))
                DoNext=0;
            break;
    }
} // </editor-fold>

static void ALS31313_Process(void) // <editor-fold defaultstate="collapsed" desc="ALS31313 process">
{
#define ALS31313_I2C_ADDRESS 96

    if(TX_LED_GetValue()==0)
    {
        TX_LED_SetHigh();
        RX_LED_SetLow();
        __db("\nSelect ALS31313\n");
    }

    switch(DoNext)
    {
        case 0:
            DoNext++;
            __db("\nIQS624 initialized\n");
            break;

        case 1:
            if(Tick_Is_Over_Ms(&Tick, 500))
            {
                uint16_t Dg, x, y, z, t;
                uint32_t Tk, dt;

                ST_LED_SetHigh();
                Tk=Tick_Get();
                Buff[0]=0x28;
                I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 1);
                I2C_Master_readNBytes(ALS31313_I2C_ADDRESS, Buff, 8);
                dt=Tick_Dif_Ms(Tick_Get(), Tk);

                if(Buff[3]&0x80) // new data
                {
                    x=((int16_t) Buff[0])<<4|(Buff[5]&0x0F);
                    y=((int16_t) Buff[1])<<4|(Buff[6]>>4);
                    z=((int16_t) Buff[2])<<4|(Buff[6]&0x0F);
                    t=((int16_t) (Buff[3]&0x3F))<<6|(Buff[7]&0x3F);

                    if(x&0x0800)
                        x-=0x1000;

                    if(y&0x0800)
                        y-=0x1000;

                    if(z&0x0800)
                        z-=0x1000;
                }

                __db("\nProcess time: %d ms", dt);
                __db("\nX=%d, Y=%d, Z=%d, T=%d", x, y, z, t);
                ST_LED_SetLow();
            }
            break;

        default:
            break;
    }
} // </editor-fold>

static void Button_Callback(void)
{
    DoNext=0;

    if(++SenSel==END_SENSOR_LIST)
        SenSel=IQS624_SENSOR;
}

void Application_Init(void)
{
    Tick_Reset(Tick);
    SenSel=IQS624_SENSOR;
    MOD_Button_SetSinglePress_Event(Button_Callback);
}

void Application_Tasks(void)
{
    switch(SenSel)
    {
        case IQS624_SENSOR:
            IQS624_Process();
            break;

        case ALS31313_SENSOR:
            ALS31313_Process();
            break;

        default:
            break;
    }
}