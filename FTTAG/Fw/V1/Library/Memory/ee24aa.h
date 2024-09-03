#ifndef EE24AA_H
#define	EE24AA_H

#include "ee24aa_cfg.h"
#include "Common/LibDef.h"

#define EE24AA_OK   PROC_DONE // 0
#define EE24AA_BUSY PROC_BUSY // 1
#define EE24AA_ERR  PROC_ERR // (-1)

bool EE24AA_Init(void);
int8_t EE24AA_Read(uint16_t addr, uint8_t *pD, uint8_t len);

#ifdef EE24AA_MODE_SINGLE_BYTE
int8_t EE24AA_Write_ModeSingleByte(uint16_t addr, uint8_t *pD, uint8_t len);
#define EE24AA_Write(addr, pD, len) EE24AA_Write_ModeSingleByte(addr, pD, len)
#elif defined(EE24AA_MODE_PAGE)
int8_t EE24AA_Write_ModePage(uint16_t addr, uint8_t *pD, uint8_t len);
#define EE24AA_Write(addr, pD, len) EE24AA_Write_ModePage(addr, pD, len)
#else
#error "Please define EE24AA_MODE_SINGLE_BYTE or EE24AA_MODE_PAGE in ee24aa_cfg.h"
#endif
#endif