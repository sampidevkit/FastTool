#include "Bootloader.h"
#include "libcomp.h"

void Bootloader_Tasks(void)
{
    WATCHDOG_TimerClear();
    
    if(BUTTON_Is_Pressed())
    {
        RX_LED_SetHigh();
        TX_LED_SetHigh();
        ST_LED_SetHigh();
        while(1);
    }
}