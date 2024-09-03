#include "ee24aa.h"
#include "libcomp.h"

#define ee24aa_debug(x) //EUSART1_Write(x)

#ifndef EE24AA_WP_SetDigitalMode
#define EE24AA_WP_SetDigitalMode()
#endif

#ifndef EE24AA_WP_SetDigitalOutput
#define EE24AA_WP_SetDigitalOutput()
#endif

#ifndef EE24AA_WP_SetDigitalInput
#define EE24AA_WP_SetDigitalInput()
#endif

#ifndef EE24AA_WP_SetHigh
#define EE24AA_WP_SetHigh()
#endif

#ifndef EE24AA_WP_SetLow
#define EE24AA_WP_SetLow()
#endif

#ifndef EE24AA_WP_GetValue
#define EE24AA_WP_GetValue() 0
#warning "Not use EE24AA_WP pin"
#endif

#ifndef EE24AA_A0_SetDigitalMode
#define EE24AA_A0_SetDigitalMode()
#endif

#ifndef EE24AA_A0_SetDigitalOutput
#define EE24AA_A0_SetDigitalOutput()
#endif

#ifndef EE24AA_A0_SetDigitalInput
#define EE24AA_A0_SetDigitalInput()
#endif

#ifndef EE24AA_A0_SetHigh
#define EE24AA_A0_SetHigh()
#endif

#ifndef EE24AA_A0_SetLow
#define EE24AA_A0_SetLow()
#endif

#ifndef EE24AA_A0_GetValue
#define EE24AA_A0_GetValue() 0
#warning "Not use EE24AA_A0 pin"
#endif

#ifndef EE24AA_A1_SetDigitalMode
#define EE24AA_A1_SetDigitalMode()
#endif

#ifndef EE24AA_A1_SetDigitalOutput
#define EE24AA_A1_SetDigitalOutput()
#endif

#ifndef EE24AA_A1_SetDigitalInput
#define EE24AA_A1_SetDigitalInput()
#endif

#ifndef EE24AA_A1_SetHigh
#define EE24AA_A1_SetHigh()
#endif

#ifndef EE24AA_A1_SetLow
#define EE24AA_A1_SetLow()
#endif

#ifndef EE24AA_A1_GetValue
#define EE24AA_A1_GetValue() 0
#warning "Not use EE24AA_A1 pin"
#endif

#ifndef EE24AA_A2_SetDigitalMode
#define EE24AA_A2_SetDigitalMode()
#endif

#ifndef EE24AA_A2_SetDigitalOutput
#define EE24AA_A2_SetDigitalOutput()
#endif

#ifndef EE24AA_A2_SetDigitalInput
#define EE24AA_A2_SetDigitalInput()
#endif

#ifndef EE24AA_A2_SetHigh
#define EE24AA_A2_SetHigh()
#endif

#ifndef EE24AA_A2_SetLow
#define EE24AA_A2_SetLow()
#endif

#ifndef EE24AA_A2_GetValue
#define EE24AA_A2_GetValue() 0
#warning "Not use EE24AA_A2 pin"
#endif

static uint8_t buffer[4];
static uint8_t i, WrTask;
static tick_timer_t Tick;
static int8_t ee24aa_state=EE24AA_ERR;

#ifdef EE24AA_MODE_PAGE
static uint8_t WrLen;
static uint16_t WrAddr;
#endif

static uint8_t EE24AA_GetSlv7bitAddr(void)
{
    uint8_t Slv7bAddr;

    Slv7bAddr=EE24AA_A2_GetValue();
    Slv7bAddr<<=1;
    Slv7bAddr|=EE24AA_A1_GetValue();
    Slv7bAddr<<=1;
    Slv7bAddr|=EE24AA_A0_GetValue();
    Slv7bAddr|=0x50;
    Slv7bAddr<<=1; // add w/r bit

    return Slv7bAddr;
}

int8_t EE24AA_Read(uint16_t addr, uint8_t *pD, uint8_t len)
{
    buffer[0]=(uint8_t) (addr>>8);
    buffer[1]=(uint8_t) (addr);
    EE24AA_I2C_Xfer(EE24AA_GetSlv7bitAddr(), &buffer[0], 2, pD, len);

    return EE24AA_I2C_GetState();
}

#ifdef EE24AA_MODE_SINGLE_BYTE

