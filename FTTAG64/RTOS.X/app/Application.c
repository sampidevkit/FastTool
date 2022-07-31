#include "libcomp.h"
#include "Application.h"

static void TMR2_UserCallback(void)
{
    RX_LED_Toggle();
}

static void TMR3_UserCallback(void)
{
    TX_LED_Toggle();
}

void Application_Init(void)
{
    TMR2_SetInterruptHandler(TMR2_UserCallback);
    TMR3_SetInterruptHandler(TMR3_UserCallback);
}

void Application_Tasks(void *pvParameters)
{
    while(1)
    {
        ST_LED_Toggle();
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}