#include "SystemTick.h"
#include "libcomp.h"

bool Tick_Is_Over(tick_t *pTick, uint32_t us) // <editor-fold defaultstate="collapsed" desc="Check timeout">
{
    if(pTick->Over==1)
    {
        pTick->Begin=Tick_Get();
        pTick->End=us*TICK_PER_US;
        pTick->Over=0;
    }

    if((Tick_Get()-pTick->Begin)>=pTick->End)
        pTick->Over=1;

    return pTick->Over;
} // </editor-fold>

void __delay_ms(uint32_t t) // <editor-fold defaultstate="collapsed" desc="delay ms">
{
    tick_t Tick;

    Tick.Begin=Tick_Get();
    Tick.End=t*TICK_PER_MS;

    while((Tick_Get()-Tick.Begin)<Tick.End);
} // </editor-fold>

void __delay_us(uint32_t t) // <editor-fold defaultstate="collapsed" desc="delay us">
{
    tick_t Tick;

    Tick.Begin=Tick_Get();
    Tick.End=t*TICK_PER_US;

    while((Tick_Get()-Tick.Begin)<Tick.End);
} // </editor-fold>