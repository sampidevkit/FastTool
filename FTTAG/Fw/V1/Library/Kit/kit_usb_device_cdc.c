#include "libcomp.h"
#include "kit_usb_device_cdc.h"

#ifdef WDT_H
#include "System/Wdt.h"
#endif

#ifdef RINGBUFFER_H
#include "Common/RingBuffer.h"
#endif

#ifdef TASKMANAGER_H
#include "System/TaskManager.h"
#endif

#ifdef INDICATOR_H
#include "Indicator/Indicator.h"
#endif

#ifdef USE_CDC_DEBUG
#include "Common/Debug.h"
#define debug(...)
#else
#if(0)
#include <stdio.h>

#define debug(...)   printf(__VA_ARGS__)
#else
#define debug(...)
#endif

#ifndef KIT_USB_Device_CDC_Uart_IO_Init
#define KIT_USB_Device_CDC_Uart_IO_Init()
#endif

#ifndef KIT_USB_Device_CDC_Uart_IO_Deinit
#define KIT_USB_Device_CDC_Uart_IO_Deinit()
#endif

#ifdef USE_CDC_FOWARD_TO_UART1
#define UART_Initialize()           UART1_Initialize()
#define UART_IsRxReady()            UART1_IsRxReady()
#define UART_Read()                 UART1_Read()
#define UART_IsTxReady()            UART1_IsTxReady()
#define UART_Write(Data)            UART1_Write(Data)

public void KIT_USB_Device_CDC_Uart_Enable(void) // <editor-fold defaultstate="collapsed" desc="UART enable">
{
    KIT_USB_Device_CDC_Uart_IO_Init();
    IEC1bits.U1TXIE=0;
    IEC1bits.U1RXIE=1;
    U1STASET=_U1STA_UTXEN_MASK;
    U1STASET=_U1STA_URXEN_MASK;
    U1MODESET=_U1MODE_ON_MASK;
} // </editor-fold>

public void KIT_USB_Device_CDC_Uart_Disable(void) // <editor-fold defaultstate="collapsed" desc="UART disable">
{
    U1MODECLR=_U1MODE_ON_MASK;
    U1STACLR=_U1STA_UTXEN_MASK;
    U1STACLR=_U1STA_URXEN_MASK;
    IEC1bits.U1TXIE=0;
    IEC1bits.U1RXIE=0;
    KIT_USB_Device_CDC_Uart_IO_Deinit();
} // </editor-fold>

#elif defined(USE_CDC_FOWARD_TO_UART2)
#define UART_Initialize()           UART2_Initialize()
#define UART_IsRxReady()            UART2_IsRxReady()
#define UART_Read()                 UART2_Read()
#define UART_IsTxReady()            UART2_IsTxReady()
#define UART_Write(Data)            UART2_Write(Data)

public void KIT_USB_Device_CDC_Uart_Enable(void) // <editor-fold defaultstate="collapsed" desc="UART enable">
{
    KIT_USB_Device_CDC_Uart_IO_Init();
    IEC1bits.U2TXIE=0;
    IEC1bits.U2RXIE=1;
    U2STASET=_U2STA_UTXEN_MASK;
    U2STASET=_U2STA_URXEN_MASK;
    U2MODESET=_U2MODE_ON_MASK;
} // </editor-fold>

public void KIT_USB_Device_CDC_Uart_Disable(void) // <editor-fold defaultstate="collapsed" desc="UART disable">
{
    U2MODECLR=_U2MODE_ON_MASK;
    U2STACLR=_U2STA_UTXEN_MASK;
    U2STACLR=_U2STA_URXEN_MASK;
    IEC1bits.U2TXIE=0;
    IEC1bits.U2RXIE=0;
    KIT_USB_Device_CDC_Uart_IO_Deinit();
} // </editor-fold>

#elif defined(USE_CDC_FOWARD_TO_UART3)
#define UART_Initialize()           UART3_Initialize()
#define UART_IsRxReady()            UART3_IsRxReady()
#define UART_Read()                 UART3_Read()
#define UART_IsTxReady()            UART3_IsTxReady()
#define UART_Write(Data)            UART3_Write(Data)

