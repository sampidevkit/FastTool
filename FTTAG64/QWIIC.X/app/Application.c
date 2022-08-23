#include "libcomp.h"
#include "Application.h"

static int16_t Data[4];
static uint8_t Buff[16];
static bool i2c_error=1;

#define SENSOR_ON_TOP      // [Magnet] --> [Sensor] --> [  PCB ]
//#define SENSOR_ON_BOTTOM // [Magnet] --> [  PCB ] --> [Sensor]
#define RTChart_Putc(x) _mon_putc((char)x)

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

void RTChartf(float *pD, uint8_t len) // <editor-fold defaultstate="collapsed" desc="Plot float data">
{
    uint8_t c;
    uint32_t i, j;
    float tmp;

    RTChart_Putc(0xFE);

    for(i=0; i<len; i++)
    {
        tmp=*pD++;

        for(j=0; j<4; j++)
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

static int16_t IQS624_Process(void) // <editor-fold defaultstate="collapsed" desc="IQS624 process">
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

    static uint8_t DoNext=0;
    int16_t rslt=(-1);

    ST_LED_SetHigh();

    switch(DoNext)
    {
        case 0:
            Buff[0]=IQS624_VERSION_INFO;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(IQS624_I2C_ADDRESS, Buff, 1);

            if(Buff[0]!=IQS624_PRODUCT_NR)
            {
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
            Buff[0]=IQS624_FILTERED_DEGREE_OUTPUT;
            I2C_Master_writeNBytes(IQS624_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(IQS624_I2C_ADDRESS, Buff, 2);

            if(i2c_error==1)
            {
                DoNext=0;
                __db("\nALS31313 not found\n");
                break;
            }

            rslt=Buff[1];
            rslt<<=8;
            rslt|=Buff[0];
            break;

        default:
            break;
    }

    ST_LED_SetLow();
    return rslt;
} // </editor-fold>

static int16_t Reader_MotionCounter(int16_t preAngle) // <editor-fold defaultstate="collapsed" desc="Motion detection">
{
    static int16_t prvAngle=0;

    int16_t delta;

#ifdef SENSOR_ON_TOP 
    preAngle=359-preAngle;
#endif

    delta=preAngle-prvAngle;
    prvAngle=preAngle;

    if((-360<delta)&&(delta<=-225)) // FORWARD
        return 100;

    if((225<=delta)&&(delta<360)) // REVERSE
        return -100;
} // </editor-fold>

static bool ALS31313_CfgCmp(const uint8_t *pD1, const uint8_t *pD2) // <editor-fold defaultstate="collapsed" desc="Compare 2 configures">
{
    uint32_t *data1=(uint32_t*) pD1;
    uint32_t *data2=(uint32_t*) pD2;

    if((*data1)==(*data2))
        return 1;

    return 0;
} // </editor-fold>

static int16_t ALS31313_Process(void) // <editor-fold defaultstate="collapsed" desc="ALS31313 process">
{
#define ALS31313_I2C_ADDRESS    96
#define ALS31313_SENSITIVITY    500.0
#define ALS31313_SCALE          4.0
#define ALS31313_Get_mTesla(x)  ((float)x/(ALS31313_SCALE*10.0))
#define ALS31313_Get_Temp(x)    ((((float)x-1708.0)*151.0)/2048.0)

    static const uint8_t ALS31313_EEPROM_Image[8]={
        /*0-REG 02 - byte 0*/ 0b00000000,
        /*1-REG 02 - byte 1*/ 0b00000000,
        /*2-REG 02 - byte 2*/ 0b00000011, // I2C support 1V8, enable channel Z
        /*3-REG 02 - byte 3*/ 0b11000000, // enable channel X, Y

        /*4-REG 03 - byte 0*/ 0b00000000,
        /*5-REG 03 - byte 1*/ 0b00000000,
        /*6-REG 03 - byte 2*/ 0b00000000,
        /*7-REG 03 - byte 3*/ 0b00000000,
    };

    static uint8_t DoNext=0;

    float mT, mTx, mTy, mTz, Temp;
    uint16_t x, y, z, t;
    int16_t rslt=(-1);

    TX_LED_SetHigh();

    switch(DoNext)
    {
        case 0:
            Buff[0]=0x02;
            I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(ALS31313_I2C_ADDRESS, Buff, 4);

            if(i2c_error==1)
            {
                __db("\nALS31313 not found\n");
                break;
            }

            if(!ALS31313_CfgCmp(Buff, &ALS31313_EEPROM_Image[0]))
            {
                Buff[0]=0x02;
                memcpy(&Buff[1], &ALS31313_EEPROM_Image[0], 4);
                I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 5);
                __db("\nLoad default configure 0x02");
            }

            Buff[0]=0x03;
            I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(ALS31313_I2C_ADDRESS, Buff, 4);

            if(!ALS31313_CfgCmp(Buff, &ALS31313_EEPROM_Image[4]))
            {
                Buff[0]=0x03;
                memcpy(&Buff[1], &ALS31313_EEPROM_Image[4], 4);
                I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 5);
                __db("\nLoad default configure 0x03");
            }

            Buff[0]=0x27;
            //cfg.sleep=0; // Low-Power Duty Cycle Mode
            //cfg.low_pwr_count=0; // LPDCM Inactive Time 100ms
            //cfg.i2c_loop_mode=0; // No Looping
            memset(&Buff[1], 0x00, 4);
            I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 5);
            DoNext++;
            __db("\nALS31313 initialized\n");
            break;

        case 1:
            Buff[0]=0x28;
            I2C_Master_writeNBytes(ALS31313_I2C_ADDRESS, Buff, 1);
            I2C_Master_readNBytes(ALS31313_I2C_ADDRESS, Buff, 8);

            if(i2c_error==1)
            {
                DoNext=0;
                __db("\nALS31313 not found\n");
                break;
            }

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

            mTx=ALS31313_Get_mTesla(x);
            mTx=ALS31313_Get_mTesla(y);
            mTx=ALS31313_Get_mTesla(z);
            Temp=ALS31313_Get_Temp(t);
            mT=mTx*mTx+mTy*mTy+mTz*mTz;
            rslt=(int16_t) sqrt(mT);
            break;

        default:
            break;
    }

    TX_LED_SetLow();

    return rslt;
} // </editor-fold>

static int16_t AT30TS74_Process(uint8_t SlvAddr) // <editor-fold defaultstate="collapsed" desc="AT30TS74 process">
{
#define AT30TS74_TEMPER_REG 0x00 // Temperature Register
#define AT30TS74_CONFIG_REG 0x01 // Configuration Register
#define AT30TS74_TLOW_REG   0x02 // TLOW Limit Register
#define AT30TS74_THIGH_REG  0x03 // THIGH Limit Register

    static uint8_t DoNext1=0, DoNext2=0;
    float tmp;
    uint8_t *DoNext;
    int16_t rslt=(-1);

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
                __db("\nAT30TS74 not found");
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
            break;

        default:
            break;
    }

    return rslt;
} // </editor-fold>

void Application_Init(void) // <editor-fold defaultstate="collapsed" desc="Application initialize">
{

} // </editor-fold>

void Application_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Application task">
{
    static tick_t Tick={1, 0, 0};

    if(Tick_Is_Over_Ms(&Tick, 300))
    {
        Data[0]=IQS624_Process();
        Data[1]=Reader_MotionCounter(Data[0]);
        Data[2]=AT30TS74_Process(0x4B);
        Data[3]=AT30TS74_Process(0x4F);
        RTChart(Data, 4);
    }
} // </editor-fold>