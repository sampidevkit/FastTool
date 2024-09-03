#ifndef TICKCOUNTER_H
#define	TICKCOUNTER_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "TickCounter_Cfg.h"
#endif

typedef uint16_t tick_counter_t;

public bool Tick_Counter_Is_Over(tick_counter_t *pTick, uint16_t Count);

#define Tick_Counter_Reset(x) x=0

#endif