#include "SystemTick.h"
#include "libcomp.h"

bool Tick_Is_Over(tick_t *pTick, uint32_t us) // <editor-fold defaultstate="collapsed" desc="Check timeout">
{
    if(pTick->Over==1)
    {
        pTick->Begin=_CP0_GET_COUNT();
        pTick->End=us*TICK_PER_US;
        pTick->Over=0;
    }

    if((_CP0_GET_COUNT()-pTick->Begin)>=pTick->End)
        pTick->Over=1;

    return pTick->Over;
} // </editor-fold>

void __delay_ms(uint32_t t) // <editor-fold defaultstate="collapsed" desc="delay ms">
{
    tick_t Tick;

    Tick.Begin=_CP0_GET_COUNT();
    Tick.End=t*TICK_PER_MS;

    while((_CP0_GET_COUNT()-Tick.Begin)<Tick.End);
} // </editor-fold>

void __delay_us(uint32_t t) // <editor-fold defaultstate="collapsed" desc="delay us">
{
    tick_t Tick;

    Tick.Begin=_CP0_GET_COUNT();
    Tick.End=t*TICK_PER_US;

    while((_CP0_GET_COUNT()-Tick.Begin)<Tick.End);
} // </editor-fold>