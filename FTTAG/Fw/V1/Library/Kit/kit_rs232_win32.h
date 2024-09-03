#ifndef KIT_RS232_WIN32_H
#define KIT_RS232_WIN32_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_rs232_win32_cfg.h"
#endif

#define rs232_state_t       int
#define RS232_PROC_ERROR    (-1)
#define RS232_PROC_SUCCESS  0
#define RS232_PROC_HANDLE   1

typedef struct RS232_PARAMETER_CONTEXT {
    uint8_t Port; // 1 to 255
    uint32_t Baud;
    uint8_t DataBit; // 5 to 8
    uint8_t Parity; // 'N'=None, 'O'=Odd, 'E'=Even, 'M'=Mark, 'S'=Space
    uint8_t FlowCtrl; // 'N'=None, 'X'=Xon/Xoff, 'H'=Hardware
    uint8_t StopBit; // 0=1bit, 1=1.5bit, 2=2bits
} rs232_cxt_t;

// Data bit
#define RS232_DATA_5BITS        5
#define RS232_DATA_6BITS        6
#define RS232_DATA_7BITS        7
#define RS232_DATA_8BITS        8

// Parity
#define RS232_PARITY_NONE       'N'
#define RS232_PARITY_ODD        'O'
#define RS232_PARITY_EVEN       'E'
#define RS232_PARITY_MARK       'M'
#define RS232_PARITY_SPACE      'S'

// Flow control
#define RS232_FLOWCTRL_NONE     'N'
#define RS232_FLOWCTRL_XON_XOFF 'X'
#define RS232_FLOWCTRL_HARDWARE 'H'

// Stop bit
#define RS232_STOPBIT_1          0
#define RS232_STOPBIT_1_5        1
#define RS232_STOPBIT_2          2

public rs232_state_t KIT_RS232_Initialize(void);
public void KIT_RS232_Deinitialize(void);
public void KIT_RS232_Tasks1(void*);
public void KIT_RS232_Tasks2(void*);
public void KIT_RS232_Tasks3(void*);
public bool KIT_RS232_IsRxReady(uint8_t portIdx);
public bool KIT_RS232_IsTxReady(uint8_t portIdx);
public void KIT_RS232_WriteByte(uint8_t portIdx, uint8_t c);
public uint8_t KIT_RS232_ReadByte(uint8_t portIdx);
public bool KIT_RS232_IsDCDEnabled(uint8_t portIdx);
public bool KIT_RS232_IsRINGEnabled(uint8_t portIdx);
public bool KIT_RS232_IsCTSEnabled(uint8_t portIdx);
public bool KIT_RS232_IsDSREnabled(uint8_t portIdx);
public void KIT_RS232_EnableDTR(uint8_t portIdx);
public void KIT_RS232_DisableDTR(uint8_t portIdx);
public void KIT_RS232_EnableRTS(uint8_t portIdx);
public void KIT_RS232_DisableRTS(uint8_t portIdx);
public void KIT_RS232_FlushRX(uint8_t portIdx);
public void KIT_RS232_FlushTX(uint8_t portIdx);
public void KIT_RS232_FlushRXTX(uint8_t portIdx);

public void KIT_RS232_EchoTest(void);
public void KIT_RS232_OpenTransparentPort(uint8_t PortIdx1, uint8_t PortIdx2);
public void KIT_RS232_CloseTransparentPort(void);

#endif

