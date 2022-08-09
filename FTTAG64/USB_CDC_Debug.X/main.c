#include "libcomp.h"
#include "Application.h"

int main(void)
{
    SYSTEM_Initialize();
    Application_Init();

    while(1)
    {
        Bootloader_Tasks(NULL);
        Application_Tasks();
        
#if defined(USB_CDC_DEBUG_H)
        USB_CDC_Debug_Tasks();
#elif defined(USB_CDC_UART_H)
        USB_CDC_UART_Tasks();
#endif
    }

    return 1;
}

