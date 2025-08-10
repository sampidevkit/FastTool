#include "Indicator/Indicator.h"
#include "pin_manager.h"

void LED1_SetState(bool state)
{
    if(state)
        LED_ACTIVE_SetHigh();
    else
        LED_ACTIVE_SetLow();
}

void LED2_SetState(bool state)
{
    if(state)
        LED_RESET_SetHigh();
    else
        LED_RESET_SetLow();
}

void LED3_SetState(bool state)
{
    if(state)
        LED_HALT_SetHigh();
    else
        LED_HALT_SetLow();
}
