#include "VCP.h"
#include "VCP_ATC.h"
#include "Common/RingBuffer.h"
#include "System/TaskManager.h"

private uint8_t i, CdcPortIdx=0;
private port_txbuf_t VcpAtcTxBuf={.next=0};
private port_rxbuf_t VcpAtcRxBuf;

private ring_buf_rx_t RxBuf;
private ring_buf_tx_t TxBuf;
private uint8_t RxSrc[256];
private uint8_t TxSrc[256];

private void VCP_ATC_Enable(uint32_t dwDTERate) // <editor-fold defaultstate="collapsed" desc="CELL UART enable">
{
    RingBuffer_RxInit(RxBuf, RxSrc, sizeof (RxSrc));
    RingBuffer_TxInit(TxBuf, TxSrc, sizeof (TxSrc));
} // </editor-fold>

private void VCP_ATC_Disable(void) // <editor-fold defaultstate="collapsed" desc="CELL UART disable">
{

} // </editor-fold>

private void LineCodingHandler(void) // <editor-fold defaultstate="collapsed" desc="Line coding handler">
{
    //Update the baudrate info in the CDC driver
    CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate);
    VCP_ATC_Disable();
    VCP_ATC_Enable(cdc_notice.GetLineCoding.dwDTERate);
} // </editor-fold>

private void DTRPinHandler(char logic) // <editor-fold defaultstate="collapsed" desc="DTR pin handler">
{
    if(logic==USB_CDC_DTR_ACTIVE_LEVEL)
        VcpAtcTxBuf.ready=1;
    else
        VcpAtcTxBuf.ready=0;
} // </editor-fold>

public bool VCP_ATC_IsTxReady(void) // <editor-fold defaultstate="collapsed" desc="UART is TX ready">
{
    if(VcpAtcTxBuf.ready)
        return (RingBuffer_IsTxReady(&TxBuf)>0);

    return 1;
} // </editor-fold>

public bool VCP_ATC_IsTxDone(void) // <editor-fold defaultstate="collapsed" desc="UART is TX done">
{
    if(VcpAtcTxBuf.ready)
        return (RingBuffer_IsTxReady(&TxBuf)==sizeof (TxSrc));

    return 1;
} // </editor-fold>

public bool VCP_ATC_IsRxReady(void) // <editor-fold defaultstate="collapsed" desc="UART is RX ready">
{
    if(VcpAtcTxBuf.ready)
        return (RingBuffer_IsRxReady(&RxBuf)>0);

    return 0;
} // </editor-fold>

public uint8_t VCP_ATC_Read(void) // <editor-fold defaultstate="collapsed" desc="UART reads 1 byte">
{
    return RingBuffer_RxRead(&RxBuf);
} // </editor-fold>

public void VCP_ATC_Write(uint8_t c) // <editor-fold defaultstate="collapsed" desc="UART writes 1 byte">
{
    RingBuffer_TxWrite(&TxBuf, c);
} // </editor-fold>

private new_simple_task_t(VCP_ATC_Tasks) // <editor-fold defaultstate="collapsed" desc="VCP ATC Tasks">
{
    if((USBGetDeviceState()<CONFIGURED_STATE)||(USBIsDeviceSuspended()==true))
        Task_Break();

    if(VcpAtcTxBuf.ready)
    {
        // USB VCP to UART
        VcpAtcRxBuf.len=getsUSBUSART(CdcPortIdx, VcpAtcRxBuf.buf, CDC_DATA_OUT_EP_SIZE);

        for(i=0; i<VcpAtcRxBuf.len; i++)
        {
            RingBuffer_RxWrite(&RxBuf, VcpAtcRxBuf.buf[i]);
        }
        // UART to USB VCP
        switch(VcpAtcTxBuf.next)
        {
            case 0: // Get TX data from buffer
                i=0;

                while(RingBuffer_TxRead(&TxBuf, &VcpAtcTxBuf.buf[i]))
                {
                    if(++i>=CDC_DATA_IN_EP_SIZE)
                        break;
                }

                if(i>0)
                {
                    VcpAtcTxBuf.len=i;
                    VcpAtcTxBuf.next=1;
                }
                else
                    break;

            case 1: // Put TX data
                if(USBUSARTIsTxTrfReady(CdcPortIdx))
                {
                    VcpAtcTxBuf.next=2;
                    putUSBUSART(CdcPortIdx, VcpAtcTxBuf.buf, VcpAtcTxBuf.len);
                }
                break;

            default: // Waiting for TX done
                CDCTxService(CdcPortIdx);

                if(USBUSARTIsTxTrfReady(CdcPortIdx)||(VcpAtcTxBuf.ready==0)) // check TX state again
                    VcpAtcTxBuf.next=0;
                break;
        }
    }
    else
    {
        Tick_Timer_Reset(VcpAtcTxBuf.tk);
        VcpAtcTxBuf.next=0;
    }

    Task_Done();
} // </editor-fold>

public void VCP_ATC_Init(uint8_t PortIdx) // <editor-fold defaultstate="collapsed" desc="Init">
{
    RingBuffer_RxInit(RxBuf, RxSrc, sizeof (RxSrc));
    RingBuffer_TxInit(TxBuf, TxSrc, sizeof (TxSrc));

    CdcPortIdx=PortIdx;
    VcpAtcTxBuf.next=0;
    USB_CDC_SetLineCodingHandler(CdcPortIdx, LineCodingHandler);
    DTRPin_SetHandler(CdcPortIdx, DTRPinHandler);
    TaskManager_Create_NewSimpleTask(VCP_ATC_Tasks); // Cellular AT command
} // </editor-fold>