int8_t EE24AA_Write_ModeSingleByte(uint16_t addr, uint8_t *pD, uint8_t len) // <editor-fold defaultstate="collapsed" desc="EEPROM single byte mode">
{
    switch(WrTask)
    {
        case 0: // init
            i=0;
            WrTask=1;
            EE24AA_WP_SetLow(); // enable write
            Tick_Timer_Reset(Tick);
            ee24aa_debug('1');

        case 1: // make address
            addr+=i;
            buffer[0]=(uint8_t) (addr>>8);
            buffer[1]=(uint8_t) (addr);
            buffer[2]=pD[i];
            WrTask=2;
            ee24aa_debug('2');

        case 2: // write
            EE24AA_I2C_Xfer(EE24AA_GetSlv7bitAddr(), &buffer[0], 3, NULL, 0);

            if(EE24AA_I2C_GetState()==EE24AA_BUSY)
                break;

            if(EE24AA_I2C_GetState()==EE24AA_ERR)
            {
                ee24aa_debug('3');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }

            WrTask=3;

        case 3:
            if(Tick_Timer_Is_Over_Ms(Tick, 6))
                WrTask=4;
            break;

        case 4: // read
            EE24AA_I2C_Xfer(EE24AA_GetSlv7bitAddr(), &buffer[0], 2, &buffer[3], 1);

            if(EE24AA_I2C_GetState()==EE24AA_BUSY)
                break;

            if(EE24AA_I2C_GetState()==EE24AA_ERR)
            {
                ee24aa_debug('4');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }

            if(buffer[2]==buffer[3])
            {
                if(++i<len)
                {
                    WrTask=1;
                    ee24aa_debug('5');
                }
                else
                {
                    ee24aa_debug('6');
                    WrTask=0;
                    EE24AA_WP_SetHigh(); // disable write
                    return EE24AA_OK;
                }
            }
            else
            {
                ee24aa_debug('7');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }
            break;

        default:
            break;
    }

    return EE24AA_BUSY;
} // </editor-fold>
#elif defined(EE24AA_MODE_PAGE)

int8_t EE24AA_Write_ModePage(uint16_t addr, uint8_t *pD, uint8_t len) // <editor-fold defaultstate="collapsed" desc="EEPROM page mode">
{
    switch(WrTask)
    {
        case 0: // init
            i=0;
            WrTask=1;
            WrAddr=addr&0x3F;
            EE24AA_WP_SetLow(); // enable write
            Tick_Timer_Reset(Tick);
            ee24aa_debug('1');

        case 1: // make address
            WrAddr+=i;
            WrLen=
            buffer[0]=(uint8_t) (WrAddr>>8);
            buffer[1]=(uint8_t) (WrAddr);
            buffer[2]=pD[i];
            WrTask=2;
            ee24aa_debug('2');

        case 2: // write
            EE24AA_I2C_Xfer(EE24AA_GetSlv7bitAddr(), &buffer[0], 3, NULL, 0);

            if(EE24AA_I2C_GetState()==EE24AA_BUSY)
                break;

            if(EE24AA_I2C_GetState()==EE24AA_ERR)
            {
                ee24aa_debug('3');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }

            WrTask=3;

        case 3:
            if(Tick_Timer_Is_Over_Ms(Tick, 6))
                WrTask=4;
            break;

        case 4: // read
            EE24AA_I2C_Xfer(EE24AA_GetSlv7bitAddr(), &buffer[0], 2, &buffer[3], 1);

            if(EE24AA_I2C_GetState()==EE24AA_BUSY)
                break;

            if(EE24AA_I2C_GetState()==EE24AA_ERR)
            {
                ee24aa_debug('4');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }

            if(buffer[2]==buffer[3])
            {
                if(++i<len)
                {
                    WrTask=1;
                    ee24aa_debug('5');
                }
                else
                {
                    ee24aa_debug('6');
                    WrTask=0;
                    EE24AA_WP_SetHigh(); // disable write
                    return EE24AA_OK;
                }
            }
            else
            {
                ee24aa_debug('7');
                WrTask=0;
                EE24AA_WP_SetHigh(); // disable write
                return EE24AA_ERR;
            }
            break;

        default:
            break;
    }

    return EE24AA_BUSY;
}
#endif

bool EE24AA_Init(void)
{
    ee24aa_state=EE24AA_ERR;
    EE24AA_A0_SetDigitalMode();
    EE24AA_A1_SetDigitalMode();
    EE24AA_A2_SetDigitalMode();
    EE24AA_WP_SetDigitalMode();

    EE24AA_A0_SetDigitalOutput();
    EE24AA_A1_SetDigitalOutput();
    EE24AA_A2_SetDigitalOutput();
    EE24AA_WP_SetDigitalOutput();

    if(EE24AA_CS_A0)
        EE24AA_A0_SetHigh();
    else
        EE24AA_A0_SetLow();

    if(EE24AA_CS_A1)
        EE24AA_A1_SetHigh();
    else
        EE24AA_A1_SetLow();

    if(EE24AA_CS_A2)
        EE24AA_A2_SetHigh();
    else
        EE24AA_A2_SetLow();

    EE24AA_WP_SetHigh();
    WrTask=0;

    if(EE24AA_I2C_Init()==0)
    {
        ee24aa_debug('1');

        do
        {
            ee24aa_debug('2');
            ee24aa_state=EE24AA_Read(0, &i, 1);
        }
        while(ee24aa_state==EE24AA_BUSY);
    }

    return ee24aa_state;
}