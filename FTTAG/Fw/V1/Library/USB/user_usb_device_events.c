#include "libcomp.h"

bool USER_USB_CALLBACK_EVENT_HANDLER(USB_EVENT event, void *pdata, uint16_t size)
{
    switch((int) event)
    {
        case EVENT_CONFIGURED:
#ifdef KIT_USB_DEVICE_HID_H
            KIT_USB_Device_HID_EventInit();
#endif
            
#ifdef KIT_USB_DEVICE_CDC_H
            KIT_USB_Device_CDC_EventInit();
#endif
            
#ifdef KIT_USB_DEVICE_MSD_H
            KIT_USB_Device_MSD_EventInit();
#endif
            break;

        case EVENT_EP0_REQUEST:
#ifdef KIT_USB_DEVICE_HID_H
            USBCheckHIDRequest();
#endif
            
#ifdef KIT_USB_DEVICE_CDC_H
            USBCheckCDCRequest();
#endif
            
#ifdef KIT_USB_DEVICE_MSD_H
            USBCheckMSDRequest();
#endif
            break;

        case EVENT_TRANSFER_TERMINATED:
#ifdef KIT_USB_DEVICE_MSD_H
            MSDTransferTerminated((USB_HANDLE *) pdata);
#endif
            break;

        default:
            break;
    }

    return true;
}