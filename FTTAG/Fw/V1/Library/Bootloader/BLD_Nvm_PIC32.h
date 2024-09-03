#ifndef BLD_NVM_PIC32_H
#define	BLD_NVM_PIC32_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "BLD_Nvm_Cfg.h"
#endif

public int8_t BLD_Nvm_Write(uint32_t Addr, const uint8_t *pData, int Len);

#endif