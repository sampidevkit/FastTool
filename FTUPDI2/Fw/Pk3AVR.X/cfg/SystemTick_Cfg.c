#include "System/TickTimer.h"
#include "tmr2.h"

tick_t Tick_Timer_Get_TickVal(void)
{
    return TMR2_Counter32BitGet();
}
