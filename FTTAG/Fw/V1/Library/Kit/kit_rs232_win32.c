#include <stdio.h>
#include <string.h>
#include "kit_rs232_win32.h"
#include "Common/RingBuffer.h"
#include "System/TaskManager.h"

#define __console(...)  //printf(__VA_ARGS__)

typedef struct
{
    HANDLE Handler;
    ring_buf_rx_t RxBuffer;
    ring_buf_tx_t TxBuffer;
    char PortName[16];
    uint8_t Para[128];
} rs232_cfg_t;

typedef struct
{
    uint8_t TxData[KIT_RS232_TX_BUFF_SIZE];
    uint8_t RxData[KIT_RS232_RX_BUFF_SIZE];
} rs232_buf_t;

private const int SupportedBaudrate[19]={
    110, 300, 600, 1200, 2400, 4800, 9600, 19200,
    38400, 57600, 115200, 128000, 25600, 500000,
    921600, 1000000, 1500000, 2000000, 3000000
};

private uint8_t InitNext=0;
private uint8_t PortTrans1, PortTrans2;
private rs232_cfg_t Rs232Cfg[NUM_OF_RS232_PORT];
private rs232_buf_t Rs232Buf[NUM_OF_RS232_PORT];

private rs232_cxt_t Rs232Cxt[NUM_OF_RS232_PORT]=// <editor-fold defaultstate="collapsed" desc="RS232 port context">
{
    {
        .Port=KIT_RS232_PORT1,
        .Baud=KIT_RS232_BAUD1,
        .DataBit=8,
        .Parity='N',
        .StopBit=0,
        .FlowCtrl='N',
    }

#if(NUM_OF_RS232_PORT>=2)
    ,
    {
        .Port=KIT_RS232_PORT2,
        .Baud=KIT_RS232_BAUD2,
        .DataBit=8,
        .Parity='N',
        .StopBit=0,
        .FlowCtrl='N',
    }
#endif

#if(NUM_OF_RS232_PORT>=3)
    ,
    {
        .Port=KIT_RS232_PORT3,
        .Baud=KIT_RS232_BAUD3,
        .DataBit=8,
        .Parity='N',
        .StopBit=0,
        .FlowCtrl='N',
    }
#endif
}; // </editor-fold>

public new_simple_task_t(KIT_RS232_Tasks1) // <editor-fold defaultstate="collapsed" desc="RS232 tasks">
{
#define __IXD__ 0
    uint8_t c;
    int n, m, i;
    static uint8_t tmpbuf[4096];

    // Write data to serial port
    while(RingBuffer_TxRead(&Rs232Cfg[__IXD__].TxBuffer, &c))
    {
        // __console("\nWrite %c", c);
        WriteFile(Rs232Cfg[__IXD__].Handler, &c, 1, (LPDWORD) ((void *) &m), NULL);
    }

    // Read data from serial port
    ReadFile(Rs232Cfg[__IXD__].Handler, &tmpbuf[0], sizeof (tmpbuf), (LPDWORD) ((void *) &n), NULL);

    if(n>0)
    {
        i=0;

        while(i!=n)
        {
            if(RingBuffer_RxWrite(&Rs232Cfg[__IXD__].RxBuffer, tmpbuf[i])==0)
            {
                // __console("\nRead %c", tmpbuf[i]);
                i++;
            }
        }

        // __console("\n2");
    }

    Task_Done();
#undef __IXD__
} // </editor-fold>

#if(NUM_OF_RS232_PORT>=2)

public new_simple_task_t(KIT_RS232_Tasks2) // <editor-fold defaultstate="collapsed" desc="RS232 tasks">
{
#define __IXD__ 1
    uint8_t c;
    int n, m, i;
    static uint8_t tmpbuf[4096];

    // Write data to serial port
    while(RingBuffer_TxRead(&Rs232Cfg[__IXD__].TxBuffer, &c))
    {
        // __console("\nWrite %c", c);
        WriteFile(Rs232Cfg[__IXD__].Handler, &c, 1, (LPDWORD) ((void *) &m), NULL);
    }

    // Read data from serial port
    ReadFile(Rs232Cfg[__IXD__].Handler, &tmpbuf[0], sizeof (tmpbuf), (LPDWORD) ((void *) &n), NULL);

    if(n>0)
    {
        i=0;

        while(i!=n)
        {
            if(RingBuffer_RxWrite(&Rs232Cfg[__IXD__].RxBuffer, tmpbuf[i])==0)
            {
                // __console("\nRead %c", tmpbuf[i]);
                i++;
            }
        }

        // __console("\n2");
    }

    Task_Done();
#undef __IXD__
} // </editor-fold>
#endif

