#include "libcomp.h"
#include "Application.h"

static tick_t Tick;

static void Bt_SinglePress_Callback(void)
{
    __db("\nButton is pressed: 1 time");
}

static void Bt_DoublePress_Callback(void)
{
    __db("\nButton is pressed: 2 times");
}

void Application_Init(void)
{
    Tick_Reset(Tick);
    MOD_Button_SetSinglePress_Event(Bt_SinglePress_Callback);
    MOD_Button_SetDoublePress_Event(Bt_DoublePress_Callback);
}

void Application_Tasks(void)
{
    if(Tick_Is_Over_Ms(&Tick, 100))
        ST_LED_Toggle();


}