#include "kit_usb_device_hid.h"

#if(USE_KIT_USB_DEVICE_HID)

#include <xc.h>
#include <string.h>
#include "System/Wdt.h"
#include "kit_usb_device.h"
#include "usb_device_hid.h"
#include "user_usb_config.h"
#include "Common/RingBuffer.h"
#include "System/TaskManager.h"

/* ********************************************************* Extern variables */
public ring_buf_rx_t KitUsbHidRxBuf; // extern variable
public ring_buf_tx_t KitUsbHidTxBuf; // extern variable
/* ********************************************************** Local variables */
private USB_HANDLE USBOutHandle=0; //Needs to be initialized to 0 at startup.
private USB_HANDLE USBInHandle=0; //Needs to be initialized to 0 at startup.
private bool Init=0;
private uint8_t RxDoNext=0, TxDoNext=0;
private task_cxt_t KitUsbHidRxTaskCxt, KitUsbHidTxTaskCxt;

public bool KIT_USB_Device_HID_Streaming(const char c) // <editor-fold defaultstate="collapsed" desc="Be used for Prinf()">
{
    if(!Task_IsPresent(KIT_USB_Device_HID_TxTask))
        return 1;

    if(Ringbuffer_IsTxReady(&KitUsbHidTxBuf)>0)
    {
        Ringbuffer_TxWrite(&KitUsbHidTxBuf, (uint8_t) c);
        return 1;
    }
    else
    {
        Task_RunIfPresent(WDT_Tasks);
        Task_RunIfPresent(KIT_USB_Device_Tasks);
        Task_RunIfPresent(KIT_USB_Device_HID_TxTask);
    }

    return 0;
} // </editor-fold>

public void KIT_USB_Device_HID_TxTask(void *i) // <editor-fold defaultstate="collapsed" desc="USB HID Tx tasks">
{
    static uint8_t TxCount=0;
    static uint8_t TxByte[64];

    switch(TxDoNext)
    {
        case 0:// Init USB Tx buffer
            KitUsbHidTxBuf.Size=USB_HID_TX_BUFFER;

            if(RingBuffer_TxInit(&KitUsbHidTxBuf))
            {
                TxCount=0;
                TxDoNext=1;
                memset(TxByte, 0x00, sizeof(TxByte));
            }
            else
                return;
            break;

        case 1:
            while(RingBuffer_TxRead(&KitUsbHidTxBuf, &TxByte[TxCount]))
            {
                TxCount++;

                if(TxCount>=64)
                    break;
            }

            if(TxCount>0)
                TxDoNext=2;
            break;

        case 2:
            if(!HIDTxHandleBusy(USBInHandle))
            {
                USBInHandle=HIDTxPacket(HID_EP, TxByte, 64);
                TxDoNext=3;
            }

        default:
            if(!HIDTxHandleBusy(USBInHandle))
            {
                TxCount=0;
                TxDoNext=1;
                memset(TxByte, 0x00, sizeof(TxByte));
            }
            break;
    }
} // </editor-fold>

public void KIT_USB_Device_HID_RxTask(void *i) // <editor-fold defaultstate="collapsed" desc="USB HID Rx tasks">
{
    static uint8_t RxIdx=0;
    static uint8_t RxByte[64];

    switch(RxDoNext)
    {
        case 0:// Init USB Rx buffer
            KitUsbHidRxBuf.Size=USB_HID_RX_BUFFER;

            if(RingBuffer_RxInit(&KitUsbHidRxBuf))
            {
                RxDoNext=1;
                //Re-arm the OUT endpoint for the next packet
                USBOutHandle=HIDRxPacket(HID_EP, (uint8_t*)&RxByte[0], 64);
            }
            break;

        case 1:
            if(!HIDRxHandleBusy(USBOutHandle))
            {
                USBOutHandle=HIDRxPacket(HID_EP, (uint8_t *)&RxByte[0], 64);
                RxIdx=0;
                RxDoNext=2;
            }
            break;

        case 2:
            while(RingBuffer_RxWrite(&KitUsbHidRxBuf, RxByte[RxIdx])==0)
            {
                RxIdx++;

                if(RxIdx>=64)
                {
                    RxDoNext=1;
                    break;
                }
            }
            break;

        default:
            break;
    }
} // </editor-fold>

public void KIT_USB_Device_HID_Init(void) // <editor-fold defaultstate="collapsed" desc="USB HID initialize">
{
    if(Init==0)
    {
        Init=1;
        RxDoNext=0;
        TxDoNext=0;
        Task_Create_NoInput(KitUsbHidRxTaskCxt, KIT_USB_Device_HID_RxTask);
        Task_Create_NoInput(KitUsbHidTxTaskCxt, KIT_USB_Device_HID_TxTask);
    }
} // </editor-fold>

public void KIT_USB_Device_HID_Deinit(void) // <editor-fold defaultstate="collapsed" desc="USB HID Deinitialize">
{
    if(Init==1)
    {
#if(USE_HID_DEBUG)
        Debug_SetStreamFnc(NULL);
#endif
        Task_Delete(&KitUsbHidRxTaskCxt);
        Task_Delete(&KitUsbHidTxTaskCxt);
        RingBuffer_TxDeinit(&KitUsbHidTxBuf);
        RingBuffer_RxDeinit(&KitUsbHidRxBuf);
        Init=0;
    }
} // </editor-fold>

public void KIT_USB_Device_HID_EventInit(void) // <editor-fold defaultstate="collapsed" desc="HID event intialize">
{
    USBOutHandle=0;
    USBInHandle=0;
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
} // </editor-fold>

#endif