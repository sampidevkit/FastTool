#include "libcomp.h"
#include "kit_usb_device.h"

private bool Init=0;
private tick_timer_t Tick={1, 0, 0};

public new_simple_task_t(KIT_USB_Device_Tasks) // <editor-fold defaultstate="collapsed" desc="USB CDC tasks">
{
#ifndef USB_INTERRUPT
    USBDeviceTasks();
#endif

    if((USBGetDeviceState()>=CONFIGURED_STATE)&&(USBBusIsSuspended==false))
    {
        if(Init==1)
        {
#ifdef KIT_USB_DEVICE_CDC_H
            if(UART_DTR)
                KIT_USB_Device_CDC_Init();
            else
                KIT_USB_Device_CDC_Deinit();
#endif

#ifdef KIT_USB_DEVICE_MSD_H
            KIT_USB_Device_MSD_Init();
#endif

#ifdef KIT_USB_DEVICE_HID_H
            KIT_USB_Device_HID_Init();
#endif

#ifdef KIT_USB_DEVICE_GEN_H
            KIT_USB_Device_GEN_Init();
#endif
        }
        else
        {
            if(Tick_Timer_Is_Over_Sec(Tick, 3))
            {
                USBDeviceAttach();
                Init=1;
            }
        }
    }
    else
    {
        if(Init==1)
        {
#ifdef KIT_USB_DEVICE_CDC_H
            KIT_USB_Device_CDC_Deinit();
#endif

#ifdef KIT_USB_DEVICE_MSD_H
            KIT_USB_Device_MSD_Deinit();
#endif

#ifdef KIT_USB_DEVICE_HID_H
            KIT_USB_Device_HID_Deinit();
#endif

#ifdef KIT_USB_DEVICE_GEN_H
            KIT_USB_Device_GEN_Deinit();
#endif

            USBDeviceDetach();
            Init=0;
        }
    }
    
    Task_Done();
} // </editor-fold>

public void KIT_USB_Device_Deinit(void) // <editor-fold defaultstate="collapsed" desc="USB device init">
{
    Init=0;
    TaskManager_End_Task(KIT_USB_Device_Tasks);
} // </editor-fold>

public void KIT_USB_Device_Init(void) // <editor-fold defaultstate="collapsed" desc="USB device init">
{
    USER_USB_Device_LoadUDID();
    TaskManager_Create_NewSimpleTask(KIT_USB_Device_Tasks);
    Tick_Timer_Reset(Tick);
    Init=0;
} // </editor-fold>