public void KIT_USB_Device_CDC_Uart_Enable(void) // <editor-fold defaultstate="collapsed" desc="UART enable">
{
    KIT_USB_Device_CDC_Uart_IO_Init();
    IEC1bits.U3TXIE=0;
    IEC1bits.U3RXIE=1;
    U3STASET=_U3STA_UTXEN_MASK;
    U3STASET=_U3STA_URXEN_MASK;
    U3MODESET=_U3MODE_ON_MASK;
} // </editor-fold>

public void KIT_USB_Device_CDC_Uart_Disable(void) // <editor-fold defaultstate="collapsed" desc="UART disable">
{
    U3MODECLR=_U3MODE_ON_MASK;
    U3STACLR=_U3STA_UTXEN_MASK;
    U3STACLR=_U3STA_URXEN_MASK;
    IEC1bits.U3TXIE=0;
    IEC1bits.U3RXIE=0;
    KIT_USB_Device_CDC_Uart_IO_Deinit();
} // </editor-fold>

#elif defined(USE_CDC_FOWARD_TO_UART4)
#define UART_Initialize()           UART4_Initialize()
#define UART_IsRxReady()            UART4_IsRxReady()
#define UART_Read()                 UART4_Read()
#define UART_IsTxReady()            UART4_IsTxReady()
#define UART_Write(Data)            UART4_Write(Data)

public void KIT_USB_Device_CDC_Uart_Enable(void) // <editor-fold defaultstate="collapsed" desc="UART enable">
{
    KIT_USB_Device_CDC_Uart_IO_Init();
    IEC1bits.U4TXIE=0;
    IEC1bits.U4RXIE=1;
    U4STASET=_U4STA_UTXEN_MASK;
    U4STASET=_U4STA_URXEN_MASK;
    U4MODESET=_U4MODE_ON_MASK;
} // </editor-fold>

public void KIT_USB_Device_CDC_Uart_Disable(void) // <editor-fold defaultstate="collapsed" desc="UART disable">
{
    U4MODECLR=_U4MODE_ON_MASK;
    U4STACLR=_U4STA_UTXEN_MASK;
    U4STACLR=_U4STA_URXEN_MASK;
    IEC1bits.U4TXIE=0;
    IEC1bits.U4RXIE=0;
    KIT_USB_Device_CDC_Uart_IO_Deinit();
} // </editor-fold>

#elif defined(USE_CDC_FOWARD_TO_PORT)
#define UART_Initialize()           PORT_Initialize()
#define UART_IsRxReady()            PORT_IsRxReady()
#define UART_Read()                 PORT_Read()
#define UART_IsTxReady()            PORT_IsTxReady()
#define UART_Write(Data)            PORT_Write(Data)

public void KIT_USB_Device_CDC_Uart_Enable(void) // <editor-fold defaultstate="collapsed" desc="UART enable">
{
} // </editor-fold>

public void KIT_USB_Device_CDC_Uart_Disable(void) // <editor-fold defaultstate="collapsed" desc="UART disable">
{
} // </editor-fold>

#else // USE_CDC_FOWARD_TO_SOFTWARE
#ifndef UART_Initialize
#warning "Please define UART_Initialize()"
#define UART_Initialize()           
#endif

#ifndef UART_IsRxReady
#warning "Please define UART_IsRxReady()"
#define UART_IsRxReady()            0
#endif

#ifndef UART_Read
#warning "Please define UART_Read()"
#define UART_Read()                 0
#endif

#ifndef UART_IsTxReady
#warning "Please define UART_IsTxReady()"
#define UART_IsTxReady()            0
#endif

#ifndef UART_Write
#warning "Please define UART_Write()"
#define UART_Write(Data)      
#endif

#ifndef KIT_USB_Device_CDC_Uart_Enable
#warning "Please define KIT_USB_Device_CDC_Uart_Enable()"
#define KIT_USB_Device_CDC_Uart_Enable()
#endif

#ifndef KIT_USB_Device_CDC_Uart_Disable
#warning "Please define KIT_USB_Device_CDC_Uart_Disable()"
#define KIT_USB_Device_CDC_Uart_Disable()
#endif

