#include "libcomp.h"
#include "Application.h"

static tick_t Tick;

void Application_Init(void)
{
    Tick_Reset(Tick);
}

void Application_Tasks(void)
{
    if(Tick_Is_Over_Ms(&Tick, 100))
        ST_LED_Toggle();
}