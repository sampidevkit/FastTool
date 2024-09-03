#ifndef BOOTLOADER_CFG_H
#define BOOTLOADER_CFG_H

#define BLD_Trigger_GetState()  BT_N_GetValue()
#define BLD_Trigger_Init()      
#define BLD_Comm_Init()         do{USBDeviceInit(); KIT_USB_Device_Init();}while(0) // Uncomment in UART BLD mode
#define BLD_SystemReboot()      WDT_Disable()

#endif