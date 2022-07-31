#include "Bootloader.h"
#include "libcomp.h"

void Bootloader_Tasks(void *pvParameters)
{
#ifdef USE_RTOS
    while(1)
    {
#endif
        WATCHDOG_TimerClear();

        if(MOD_Button_GetState()==HOLD_PRESS)
        {
            RX_LED_SetHigh();
            TX_LED_SetHigh();
            ST_LED_SetHigh();
            SYSKEY=0x0; //write invalid key to force lock
            SYSKEY=0xAA996655; //write Key1 to SYSKEY
            SYSKEY=0x556699AA; //write Key2 to SYSKEY
            RSWRSTSET=1;
            unsigned int dummy=RSWRST;
        }

#ifdef USE_RTOS
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
#endif
}