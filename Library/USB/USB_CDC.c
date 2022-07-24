#include "USB_CDC.h"
#include "libcomp.h"

#define DTR_LED_SetHigh()   (LATBSET=(1<<13))
#define DTR_LED_SetLow()    (LATBCLR=(1<<13))

#undef RX_LED_SetHigh
#define RX_LED_SetHigh()

#undef RX_LED_SetLow
#define RX_LED_SetLow()

char UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1; // extern variable loacted in usb_device_config.h

static uint8_t txBuf[CDC_DATA_OUT_EP_SIZE]={0x00};
static uint8_t txLen=0;
static uint8_t rxBuf[CDC_DATA_IN_EP_SIZE];
static uint8_t rxLen=0;

void mInitDTRPin(void) // defined in user_usb_device_config.h
{
    DTR_LED_SetLow();
    UART_DTR=USB_CDC_DTR_ACTIVE_LEVEL^1;
}

void USB_CDC_SetLineCodingHandler(void)
{

}

static inline bool USB_CDC_Is_Busy(void) // <editor-fold defaultstate="collapsed" desc="Get USB CDC state">
{
    if((USBGetDeviceState()<CONFIGURED_STATE)||(USBIsDeviceSuspended()==true)||(UART_DTR!=USB_CDC_DTR_ACTIVE_LEVEL))
    {
        RX_LED_SetLow();
        TX_LED_SetLow();
        DTR_LED_SetLow();
        return 1;
    }
    else
        DTR_LED_SetHigh();

    return 0;
} // </editor-fold>

void USB_CDC_Tasks(void) // <editor-fold defaultstate="collapsed" desc="USB CDC Tx tasks">
{
    if(USB_CDC_Is_Busy())
        return;

    rxLen=getsUSBUSART(rxBuf, CDC_DATA_IN_EP_SIZE);

    if(rxLen>0)
    {
        RX_LED_SetHigh();
        putUSBUSART(rxBuf, rxLen);
    }
    else
        RX_LED_SetLow();

    if(txLen>0)
    {
        TX_LED_SetHigh();
        putUSBUSART(txBuf, txLen);
        txLen=0;
    }
    else
        TX_LED_SetLow();

    while(!USBUSARTIsTxTrfReady())
        CDCTxService();
} // </editor-fold>

void _mon_putc(char c) // <editor-fold defaultstate="collapsed" desc="SDTIO stream function">
{
    if(USB_CDC_Is_Busy())
        return;

    txBuf[txLen++]=c;

    if(txLen>=CDC_DATA_IN_EP_SIZE)
    {
        txLen=0;
        TX_LED_SetHigh();
        putUSBUSART(txBuf, CDC_DATA_IN_EP_SIZE);
    }

    while(!USBUSARTIsTxTrfReady())
        CDCTxService();
} // </editor-fold>

bool USB_CDC_Is_RxReady(void)
{
    return 0;
}

bool USB_CDC_Is_TxReady(void)
{
    return 0;
}

bool USB_CDC_Is_TxDone(void)
{
    return 0;
}

void USB_CDC_Write(uint8_t c)
{

}

uint8_t USB_CDC_Read(void)
{
    return 0;
}