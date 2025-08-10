#ifndef PROJECT_CFG_H
#define	PROJECT_CFG_H

#include "mcc.h"

#define Disable_Global_Interrupt()  INTERRUPT_GlobalDisable()
#define Enable_Global_Interrupt()   INTERRUPT_GlobalEnable()

#define TICK_PER_SEC                16000000U // Clock source of core timer
#define TICK_PER_MS                 16000U
#define TICK_PER_US                 16U

#define NUM_OF_INDICATORS           3

#define USE_SYSTIME_STAMP
#define USE_TASKMANAGER
#define USE_VCP_ATC

void SYS_Wait(void);

#endif