#endif
#endif

#ifndef USB_CDC_RXD_LedSetHigh
#define USB_CDC_RXD_LedSetHigh()
#endif

#ifndef USB_CDC_RXD_LedSetLow
#define USB_CDC_RXD_LedSetLow()
#endif

#ifndef USB_CDC_TXD_LedSetHigh
#define USB_CDC_TXD_LedSetHigh()
#endif

#ifndef USB_CDC_TXD_LedSetLow
#define USB_CDC_TXD_LedSetLow()
#endif

#ifdef USB_CDC_SUPPORT_DTR_SIGNALING

public bool UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1; // extern variable

public void mInitDTRPin(void) // defined in user_usb_device_config.h
{

}
#endif

#ifdef USB_CDC_SUPPORT_DSR_REPORTING

public bool UART_DTS=USB_CDC_DSR_ACTIVE_LEVEL^1; // extern variable

public void mInitDTSPin(void) // defined in user_usb_device_config.h
{

}
#endif

/* ********************************************************* Extern variables */
#if(!USE_CDC_FOWARD)
public ring_buf_rx_t KitUsbCdcRxBuf; // extern variable
public ring_buf_tx_t KitUsbCdcTxBuf; // extern variable
#else

typedef struct
{
    uint16_t Size;
    uint16_t Idx;
    uint8_t WrLen;
    uint8_t *pData;
} __attribute__((packed)) cdc_buffer_t;

private cdc_buffer_t KitUsbCdcRxBuf;
private cdc_buffer_t KitUsbCdcTxBuf;
#endif

private uint8_t RxData[USB_CDC_RX_BUFFER];
private uint8_t TxData[USB_CDC_TX_BUFFER];
/* ********************************************************** Local variables */

public bool UsbDeviceCDC_Init=0;
private uint8_t RxDoNext=0, TxDoNext=0;

#if defined(USB_CDC_SET_LINE_CODING_HANDLER)
// See in usb_device_config.h

void KIT_USB_Device_CDC_SetLineCodingHandler(void) // <editor-fold defaultstate="collapsed" desc="Set Line Coding">
{
#if(USE_CDC_FOWARD)
    //Update the baudrate info in the CDC driver
    CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate);
    //UART_baudrateSet(line_coding.dwDTERate); // !!!
#if !defined(USE_CDC_FOWARD_TO_SOFTWARE) && !defined(USE_CDC_FOWARD_TO_PORT)
    uint32_t BaudValue0=(SYS_CLK/(16*line_coding.dwDTERate))-1;
    uint32_t BaudValue1=(SYS_CLK/(4*line_coding.dwDTERate))-1;
#endif

    KIT_USB_Device_CDC_Uart_Disable();
    UART_Initialize();
    KIT_USB_Device_CDC_Uart_Disable();

#if(USE_CDC_FOWARD_TO_UART1)
    if(U1MODEbits.BRGH)
        U1BRG=BaudValue1;
    else
        U1BRG=BaudValue0;
#elif(USE_CDC_FOWARD_TO_UART2)
    if(U2MODEbits.BRGH)
        U2BRG=BaudValue1;
    else
        U2BRG=BaudValue0;
#elif(USE_CDC_FOWARD_TO_UART3)
    if(U3MODEbits.BRGH)
        U3BRG=BaudValue1;
    else
        U3BRG=BaudValue0;
#elif(USE_CDC_FOWARD_TO_UART4)
    if(U4MODEbits.BRGH)
        U4BRG=BaudValue1;
    else
        U4BRG=BaudValue0;
#else
    KIT_USB_Device_CDC_SetBaudrate(line_coding.dwDTERate);
#endif

    KIT_USB_Device_CDC_Uart_Enable();
#endif
} // </editor-fold>
#endif

#if(!USE_CDC_FOWARD)

