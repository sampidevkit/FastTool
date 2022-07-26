#include "USB_CDC_Debug.h"
#include "libcomp.h"

#define DTR_LED_SetHigh()   //(LATBSET=(1<<13))
#define DTR_LED_SetLow()    //(LATBCLR=(1<<13))

//#undef RX_LED_SetHigh
//#define RX_LED_SetHigh()
//
//#undef RX_LED_SetLow
//#define RX_LED_SetLow()

static struct
{
    uint8_t head;
    uint8_t tail;
    uint8_t count;
    uint8_t data[CDC_DATA_IN_EP_SIZE];
} rxBuf;

static struct
{
    uint8_t head;
    uint8_t tail;
    uint8_t remain;
    uint8_t data[CDC_DATA_OUT_EP_SIZE];
} txBuf;

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

} // </editor-fold>

static inline bool USB_CDC_Debug_Is_Ready(void) // <editor-fold defaultstate="collapsed" desc="Get USB CDC state">
{
    static bool Is_Init=0;

    if((USBGetDeviceState()<CONFIGURED_STATE)||(USBIsDeviceSuspended()==true)||(UART_DTR!=USB_CDC_DTR_ACTIVE_LEVEL))
    {
        if(Is_Init==1)
        {
            Is_Init=0;
            rxBuf.count=0;
            txBuf.remain=0;
            RX_LED_SetLow();
            TX_LED_SetLow();
            DTR_LED_SetLow();
        }
    }
    else if(Is_Init==0)
    {
        Is_Init=1;
        rxBuf.head=rxBuf.tail=rxBuf.count=0;
        txBuf.head=txBuf.tail=0;
        txBuf.remain=CDC_DATA_OUT_EP_SIZE;
        DTR_LED_SetHigh();
    }

    return Is_Init;
} // </editor-fold>

static inline void USB_CDC_Debug_Rx_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Rx tasks">
{
    if(!USBHandleBusy(CDCDataOutHandle))
    {
        RX_LED_SetHigh();
        __len=CDC_DATA_IN_EP_SIZE;

        if(__len>USBHandleGetLength(CDCDataOutHandle))
            __len=USBHandleGetLength(CDCDataOutHandle);

        for(cdc_rx_len=0; cdc_rx_len<__len; cdc_rx_len++)
        {
            rxBuf.data[rxBuf.head++]=cdc_data_rx[cdc_rx_len];

            if(CDC_DATA_IN_EP_SIZE<=rxBuf.head)
                rxBuf.head=0;

            if(CDC_DATA_IN_EP_SIZE>rxBuf.count)
                rxBuf.count++;
        }

        CDCDataOutHandle=USBRxOnePacket(CDC_DATA_EP, (uint8_t*)&cdc_data_rx, sizeof (cdc_data_rx));
    }
} // </editor-fold>

static inline void USB_CDC_Debug_Tx_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Tx tasks">
{
    __len=0;

    while(CDC_DATA_OUT_EP_SIZE>txBuf.remain)
    {
        __data[__len++]=txBuf.data[txBuf.tail++];

        if(CDC_DATA_OUT_EP_SIZE<=txBuf.tail)
            txBuf.tail=0;

        txBuf.remain++;
    }

    USBMaskInterrupts();

    if(cdc_trf_state==CDC_TX_READY)
    {
        mUSBUSARTTxRam(__data, __len); // See cdc.h
    }

    USBUnmaskInterrupts();

    while(!USBUSARTIsTxTrfReady())
        CDCTxService();
} // </editor-fold>

void USB_CDC_Debug_Tasks(void) // <editor-fold defaultstate="collapsed" desc="USB CDC Tx tasks">
{
    if(USB_CDC_Debug_Is_Ready())
    {
        USB_CDC_Debug_Rx_Tasks();
        USB_CDC_Debug_Tx_Tasks();
    }

    if(RX_LED_GetValue()&&(rxBuf.count==0))
        RX_LED_SetLow();

    if(TX_LED_GetValue()&&(txBuf.remain>=CDC_DATA_OUT_EP_SIZE))
        TX_LED_SetLow();
} // </editor-fold>

void _mon_putc(char c) // <editor-fold defaultstate="collapsed" desc="SDTIO stream function">
{
    if(txBuf.remain==0)
    {
        if(!USB_CDC_Debug_Is_Ready())
            return;

        USB_CDC_Debug_Tx_Tasks();
    }

    TX_LED_SetHigh();
    txBuf.data[txBuf.head++]=c;

    if(CDC_DATA_OUT_EP_SIZE<=txBuf.head)
        txBuf.head=0;

    if(txBuf.remain>0)
        txBuf.remain--;
} // </editor-fold>

bool USB_CDC_Debug_Is_RxReady(void)
{
    return (rxBuf.count>0?1:0);
}

bool USB_CDC_Debug_Is_TxReady(void)
{
    return (txBuf.remain>0?1:0);
}

bool USB_CDC_Debug_Is_TxDone(void)
{
    return (txBuf.remain==CDC_DATA_OUT_EP_SIZE?1:0);
}

void USB_CDC_Debug_Write(uint8_t c)
{
    if(txBuf.remain==0)
        return;

    TX_LED_SetHigh();
    txBuf.data[txBuf.head++]=c;

    if(CDC_DATA_OUT_EP_SIZE<=txBuf.head)
        txBuf.head=0;

    if(txBuf.remain>0)
        txBuf.remain--;
}

uint8_t USB_CDC_Debug_Read(void)
{
    uint8_t readValue=rxBuf.data[rxBuf.tail++];

    if(CDC_DATA_IN_EP_SIZE<=rxBuf.tail)
        rxBuf.tail=0;

    if(rxBuf.count>0)
        rxBuf.count--;

    return readValue;
}