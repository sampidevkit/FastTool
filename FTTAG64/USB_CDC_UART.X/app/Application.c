#include "libcomp.h"
#include "Application.h"

static uint8_t DoNext;
static tick_timer_t Tick;

static void Button_is_pressed(void)
{
    DoNext=1;
    ST_LED_SetHigh();
    TRIGGER_SetLow();
    Tick_Reset(Tick);
}

void Application_Init(void)
{
    DoNext=0;
    Tick_Reset(Tick);
    MOD_Button_SetSinglePress_Event(Button_is_pressed);
}

void Application_Tasks(void)
{
    switch(DoNext)
    {
        default:
        case 0:
            if(Tick_Is_Over_Ms(&Tick, 100))
                ST_LED_Toggle();
            break;

        case 1:
            if(Tick_Is_Over_Ms(&Tick, 4000))
            {
                DoNext=0;
                ST_LED_SetLow();
                TRIGGER_SetHigh();
            }
            break;
    }
}