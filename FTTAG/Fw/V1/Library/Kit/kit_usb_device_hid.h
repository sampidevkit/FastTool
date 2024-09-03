#ifndef KIT_USB_DEVICE_HID_H
#define KIT_USB_DEVICE_HID_H

#include "Common/RingBuffer.h"
#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_usb_device_cfg.h"
#endif

/* Application Definitions */
#ifdef public
#undef  public
#define public
#else
#define public
#endif

#ifdef private
#undef  private
#define private static
#else
#define private static
#endif

#define KIT_USB_Device_HID_IsRxReady()      RingBuffer_IsRxReady(&KitUsbHidRxBuf)
#define KIT_USB_Device_HID_ReadByte(pD)     RingBuffer_RxRead(&KitUsbHidRxBuf, pD)
#define KIT_USB_Device_HID_WriteByte(Data)  Ringbuffer_TxWrite(&KitUsbHidTxBuf, Data)

extern ring_buf_rx_t KitUsbHidRxBuf;
extern ring_buf_tx_t KitUsbHidTxBuf;

public bool KIT_USB_Device_HID_Streaming(const char c);
public void KIT_USB_Device_HID_TxTask(void *i);
public void KIT_USB_Device_HID_RxTask(void *i);
public void KIT_USB_Device_HID_Init(void);
public void KIT_USB_Device_HID_Deinit(void);
public void KIT_USB_Device_HID_EventInit(void);

#endif