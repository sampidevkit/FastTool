#ifndef SYSTEMTICK_CFG_H
#define SYSTEMTICK_CFG_H

#include "timer/rtc.h"

#define USE_SYS_TMR_INTERRUPT
#define SYS_TMR_BIT_LEN         16
#define TICK_PER_SEC            32768U
#define TICK_PER_MS             32U
#define TICK_PER_US             1U
#define SysTmr_Read()           RTC_ReadCounter()
#define SysTmr_OvfCallback(x)   RTC_SetOVFIsrCallback(x)

#endif