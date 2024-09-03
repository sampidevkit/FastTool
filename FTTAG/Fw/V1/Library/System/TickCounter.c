#include "TickCounter.h"

public bool Tick_Counter_Is_Over(tick_counter_t *pTick, uint16_t Count) // <editor-fold defaultstate="collapsed" desc="Check 1 tick">
{
    if((uint16_t) pTick[0]<Count)
        pTick[0]++;
    else
    {
        pTick[0]=0;
        return 1;
    }

    return 0;
} // </editor-fold>
