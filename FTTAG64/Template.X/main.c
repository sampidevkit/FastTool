#include "libcomp.h"
#include "Application.h"

int main(void)
{
    SYSTEM_Initialize();
    Application_Init();

    while(1)
    {
        Bootloader_Tasks();
        Application_Tasks();
        USB_CDC_Tasks();
    }

    return 1;
}