public bool KIT_USB_Device_CDC_Streaming(const char c) // <editor-fold defaultstate="collapsed" desc="Be used for Prinf()">
{
    if(UsbDeviceCDC_Init==0)
        return 1;

    if(RingBuffer_IsTxReady(&KitUsbCdcTxBuf)>0)
    {
        RingBuffer_TxWrite(&KitUsbCdcTxBuf, (uint8_t) c);
        return 1;
    }
    else
        TaskManager();

    return 0;
} // </editor-fold>
#endif

public new_simple_task_t(KIT_USB_Device_CDC_TxTask) // <editor-fold defaultstate="collapsed" desc="USB CDC Tx tasks">
{
#if(!USE_CDC_FOWARD)
    static uint8_t TxCount=0;
    static uint8_t TxByte[CDC_DATA_IN_EP_SIZE];

    switch(TxDoNext)
    {
        case 0:// Init USB Tx buffer
            RingBuffer_TxInit(KitUsbCdcTxBuf, TxData, USB_CDC_TX_BUFFER);
            TxCount=0;
            TxDoNext=1;
            break;

        case 1:
            while(RingBuffer_TxRead(&KitUsbCdcTxBuf, &TxByte[TxCount]))
            {
                TxCount++;

                if(TxCount>=CDC_DATA_IN_EP_SIZE)
                    break;
            }

            if(TxCount>0)
            {
                USB_CDC_TXD_LedSetHigh();
                TxDoNext=2;
            }
            break;

        case 2:
            if(USBUSARTIsTxTrfReady())
            {
                putUSBUSART(&TxByte[0], TxCount);
                TxDoNext=3;
            }
            break;

        default:
            CDCTxService();

            if(cdc_trf_state==CDC_TX_READY)// Tx is done
            {
                USB_CDC_TXD_LedSetLow();
                TxCount=0;
                TxDoNext=1;
            }
            break;
    }
#else
    switch(TxDoNext)
    {
        case 0:
            KitUsbCdcTxBuf.Size=0;
            KitUsbCdcTxBuf.pData=TxData;
            TxDoNext=1;
            break;

        case 1:
            while(UART_IsRxReady())
            {
                KitUsbCdcTxBuf.pData[KitUsbCdcTxBuf.Size]=UART_Read();
                KitUsbCdcTxBuf.Size++;

                if(KitUsbCdcTxBuf.Size>=USB_CDC_TX_BUFFER)
                    break;
            }

            if(KitUsbCdcTxBuf.Size>0)
            {
                KitUsbCdcTxBuf.Idx=0;
                USB_CDC_TXD_LedSetHigh();
                TxDoNext=2;
            }
            break;

        case 2:
            if(USBUSARTIsTxTrfReady())
            {
                KitUsbCdcTxBuf.WrLen=(uint8_t) (KitUsbCdcTxBuf.Size%CDC_DATA_IN_EP_SIZE);
                putUSBUSART(&KitUsbCdcTxBuf.pData[KitUsbCdcTxBuf.Idx], KitUsbCdcTxBuf.WrLen);
                KitUsbCdcTxBuf.Size-=KitUsbCdcTxBuf.WrLen;
                KitUsbCdcTxBuf.Idx+=KitUsbCdcTxBuf.WrLen;
                TxDoNext=3;
            }
            break;

        default:
            CDCTxService();

            if(cdc_trf_state==CDC_TX_READY) // Tx is done
            {
                USB_CDC_TXD_LedSetLow();

                if(KitUsbCdcTxBuf.Size>0)
                    TxDoNext=2;
                else
                    TxDoNext=1;
            }
            break;
    }
#endif

__EXIT:
    Task_Done();
} // </editor-fold>

