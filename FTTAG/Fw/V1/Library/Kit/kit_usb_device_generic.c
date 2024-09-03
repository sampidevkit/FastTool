#include <string.h>
#include "project.h"
#include "System/Wdt.h"
#include "kit_usb_device.h"
#include "Common/RingBuffer.h"
#include "System/TaskManager.h"
#include "kit_usb_device_generic.h"

#ifndef USB_GEN_TX_BUFFER
#define USB_GEN_TX_BUFFER 64
#endif

#ifndef USB_GEN_RX_BUFFER
#define USB_GEN_RX_BUFFER 64
#endif

#ifndef GEN_EP
#define GEN_EP USBGEN_EP_SIZE
#endif

/* ********************************************************* Extern variables */
public ring_buf_rx_t KitUsbGenRxBuf; // extern variable
public ring_buf_tx_t KitUsbGenTxBuf; // extern variable
/* ********************************************************** Local variables */
private USB_HANDLE USBOutHandle=0; //Needs to be initialized to 0 at startup.
private USB_HANDLE USBInHandle=0; //Needs to be initialized to 0 at startup.
private bool Init=0;
private uint8_t RxDoNext=0, TxDoNext=0;
private task_cxt_t KitUsbGenRxTaskCxt, KitUsbGenTxTaskCxt;

public bool KIT_USB_Device_GEN_Streaming(const char c) // <editor-fold defaultstate="collapsed" desc="Be used for Prinf()">
{
    if(!Task_IsPresent((fnc_t) KIT_USB_Device_GEN_TxTask))
        return 1;

    if(Ringbuffer_IsTxReady(&KitUsbGenTxBuf)>0)
    {
        Ringbuffer_TxWrite(&KitUsbGenTxBuf, (uint8_t) c);
        return 1;
    }
    else
        Task_Manager();

    return 0;
} // </editor-fold>

public void KIT_USB_Device_GEN_TxTask(void *i) // <editor-fold defaultstate="collapsed" desc="USB GEN Tx tasks">
{
    static uint8_t TxCount=0;
    static uint8_t TxByte[64];

    switch(TxDoNext)
    {
        case 0:// Init USB Tx buffer
            KitUsbGenTxBuf.Size=USB_GEN_TX_BUFFER;

            if(RingBuffer_TxInit(&KitUsbGenTxBuf))
            {
                TxCount=0;
                TxDoNext=1;
                memset(TxByte, 0x00, sizeof(TxByte));
            }
            else
                return;
            break;

        case 1:
            while(RingBuffer_TxRead(&KitUsbGenTxBuf, &TxByte[TxCount]))
            {
                TxCount++;

                if(TxCount>=64)
                    break;
            }

            if(TxCount>0)
                TxDoNext=2;
            break;

        case 2:
            if(!GENTxHandleBusy(USBInHandle))
            {
                USBInHandle=GENTxPacket(GEN_EP, TxByte, 64);
                TxDoNext=3;
            }

        default:
            if(!GENTxHandleBusy(USBInHandle))
            {
                TxCount=0;
                TxDoNext=1;
                memset(TxByte, 0x00, sizeof(TxByte));
            }
            break;
    }
} // </editor-fold>

public void KIT_USB_Device_GEN_RxTask(void *i) // <editor-fold defaultstate="collapsed" desc="USB GEN Rx tasks">
{
    static uint8_t RxIdx=0;
    static uint8_t RxByte[64];

    switch(RxDoNext)
    {
        case 0:// Init USB Rx buffer
            KitUsbGenRxBuf.Size=USB_GEN_RX_BUFFER;

            if(RingBuffer_RxInit(&KitUsbGenRxBuf))
            {
                RxDoNext=1;
                //Re-arm the OUT endpoint for the next packet
                USBOutHandle=GENRxPacket(GEN_EP, (uint8_t*)&RxByte[0], 64);
            }
            break;

        case 1:
            if(!GENRxHandleBusy(USBOutHandle))
            {
                USBOutHandle=GENRxPacket(GEN_EP, (uint8_t *)&RxByte[0], 64);
                RxIdx=0;
                RxDoNext=2;
            }
            break;

        case 2:
            while(RingBuffer_RxWrite(&KitUsbGenRxBuf, RxByte[RxIdx])==0)
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

public void KIT_USB_Device_GEN_Init(void) // <editor-fold defaultstate="collapsed" desc="USB GEN initialize">
{
    if(Init==0)
    {
        Init=1;
        RxDoNext=0;
        TxDoNext=0;
        Task_Create_NoInput(KitUsbGenRxTaskCxt, KIT_USB_Device_GEN_RxTask);
        Task_Create_NoInput(KitUsbGenTxTaskCxt, KIT_USB_Device_GEN_TxTask);
    }
} // </editor-fold>

public void KIT_USB_Device_GEN_Deinit(void) // <editor-fold defaultstate="collapsed" desc="USB GEN Deinitialize">
{
    if(Init==1)
    {
#if(USE_GEN_DEBUG)
        Debug_SetStreamFnc(NULL);
#endif
        Task_Delete(&KitUsbGenRxTaskCxt);
        Task_Delete(&KitUsbGenTxTaskCxt);
        RingBuffer_TxDeinit(&KitUsbGenTxBuf);
        RingBuffer_RxDeinit(&KitUsbGenRxBuf);
        Init=0;
    }
} // </editor-fold>

public void KIT_USB_Device_GEN_EventInit(void) // <editor-fold defaultstate="collapsed" desc="GEN event intialize">
{
    USBOutHandle=0;
    USBInHandle=0;
    //enable the GEN endpoint
    USBEnableEndpoint(GEN_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
} // </editor-fold>
