#ifndef ATCMD_CFG_H
#define ATCMD_CFG_H

#include "uart2.h"

/* **************************************************************** Data Port */
#define ATCMD_Port_IsRxReady()      UART2_IsRxReady()
#define ATCMD_Port_Read()           UART2_Read()
#define ATCMD_Port_IsTxReady()      UART2_IsTxReady()
#define ATCMD_Port_Write(x)         UART2_Write(x)
#define ATCMD_Port_IsTxDone()       UART2_IsTxDone()

/* ************************************************************ Library Debug */
#define USE_ATCMD_DEBUG

#endif