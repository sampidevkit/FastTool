#ifndef VCP_ATC_H
#define	VCP_ATC_H

#include "Common/LibDef.h"

public void VCP_ATC_Init(uint8_t PortIdx);
public void VCP_ATC_Write(uint8_t c);
public uint8_t VCP_ATC_Read(void);
public bool VCP_ATC_IsRxReady(void);
public bool VCP_ATC_IsTxDone(void);
public bool VCP_ATC_IsTxReady(void);

#endif