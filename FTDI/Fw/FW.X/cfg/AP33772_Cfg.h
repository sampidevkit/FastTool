#ifndef AP33772_CFG_H
#define AP33772_CFG_H

#include "Timer/SystemTick.h"
#include "i2c_host/twi0.h"

//#define USE_AP33772_DEBUG
#define AP33772_I2C_Read(slvAddr, data, len)    TWI0_Read(slvAddr, data, len)
#define AP33772_I2C_Write(slvAddr, data, len)   TWI0_Write(slvAddr, data, len)
#define AP33772_DelayMs(t)                      __delay_ms(t)

#endif