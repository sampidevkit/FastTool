#include "libcomp.h"
#include "Application.h"

int main(void)
{
    uint8_t DoNext=0;
    tick_timer_t Tick={1, 0, 0};

    SYSTEM_Initialize();
    TaskManager_Init();
    WDT_Enable();
    Bootloader_Init();

    while(1)
    {
        switch(DoNext)
        {
            case 0:
                if(Tick_Timer_Is_Over_Sec(Tick, 5))
                {
                    DoNext=1;
                    USBDeviceAttach();
                    USB_CDC_Debug_Init();
                    Application_Init();
                }
                break;

            case 1:
                if(Tick_Timer_Is_Over_Sec(Tick, 3))
                    DoNext++;
                break;

            default:
                Application_Tasks();
                break;
        }

        TaskManager();
    }

    return 1;
}

