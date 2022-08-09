#include "USB_CDC_UART.h"
#include "libcomp.h"

#ifndef DTR_LED_SetHigh
#define DTR_LED_SetHigh()
#endif

#ifndef DTR_LED_SetLow
#define DTR_LED_SetLow()
#endif

#ifndef RX_LED_SetHigh
#define RX_LED_SetHigh()
#endif

#ifndef RX_LED_SetLow
#define RX_LED_SetLow()
#endif

#ifndef TX_LED_SetHigh
#define TX_LED_SetHigh()
#endif

#ifndef TX_LED_SetLow
#define TX_LED_SetLow()
#endif

static bool __init=0;
static uint8_t __len;
static uint8_t __data[CDC_DATA_OUT_EP_SIZE];

char UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1; // extern variable loacted in usb_device_config.h

void mInitDTRPin(void) // <editor-fold defaultstate="collapsed" desc="DTR initialize, defined in usb_device_config.h">
{
    DTR_LED_SetLow();
    UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1;
} // </editor-fold>

void USB_CDC_SetLineCodingHandler(void) // <editor-fold defaultstate="collapsed" desc="Baudrate configure, defined in usb_device_config.h">
{
    if(line_coding.dwDTERate!=cdc_notice.GetLineCoding.dwDTERate)
    {
        //Update the baud rate info in the CDC driver
        CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate);
        UART2_Initialize();
        U2MODECLR=_U2MODE_ON_MASK;
        U2STACLR=_U2STA_UTXEN_MASK;
        U2STACLR=_U2STA_URXEN_MASK;
        IEC1bits.U2TXIE=0;
        IEC1bits.U2RXIE=0;

        if(U2MODEbits.BRGH)
            U2BRG=(_XTAL_FREQ/(4*line_coding.dwDTERate))-1;
        else
            U2BRG=(_XTAL_FREQ/(16*line_coding.dwDTERate))-1;

        IEC1bits.U2TXIE=0;
        IEC1bits.U2RXIE=1;
        U2STASET=_U2STA_UTXEN_MASK;
        U2STASET=_U2STA_URXEN_MASK;
        U2MODESET=_U2MODE_ON_MASK;
    }
} // </editor-fold>

static inline bool USB_CDC_UART_Is_Ready(void) // <editor-fold defaultstate="collapsed" desc="Get USB CDC state">
{
    static bool Is_Init=0;

    if((USBGetDeviceState()<CONFIGURED_STATE)||(USBIsDeviceSuspended()==true)||(UART_DTR!=USB_CDC_DTR_ACTIVE_LEVEL))
    {
        if(Is_Init==1)
        {
            Is_Init=0;
            U2MODECLR=_U2MODE_ON_MASK;
            U2STACLR=_U2STA_UTXEN_MASK;
            U2STACLR=_U2STA_URXEN_MASK;
            IEC1bits.U2TXIE=0;
            IEC1bits.U2RXIE=0;
            RX_LED_SetLow();
            TX_LED_SetLow();
            DTR_LED_SetLow();
        }
    }
    else if(Is_Init==0)
    {
        Is_Init=1;
        IEC1bits.U2TXIE=0;
        IEC1bits.U2RXIE=1;
        U2STASET=_U2STA_UTXEN_MASK;
        U2STASET=_U2STA_URXEN_MASK;
        U2MODESET=_U2MODE_ON_MASK;
        DTR_LED_SetHigh();
    }

    return Is_Init;
} // </editor-fold>

static inline void USB_CDC_UART_Rx_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Rx tasks">
{
    if(!USBHandleBusy(CDCDataOutHandle))
    {
        RX_LED_SetHigh();
        __len=CDC_DATA_IN_EP_SIZE;

        if(__len>USBHandleGetLength(CDCDataOutHandle))
            __len=USBHandleGetLength(CDCDataOutHandle);

        for(cdc_rx_len=0; cdc_rx_len<__len; cdc_rx_len++)
        {
            while(!UART2_IsTxReady());
            UART2_Write(cdc_data_rx[cdc_rx_len]);
        }

        CDCDataOutHandle=USBRxOnePacket(CDC_DATA_EP, (uint8_t*)&cdc_data_rx, sizeof (cdc_data_rx));
    }
} // </editor-fold>

static inline void USB_CDC_UART_Tx_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Tx tasks">
{
    __len=0;

    while(UART2_IsRxReady())
    {
        TX_LED_SetHigh();
        __data[__len++]=UART2_Read();

        if(__len==CDC_DATA_OUT_EP_SIZE)
            break;
    }

    USBMaskInterrupts();

    if(cdc_trf_state==CDC_TX_READY)
    {
        mUSBUSARTTxRam(__data, __len); // See cdc.h
    }

    USBUnmaskInterrupts();

    while(!USBUSARTIsTxTrfReady())
    {
        CDCTxService();

        if(!USB_CDC_UART_Is_Ready())
            break;
    }
} // </editor-fold>

void USB_CDC_UART_Tasks(void) // <editor-fold defaultstate="collapsed" desc="USB CDC Tx tasks">
{
    if(__init==0)
    {
        __init=1;
        USB_Device_LoadUDID();
    }

    if(USB_CDC_UART_Is_Ready())
    {
        USB_CDC_UART_Rx_Tasks();
        USB_CDC_UART_Tx_Tasks();
    }

    if(RX_LED_GetValue()&&(!UART2_IsRxReady()))
        RX_LED_SetLow();

    if(TX_LED_GetValue()&&USBUSARTIsTxTrfReady())
        TX_LED_SetLow();
} // </editor-fold>