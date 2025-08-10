#ifndef UPDI_H
#define	UPDI_H

#include "Common/LibDef.h"

void UPDI_SendData(const uint8_t *pD, uint8_t len);
void UPDI_SendIdle(void);
void UPDI_SendBreak(void);
void UPDI_SendSynch(void);
void UPDI_SendAck(void);
uint8_t UPDI_ReadData(uint16_t addr);
#endif
