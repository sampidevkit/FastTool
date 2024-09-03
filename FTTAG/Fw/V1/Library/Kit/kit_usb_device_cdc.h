#ifndef KIT_USB_DEVICE_CDC_H
#define KIT_USB_DEVICE_CDC_H

#include "Common/LibDef.h"
#include "Common/RingBuffer.h"
#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_usb_device_cfg.h"
#endif

#define USE_CDC_FOWARD ((USE_CDC_FOWARD_TO_UART1)||(USE_CDC_FOWARD_TO_UART2)|| \
(USE_CDC_FOWARD_TO_UART3)||(USE_CDC_FOWARD_TO_UART4)||(USE_CDC_FOWARD_TO_PORT))|| \
(USE_CDC_FOWARD_TO_SOFTWARE)

#ifndef USB_CDC_TX_BUFFER
#define USB_CDC_TX_BUFFER   128
#endif

#ifndef USB_CDC_RX_BUFFER
#define USB_CDC_RX_BUFFER   128
#endif

#ifndef KIT_USB_Device_CDC_InitCb
#define KIT_USB_Device_CDC_InitCb()
#endif

#ifndef KIT_USB_Device_CDC_DeInitCb
#define KIT_USB_Device_CDC_DeInitCb()
#endif

#if(!USE_CDC_FOWARD)
extern ring_buf_rx_t KitUsbCdcRxBuf;
extern ring_buf_tx_t KitUsbCdcTxBuf;

#define KIT_USB_Device_CDC_IsRxReady()      RingBuffer_IsRxReady(&KitUsbCdcRxBuf)
#define KIT_USB_Device_CDC_ReadByte()     	RingBuffer_RxRead(&KitUsbCdcRxBuf)
#define KIT_USB_Device_CDC_WriteByte(Data)  Ringbuffer_TxWrite(&KitUsbCdcTxBuf, Data)
#define KIT_USB_Device_CDC_IsTxDone()       (RingBuffer_IsTxReady(&KitUsbCdcTxBuf)==USB_CDC_TX_BUFFER)
#endif

extern bool UsbDeviceCDC_Init;

#ifndef KIT_USB_Device_CDC_Uart_Enable
public void KIT_USB_Device_CDC_Uart_Enable(void);
#endif

#ifndef KIT_USB_Device_CDC_Uart_Disable
public void KIT_USB_Device_CDC_Uart_Disable(void);
#endif

public bool KIT_USB_Device_CDC_Streaming(const char c);
public void KIT_USB_Device_CDC_TxTask(void *);
public void KIT_USB_Device_CDC_RxTask(void *);
public void KIT_USB_Device_CDC_Init(void);
public void KIT_USB_Device_CDC_Deinit(void);
public void KIT_USB_Device_CDC_EventInit(void);

#endif