public new_simple_task_t(KIT_USB_Device_CDC_RxTask) // <editor-fold defaultstate="collapsed" desc="USB CDC Rx tasks">
{
#if(!USE_CDC_FOWARD)
    static uint8_t RxIdx=0;
    static uint8_t RxCount=0;
    static uint8_t RxByte[CDC_DATA_OUT_EP_SIZE];

    switch(RxDoNext)
    {
        case 0:// Init USB Rx buffer
            RingBuffer_RxInit(KitUsbCdcRxBuf, RxData, USB_CDC_RX_BUFFER);
            RxDoNext=1;
            break;

        case 1:
            RxCount=getsUSBUSART(&RxByte[0], CDC_DATA_OUT_EP_SIZE);

            if(RxCount>0)
            {
                USB_CDC_RXD_LedSetHigh();
                RxIdx=0;
                RxDoNext=2;
            }
            break;

        case 2:
            while(RingBuffer_RxWrite(&KitUsbCdcRxBuf, RxByte[RxIdx])==0)
            {
                RxIdx++;

                if(RxIdx==RxCount)
                {
                    USB_CDC_RXD_LedSetLow();
                    RxDoNext=1;
                    break;
                }
            }
            break;

        default:
            break;
    }
#else
    switch(RxDoNext)
    {
        case 0:
            RxDoNext=1;
            KitUsbCdcRxBuf.pData=RxData;
            break;

        case 1:
            KitUsbCdcRxBuf.Size=getsUSBUSART(&KitUsbCdcRxBuf.pData[0], CDC_DATA_OUT_EP_SIZE);

            if(KitUsbCdcRxBuf.Size>0)
            {
                USB_CDC_RXD_LedSetHigh();
                KitUsbCdcRxBuf.Idx=0;
                RxDoNext=2;
            }
            break;

        default:
            while(UART_IsTxReady())
            {
                UART_Write(KitUsbCdcRxBuf.pData[KitUsbCdcRxBuf.Idx]);
                KitUsbCdcRxBuf.Idx++;

                if(KitUsbCdcRxBuf.Idx==KitUsbCdcRxBuf.Size)
                {
                    USB_CDC_RXD_LedSetLow();
                    RxDoNext=1;
                    break;
                }
            }
            break;
    }
#endif

    Task_Done();
} // </editor-fold>

public void KIT_USB_Device_CDC_Init(void) // <editor-fold defaultstate="collapsed" desc="USB CDC initialize">
{
    if(UsbDeviceCDC_Init==0)
    {
        USB_CDC_RXD_LedSetLow();
        USB_CDC_TXD_LedSetLow();

        if(UART_DTR)
        {
            UsbDeviceCDC_Init=1;
            RxDoNext=0;
            TxDoNext=0;

#ifdef USE_CDC_DEBUG
            Debug_SetStreamFnc(KIT_USB_Device_CDC_Streaming);
#endif
            TaskManager_Create_NewSimpleTask(KIT_USB_Device_CDC_RxTask);
            TaskManager_Create_NewSimpleTask(KIT_USB_Device_CDC_TxTask);
            KIT_USB_Device_CDC_InitCb();
            debug("\nPort opened");
        }
    }
} // </editor-fold>

public void KIT_USB_Device_CDC_Deinit(void) // <editor-fold defaultstate="collapsed" desc="USB CDC Deinitialize">
{
    if(UsbDeviceCDC_Init==1)
    {
#ifdef USE_CDC_DEBUG
        Debug_SetStreamFnc(NULL);
#endif
        USB_CDC_RXD_LedSetLow();
        USB_CDC_TXD_LedSetLow();
        TaskManager_End_Task(KIT_USB_Device_CDC_RxTask);
        TaskManager_End_Task(KIT_USB_Device_CDC_TxTask);
        KIT_USB_Device_CDC_DeInitCb();
#if(!USE_CDC_FOWARD)
        RingBuffer_TxDeinit(&KitUsbCdcTxBuf);
        RingBuffer_RxDeinit(&KitUsbCdcRxBuf);
#endif
        UsbDeviceCDC_Init=0;
#ifdef USB_CDC_SUPPORT_DTR_SIGNALING
        UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1;
#endif
        USB_CDC_TXD_LedSetLow();
        USB_CDC_RXD_LedSetLow();
        debug("\nPort closed");
    }
} // </editor-fold>

public void KIT_USB_Device_CDC_EventInit(void) // <editor-fold defaultstate="collapsed" desc="CDC event intialize">
{
    CDCInitEP();
    line_coding.bCharFormat=0;
    line_coding.bDataBits=8;
    line_coding.bParityType=0;
    line_coding.dwDTERate=9600;
} // </editor-fold>