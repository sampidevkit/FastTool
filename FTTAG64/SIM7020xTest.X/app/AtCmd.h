#ifndef ATCMD_H
#define ATCMD_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define ATCMD_Port_IsRxReady()      UART2_IsRxReady()
#define ATCMD_Port_Read()           UART2_Read()
#define ATCMD_Port_IsTxReady()      UART2_IsTxReady()
#define ATCMD_Port_Write(x)         UART2_Write(x)
#define ATCMD_Port_IsTxDone()       UART2_IsTxDone()

typedef struct
{
    uint8_t *pData;
    size_t Len;
} buff_t;

extern buff_t AtCmdRxBkBuff;

void ATCMD_Init(void);
void ATCMD_SendRaw(const uint8_t *pD, size_t sz);
int8_t ATCMD_GetRaw(uint8_t *pD, size_t *pSz, uint16_t firstWait, uint16_t lastWait);
int8_t ATCMD_SendGetDat(const char *pTx, char *pRx, uint16_t firstWait, uint16_t lastWait);
int8_t ATCMD_SendGetAck(const char *pTx, const char *pAck, uint16_t firstWait, uint16_t lastWait);

#define ATCMD_SetBkBuffer(buf)      AtCmdRxBkBuff.pData=buf
#define ATCMD_GetBkBuffer(idx)      AtCmdRxBkBuff.pData[idx]
#define ATCMD_GetBkBufferSize()     AtCmdRxBkBuff.Len

#endif