#if(NUM_OF_RS232_PORT>=3)

public new_simple_task_t(KIT_RS232_Tasks3) // <editor-fold defaultstate="collapsed" desc="RS232 tasks">
{
#define __IXD__ 2
    uint8_t c;
    int n, m, i;
    static uint8_t tmpbuf[4096];

    // Write data to serial port
    while(RingBuffer_TxRead(&Rs232Cfg[__IXD__].TxBuffer, &c))
    {
        // __console("\nWrite %c", c);
        WriteFile(Rs232Cfg[__IXD__].Handler, &c, 1, (LPDWORD) ((void *) &m), NULL);
    }

    // Read data from serial port
    ReadFile(Rs232Cfg[__IXD__].Handler, &tmpbuf[0], sizeof (tmpbuf), (LPDWORD) ((void *) &n), NULL);

    if(n>0)
    {
        i=0;

        while(i!=n)
        {
            if(RingBuffer_RxWrite(&Rs232Cfg[__IXD__].RxBuffer, tmpbuf[i])==0)
            {
                // __console("\nRead %c", tmpbuf[i]);
                i++;
            }
        }

        // __console("\n2");
    }

    Task_Done();
#undef __IXD__
} // </editor-fold>
#endif

public bool KIT_RS232_IsRxReady(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="RS232 is RX ready">
{
    if(RingBuffer_IsRxReady(&Rs232Cfg[portIdx].RxBuffer)>0)
        return 1;

    return 0;
} // </editor-fold>

public bool KIT_RS232_IsTxReady(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="RS232 is TX ready">
{
    if(RingBuffer_IsTxReady(&Rs232Cfg[portIdx].TxBuffer))
        return 1;

    return 0;
} // </editor-fold>

public void KIT_RS232_WriteByte(uint8_t portIdx, uint8_t c) // <editor-fold defaultstate="collapsed" desc="RS232 write 1 byte">
{
    while(!RingBuffer_TxWrite(&Rs232Cfg[portIdx].TxBuffer, c));
} // </editor-fold>

public uint8_t KIT_RS232_ReadByte(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="RS232 read 1 byte">
{
    return RingBuffer_RxRead(&Rs232Cfg[portIdx].RxBuffer);
} // </editor-fold>

public bool KIT_RS232_IsDCDEnabled(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="DCD enable">
{
    int status;

    GetCommModemStatus(Rs232Cfg[portIdx].Handler, (LPDWORD) ((void *) &status));

    if(status&MS_RLSD_ON)
        return (1);

    return (0);
} // </editor-fold>

public bool KIT_RS232_IsRINGEnabled(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Get ring enable state">
{
    int status;

    GetCommModemStatus(Rs232Cfg[portIdx].Handler, (LPDWORD) ((void *) &status));

    if(status&MS_RING_ON)
        return (1);

    return (0);
} // </editor-fold>

public bool KIT_RS232_IsCTSEnabled(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Get CTS enable state">
{
    int status;

    GetCommModemStatus(Rs232Cfg[portIdx].Handler, (LPDWORD) ((void *) &status));

    if(status&MS_CTS_ON)
        return (1);

    return (0);
} // </editor-fold>

public bool KIT_RS232_IsDSREnabled(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Get DSR state enable">
{
    int status;

    GetCommModemStatus(Rs232Cfg[portIdx].Handler, (LPDWORD) ((void *) &status));

    if(status&MS_DSR_ON)
        return (1);

    return (0);
} // </editor-fold>

public void KIT_RS232_EnableDTR(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Enable DTR">
{
    EscapeCommFunction(Rs232Cfg[portIdx].Handler, SETDTR);
} // </editor-fold>

public void KIT_RS232_DisableDTR(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Disable DTR">
{
    EscapeCommFunction(Rs232Cfg[portIdx].Handler, CLRDTR);
} // </editor-fold>

public void KIT_RS232_EnableRTS(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Enable RTS">
{
    EscapeCommFunction(Rs232Cfg[portIdx].Handler, SETRTS);
} // </editor-fold>

public void KIT_RS232_DisableRTS(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Disable RTS">
{
    EscapeCommFunction(Rs232Cfg[portIdx].Handler, CLRRTS);
} // </editor-fold>

public void KIT_RS232_FlushRX(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="flush RX">
{
    PurgeComm(Rs232Cfg[portIdx].Handler, PURGE_RXCLEAR|PURGE_RXABORT);
} // </editor-fold>

public void KIT_RS232_FlushTX(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Flush TX">
{
    PurgeComm(Rs232Cfg[portIdx].Handler, PURGE_TXCLEAR|PURGE_TXABORT);
} // </editor-fold>

public void KIT_RS232_FlushRXTX(uint8_t portIdx) // <editor-fold defaultstate="collapsed" desc="Flush RXTX">
{
    PurgeComm(Rs232Cfg[portIdx].Handler, PURGE_RXCLEAR|PURGE_RXABORT);
    PurgeComm(Rs232Cfg[portIdx].Handler, PURGE_TXCLEAR|PURGE_TXABORT);
} // </editor-fold>

private rs232_state_t KIT_RS232_Initialize1(void) // <editor-fold defaultstate="collapsed" desc="RS232 initialize">
{
#define __IDX__ 0
    int i;
    DCB port_settings;
    COMMTIMEOUTS Cptimeouts;

    __console("\nPORT %d CONFIGURATION:\n", __IDX__);

    if((Rs232Cxt[__IDX__].Port<1)||(Rs232Cxt[__IDX__].Port>255))
    {
        __console("\nPort value is between 1 & 255");
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].PortName[0], "\\\\.\\COM%d", Rs232Cxt[__IDX__].Port);

    for(i=0; i<sizeof (SupportedBaudrate); i++)
    {
        if(Rs232Cxt[__IDX__].Baud==SupportedBaudrate[i])
            break;
    }

    if(i>=sizeof (SupportedBaudrate))
    {
        __console("\nBaud rate %d is not supported", Rs232Cxt[__IDX__].Baud);
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].Para[0], "baud=%d ", Rs232Cxt[__IDX__].Baud);

    switch(Rs232Cxt[__IDX__].DataBit)
    {
        case 5:
            strcat(Rs232Cfg[__IDX__].Para, "data=5 ");
            break;

        case 6:
            strcat(Rs232Cfg[__IDX__].Para, "data=6 ");
            break;

        case 7:
            strcat(Rs232Cfg[__IDX__].Para, "data=7 ");
            break;

        case 8:
            strcat(Rs232Cfg[__IDX__].Para, "data=8 ");
            break;

        default:
            __console("\nData bit value is between 5 & 8");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].Parity)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "parity=n ");
            break;

        case 'O':
        case 'o':
            strcat(Rs232Cfg[__IDX__].Para, "parity=o ");
            break;

        case 'E':
        case 'e':
            strcat(Rs232Cfg[__IDX__].Para, "parity=e ");
            break;

        case 'M':
        case 'm':
            strcat(Rs232Cfg[__IDX__].Para, "parity=m ");
            break;

        case 'S':
        case 's':
            strcat(Rs232Cfg[__IDX__].Para, "parity=s ");
            break;

        default:
            __console("\nParity value is 'N', 'O', 'E', 'M' or 'S'");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].StopBit)
    {
        case 0:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1 ");
            break;

        case 1:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1.5 ");
            break;

        case 2:
            strcat(Rs232Cfg[__IDX__].Para, "stop=2 ");
            break;

        default:
            __console("\nParity value is 0=1bit, 1=1.5bit, or 2=2bits");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].FlowCtrl)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=on");
            break;

        case 'X':
        case 'x':
            strcat(Rs232Cfg[__IDX__].Para, "xon=on to=on odsr=off dtr=on rts=off");
            break;

        case 'H':
        case 'h':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=off");
            break;

        default:
            __console("\nFlow control value is 'N', 'X', or 'H'");
            return RS232_PROC_ERROR;
    }

    __console("\nRS232 configure: %s, %s", Rs232Cfg[__IDX__].PortName, Rs232Cfg[__IDX__].Para);

    Rs232Cfg[__IDX__].Handler=CreateFileA(Rs232Cfg[__IDX__].PortName, GENERIC_READ|GENERIC_WRITE,
            0, /* no share  */
            NULL, /* no security */
            OPEN_EXISTING,
            0, /* no threads */
            NULL); /* no templates */

    if(Rs232Cfg[__IDX__].Handler==INVALID_HANDLE_VALUE)
    {
        __console("\nUnable to open comport");
        return RS232_PROC_ERROR;
    }

    memset(&port_settings, 0, sizeof (port_settings)); /* clear the new struct  */
    port_settings.DCBlength=sizeof (port_settings);

    if(!BuildCommDCBA(&Rs232Cfg[__IDX__].Para[0], &port_settings))
    {
        __console("\nUnable to set comport DCB settings");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    if((Rs232Cxt[__IDX__].Parity!='N')||(Rs232Cxt[__IDX__].Parity!='n'))
    {
        port_settings.fOutxCtsFlow=TRUE;
        port_settings.fRtsControl=RTS_CONTROL_HANDSHAKE;
    }

    if(!SetCommState(Rs232Cfg[__IDX__].Handler, &port_settings))
    {
        __console("\nUnable to set comport cfg settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    Cptimeouts.ReadIntervalTimeout=MAXDWORD;
    Cptimeouts.ReadTotalTimeoutMultiplier=0;
    Cptimeouts.ReadTotalTimeoutConstant=0;
    Cptimeouts.WriteTotalTimeoutMultiplier=0;
    Cptimeouts.WriteTotalTimeoutConstant=0;

    if(!SetCommTimeouts(Rs232Cfg[__IDX__].Handler, &Cptimeouts))
    {
        __console("\nUnable to set comport time-out settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    KIT_RS232_EnableDTR(__IDX__);
    KIT_RS232_EnableRTS(__IDX__);

    RingBuffer_RxInit(Rs232Cfg[__IDX__].RxBuffer, Rs232Buf[__IDX__].RxData, KIT_RS232_RX_BUFF_SIZE);
    RingBuffer_TxInit(Rs232Cfg[__IDX__].TxBuffer, Rs232Buf[__IDX__].TxData, KIT_RS232_TX_BUFF_SIZE);

    TaskManager_Create_NewSimpleTask(KIT_RS232_Tasks1);
    __console("\nRS232 success");

    return RS232_PROC_SUCCESS;

#undef __IDX__
} // </editor-fold>

private void KIT_RS232_Deinitialize1(void) // <editor-fold defaultstate="collapsed" desc="RS232 deinitialize">
{
#define __IDX__ 0
    TaskManager_End_Task(KIT_RS232_Tasks1);
    CloseHandle(Rs232Cfg[__IDX__].Handler);
    RingBuffer_RxDeinit(&Rs232Cfg[__IDX__].RxBuffer);
    RingBuffer_TxDeinit(&Rs232Cfg[__IDX__].TxBuffer);
    __console("\nSerial port %d closed", __IDX__);
#undef __IDX__
} // </editor-fold>

#if(NUM_OF_RS232_PORT>=2)

private rs232_state_t KIT_RS232_Initialize2(void) // <editor-fold defaultstate="collapsed" desc="RS232 initialize">
{
#define __IDX__ 1
    int i;
    DCB port_settings;
    COMMTIMEOUTS Cptimeouts;

    __console("\nPORT %d CONFIGURATION:\n", __IDX__);

    if((Rs232Cxt[__IDX__].Port<1)||(Rs232Cxt[__IDX__].Port>255))
    {
        __console("\nPort value is between 1 & 255");
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].PortName[0], "\\\\.\\COM%d", Rs232Cxt[__IDX__].Port);

    for(i=0; i<sizeof (SupportedBaudrate); i++)
    {
        if(Rs232Cxt[__IDX__].Baud==SupportedBaudrate[i])
            break;
    }

    if(i>=sizeof (SupportedBaudrate))
    {
        __console("\nBaud rate %d is not supported", Rs232Cxt[__IDX__].Baud);
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].Para[0], "baud=%d ", Rs232Cxt[__IDX__].Baud);

    switch(Rs232Cxt[__IDX__].DataBit)
    {
        case 5:
            strcat(Rs232Cfg[__IDX__].Para, "data=5 ");
            break;

        case 6:
            strcat(Rs232Cfg[__IDX__].Para, "data=6 ");
            break;

        case 7:
            strcat(Rs232Cfg[__IDX__].Para, "data=7 ");
            break;

        case 8:
            strcat(Rs232Cfg[__IDX__].Para, "data=8 ");
            break;

        default:
            __console("\nData bit value is between 5 & 8");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].Parity)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "parity=n ");
            break;

        case 'O':
        case 'o':
            strcat(Rs232Cfg[__IDX__].Para, "parity=o ");
            break;

        case 'E':
        case 'e':
            strcat(Rs232Cfg[__IDX__].Para, "parity=e ");
            break;

        case 'M':
        case 'm':
            strcat(Rs232Cfg[__IDX__].Para, "parity=m ");
            break;

        case 'S':
        case 's':
            strcat(Rs232Cfg[__IDX__].Para, "parity=s ");
            break;

        default:
            __console("\nParity value is 'N', 'O', 'E', 'M' or 'S'");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].StopBit)
    {
        case 0:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1 ");
            break;

        case 1:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1.5 ");
            break;

        case 2:
            strcat(Rs232Cfg[__IDX__].Para, "stop=2 ");
            break;

        default:
            __console("\nParity value is 0=1bit, 1=1.5bit, or 2=2bits");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].FlowCtrl)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=on");
            break;

        case 'X':
        case 'x':
            strcat(Rs232Cfg[__IDX__].Para, "xon=on to=on odsr=off dtr=on rts=off");
            break;

        case 'H':
        case 'h':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=off");
            break;

        default:
            __console("\nFlow control value is 'N', 'X', or 'H'");
            return RS232_PROC_ERROR;
    }

    __console("\nRS232 configure: %s, %s", Rs232Cfg[__IDX__].PortName, Rs232Cfg[__IDX__].Para);

    Rs232Cfg[__IDX__].Handler=CreateFileA(Rs232Cfg[__IDX__].PortName, GENERIC_READ|GENERIC_WRITE,
            0, /* no share  */
            NULL, /* no security */
            OPEN_EXISTING,
            0, /* no threads */
            NULL); /* no templates */

    if(Rs232Cfg[__IDX__].Handler==INVALID_HANDLE_VALUE)
    {
        __console("\nUnable to open comport");
        return RS232_PROC_ERROR;
    }

    memset(&port_settings, 0, sizeof (port_settings)); /* clear the new struct  */
    port_settings.DCBlength=sizeof (port_settings);

    if(!BuildCommDCBA(&Rs232Cfg[__IDX__].Para[0], &port_settings))
    {
        __console("\nUnable to set comport DCB settings");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    if((Rs232Cxt[__IDX__].Parity!='N')||(Rs232Cxt[__IDX__].Parity!='n'))
    {
        port_settings.fOutxCtsFlow=TRUE;
        port_settings.fRtsControl=RTS_CONTROL_HANDSHAKE;
    }

    if(!SetCommState(Rs232Cfg[__IDX__].Handler, &port_settings))
    {
        __console("\nUnable to set comport cfg settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    Cptimeouts.ReadIntervalTimeout=MAXDWORD;
    Cptimeouts.ReadTotalTimeoutMultiplier=0;
    Cptimeouts.ReadTotalTimeoutConstant=0;
    Cptimeouts.WriteTotalTimeoutMultiplier=0;
    Cptimeouts.WriteTotalTimeoutConstant=0;

    if(!SetCommTimeouts(Rs232Cfg[__IDX__].Handler, &Cptimeouts))
    {
        __console("\nUnable to set comport time-out settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    KIT_RS232_EnableDTR(__IDX__);
    KIT_RS232_EnableRTS(__IDX__);

    RingBuffer_RxInit(Rs232Cfg[__IDX__].RxBuffer, Rs232Buf[__IDX__].RxData, KIT_RS232_RX_BUFF_SIZE);
    RingBuffer_TxInit(Rs232Cfg[__IDX__].TxBuffer, Rs232Buf[__IDX__].TxData, KIT_RS232_TX_BUFF_SIZE);

    TaskManager_Create_NewSimpleTask(KIT_RS232_Tasks2);
    __console("\nRS232 success");

    return RS232_PROC_SUCCESS;

#undef __IDX__
} // </editor-fold>

private void KIT_RS232_Deinitialize2(void) // <editor-fold defaultstate="collapsed" desc="RS232 deinitialize">
{
#define __IDX__ 1
    TaskManager_End_Task(KIT_RS232_Tasks2);
    CloseHandle(Rs232Cfg[__IDX__].Handler);
    RingBuffer_RxDeinit(&Rs232Cfg[__IDX__].RxBuffer);
    RingBuffer_TxDeinit(&Rs232Cfg[__IDX__].TxBuffer);
    __console("\nSerial port %d closed", __IDX__);
#undef __IDX__
} // </editor-fold>

#endif

#if(NUM_OF_RS232_PORT>=3)

private rs232_state_t KIT_RS232_Initialize3(void) // <editor-fold defaultstate="collapsed" desc="RS232 initialize">
{
#define __IDX__ 2
    int i;
    DCB port_settings;
    COMMTIMEOUTS Cptimeouts;

    __console("\nPORT %d CONFIGURATION:\n", __IDX__);

    if((Rs232Cxt[__IDX__].Port<1)||(Rs232Cxt[__IDX__].Port>255))
    {
        __console("\nPort value is between 1 & 255");
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].PortName[0], "\\\\.\\COM%d", Rs232Cxt[__IDX__].Port);

    for(i=0; i<sizeof (SupportedBaudrate); i++)
    {
        if(Rs232Cxt[__IDX__].Baud==SupportedBaudrate[i])
            break;
    }

    if(i>=sizeof (SupportedBaudrate))
    {
        __console("\nBaud rate %d is not supported", Rs232Cxt[__IDX__].Baud);
        return RS232_PROC_ERROR;
    }

    sprintf(&Rs232Cfg[__IDX__].Para[0], "baud=%d ", Rs232Cxt[__IDX__].Baud);

    switch(Rs232Cxt[__IDX__].DataBit)
    {
        case 5:
            strcat(Rs232Cfg[__IDX__].Para, "data=5 ");
            break;

        case 6:
            strcat(Rs232Cfg[__IDX__].Para, "data=6 ");
            break;

        case 7:
            strcat(Rs232Cfg[__IDX__].Para, "data=7 ");
            break;

        case 8:
            strcat(Rs232Cfg[__IDX__].Para, "data=8 ");
            break;

        default:
            __console("\nData bit value is between 5 & 8");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].Parity)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "parity=n ");
            break;

        case 'O':
        case 'o':
            strcat(Rs232Cfg[__IDX__].Para, "parity=o ");
            break;

        case 'E':
        case 'e':
            strcat(Rs232Cfg[__IDX__].Para, "parity=e ");
            break;

        case 'M':
        case 'm':
            strcat(Rs232Cfg[__IDX__].Para, "parity=m ");
            break;

        case 'S':
        case 's':
            strcat(Rs232Cfg[__IDX__].Para, "parity=s ");
            break;

        default:
            __console("\nParity value is 'N', 'O', 'E', 'M' or 'S'");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].StopBit)
    {
        case 0:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1 ");
            break;

        case 1:
            strcat(Rs232Cfg[__IDX__].Para, "stop=1.5 ");
            break;

        case 2:
            strcat(Rs232Cfg[__IDX__].Para, "stop=2 ");
            break;

        default:
            __console("\nParity value is 0=1bit, 1=1.5bit, or 2=2bits");
            return RS232_PROC_ERROR;
    }

    switch(Rs232Cxt[__IDX__].FlowCtrl)
    {
        case 'N':
        case 'n':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=on");
            break;

        case 'X':
        case 'x':
            strcat(Rs232Cfg[__IDX__].Para, "xon=on to=on odsr=off dtr=on rts=off");
            break;

        case 'H':
        case 'h':
            strcat(Rs232Cfg[__IDX__].Para, "xon=off to=off odsr=off dtr=on rts=off");
            break;

        default:
            __console("\nFlow control value is 'N', 'X', or 'H'");
            return RS232_PROC_ERROR;
    }

    __console("\nRS232 configure: %s, %s", Rs232Cfg[__IDX__].PortName, Rs232Cfg[__IDX__].Para);

    Rs232Cfg[__IDX__].Handler=CreateFileA(Rs232Cfg[__IDX__].PortName, GENERIC_READ|GENERIC_WRITE,
            0, /* no share  */
            NULL, /* no security */
            OPEN_EXISTING,
            0, /* no threads */
            NULL); /* no templates */

    if(Rs232Cfg[__IDX__].Handler==INVALID_HANDLE_VALUE)
    {
        __console("\nUnable to open comport");
        return RS232_PROC_ERROR;
    }

    memset(&port_settings, 0, sizeof (port_settings)); /* clear the new struct  */
    port_settings.DCBlength=sizeof (port_settings);

    if(!BuildCommDCBA(&Rs232Cfg[__IDX__].Para[0], &port_settings))
    {
        __console("\nUnable to set comport DCB settings");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    if((Rs232Cxt[__IDX__].Parity!='N')||(Rs232Cxt[__IDX__].Parity!='n'))
    {
        port_settings.fOutxCtsFlow=TRUE;
        port_settings.fRtsControl=RTS_CONTROL_HANDSHAKE;
    }

    if(!SetCommState(Rs232Cfg[__IDX__].Handler, &port_settings))
    {
        __console("\nUnable to set comport cfg settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    Cptimeouts.ReadIntervalTimeout=MAXDWORD;
    Cptimeouts.ReadTotalTimeoutMultiplier=0;
    Cptimeouts.ReadTotalTimeoutConstant=0;
    Cptimeouts.WriteTotalTimeoutMultiplier=0;
    Cptimeouts.WriteTotalTimeoutConstant=0;

    if(!SetCommTimeouts(Rs232Cfg[__IDX__].Handler, &Cptimeouts))
    {
        __console("\nUnable to set comport time-out settings\n");
        CloseHandle(Rs232Cfg[__IDX__].Handler);
        return RS232_PROC_ERROR;
    }

    KIT_RS232_EnableDTR(__IDX__);
    KIT_RS232_EnableRTS(__IDX__);

    RingBuffer_RxInit(Rs232Cfg[__IDX__].RxBuffer, Rs232Buf[__IDX__].RxData, KIT_RS232_RX_BUFF_SIZE);
    RingBuffer_TxInit(Rs232Cfg[__IDX__].TxBuffer, Rs232Buf[__IDX__].TxData, KIT_RS232_TX_BUFF_SIZE);

    TaskManager_Create_NewSimpleTask(KIT_RS232_Tasks3);
    __console("\nRS232 success");

    return RS232_PROC_SUCCESS;

#undef __IDX__
} // </editor-fold>

private void KIT_RS232_Deinitialize3(void) // <editor-fold defaultstate="collapsed" desc="RS232 deinitialize">
{
#define __IDX__ 2
    TaskManager_End_Task(KIT_RS232_Tasks3);
    CloseHandle(Rs232Cfg[__IDX__].Handler);
    RingBuffer_RxDeinit(&Rs232Cfg[__IDX__].RxBuffer);
    RingBuffer_TxDeinit(&Rs232Cfg[__IDX__].TxBuffer);
    __console("\nSerial port %d closed", __IDX__);
#undef __IDX__
} // </editor-fold>

#endif

private void KIT_RS232_EchoTest1(void) // <editor-fold defaultstate="collapsed" desc="Test">
{
#define __IDX__ 0
    static uint8_t c;
    static bool latch=0;

    if(KIT_RS232_IsRxReady(__IDX__))
    {
        if(latch==0)
        {
            latch=1;
            c=KIT_RS232_ReadByte(__IDX__);
        }
        else if(KIT_RS232_IsTxReady(__IDX__))
        {
            latch=0;
            KIT_RS232_WriteByte(__IDX__, c);
        }
    }

#undef __IDX__
} // </editor-fold>

#if(NUM_OF_RS232_PORT>=2)

private void KIT_RS232_EchoTest2(void) // <editor-fold defaultstate="collapsed" desc="Test">
{
#define __IDX__ 1
    static uint8_t c;
    static bool latch=0;

    if(KIT_RS232_IsRxReady(__IDX__))
    {
        if(latch==0)
        {
            latch=1;
            c=KIT_RS232_ReadByte(__IDX__);
        }
        else if(KIT_RS232_IsTxReady(__IDX__))
        {
            latch=0;
            KIT_RS232_WriteByte(__IDX__, c);
        }
    }

#undef __IDX__
} // </editor-fold>
#endif

#if(NUM_OF_RS232_PORT>=3)

private void KIT_RS232_EchoTest3(void) // <editor-fold defaultstate="collapsed" desc="Test">
{
#define __IDX__ 2
    static uint8_t c;
    static bool latch=0;

    if(KIT_RS232_IsRxReady(__IDX__))
    {
        if(latch==0)
        {
            latch=1;
            c=KIT_RS232_ReadByte(__IDX__);
        }
        else if(KIT_RS232_IsTxReady(__IDX__))
        {
            latch=0;
            KIT_RS232_WriteByte(__IDX__, c);
        }
    }

#undef __IDX__
} // </editor-fold>
#endif

public rs232_state_t KIT_RS232_Initialize(void) // <editor-fold defaultstate="collapsed" desc="Initialize">
{
    rs232_state_t rslt=RS232_PROC_HANDLE;

    switch(InitNext)
    {
        case 0:
            rslt=KIT_RS232_Initialize1();

            if(rslt==RS232_PROC_SUCCESS)
            {
                rslt=RS232_PROC_HANDLE;
                InitNext++;
            }
            break;

#if(NUM_OF_RS232_PORT>=2)
        case 1:
            rslt=KIT_RS232_Initialize2();

            if(rslt==RS232_PROC_SUCCESS)
            {
                rslt=RS232_PROC_HANDLE;
                InitNext++;
            }
            break;
#endif

#if(NUM_OF_RS232_PORT>=3)
        case 1:
            rslt=KIT_RS232_Initialize3();

            if(rslt==RS232_PROC_SUCCESS)
            {
                rslt=RS232_PROC_HANDLE;
                InitNext++;
            }
            break;
#endif

        default:
            rslt=RS232_PROC_SUCCESS;
            break;
    }

    return rslt;
} // </editor-fold>

public void KIT_RS232_Deinitialize(void) // <editor-fold defaultstate="collapsed" desc="Deinitialize">
{
    KIT_RS232_Deinitialize1();

#if(NUM_OF_RS232_PORT>=2)
    KIT_RS232_Deinitialize2();
#endif

#if(NUM_OF_RS232_PORT>=3)
    KIT_RS232_Deinitialize3();
#endif

    InitNext=0;
} // </editor-fold>

public void KIT_RS232_EchoTest(void) // <editor-fold defaultstate="collapsed" desc="Test">
{
    KIT_RS232_EchoTest1();

#if(NUM_OF_RS232_PORT>=2)
    KIT_RS232_EchoTest2();
#endif

#if(NUM_OF_RS232_PORT>=3)
    KIT_RS232_EchoTest3();
#endif
} // </editor-fold>

public new_simple_task_t(KIT_RS232_Transparent) // <editor-fold defaultstate="collapsed" desc="Transparent data">
{
    while(KIT_RS232_IsRxReady(PortTrans1))
    {
        if(!KIT_RS232_IsTxReady(PortTrans2))
            break;

        KIT_RS232_WriteByte(PortTrans2, KIT_RS232_ReadByte(PortTrans1));
    }

    while(KIT_RS232_IsRxReady(PortTrans2))
    {
        if(!KIT_RS232_IsTxReady(PortTrans1))
            break;

        KIT_RS232_WriteByte(PortTrans1, KIT_RS232_ReadByte(PortTrans2));
    }

    Task_Done();
} // </editor-fold>

public void KIT_RS232_OpenTransparentPort(uint8_t PortIdx1, uint8_t PortIdx2) // <editor-fold defaultstate="collapsed" desc="Open transparent port">
{
    PortTrans1=PortIdx1;
    PortTrans2=PortIdx2;
    TaskManager_Create_NewSimpleTask(KIT_RS232_Transparent);
} // </editor-fold>

public void KIT_RS232_CloseTransparentPort(void) // <editor-fold defaultstate="collapsed" desc="Close transparent port">
{
    TaskManager_End_Task(KIT_RS232_Transparent);
}