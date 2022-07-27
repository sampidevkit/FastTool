#include "libcomp.h"
#include "Application.h"

static tick_t Tick;
static uint8_t i;

void Application_Init(void)
{
    i=0;
    Tick_Reset(Tick);
}

void Application_Tasks(void)
{
    if(Tick_Is_Over(&Tick, 100))
    {
        ST_LED_Toggle();

        if(++i>10)
        {
            i=0;
            __db("\nHello");
        }
    }
    
    while(USB_CDC_Debug_Is_RxReady())
    {
        if(USB_CDC_Debug_Is_TxReady())
            USB_CDC_Debug_Write(USB_CDC_Debug_Read());
        else
            break;
    }
}