#ifndef ICSP_PIC16F188XX_H
#define	ICSP_PIC16F188XX_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "ICSP_PIC16F188XX_Cfg.h"
#endif

// ICSP command set - DS4000175B-page 9
#define LOAD_PC_ADDRESS             0x80 // PC=payload value, delay TDLY
#define BULK_ERASE_PROGRAM_MEMORY   0x18 // Depending on the current value of the PC, one or more memory regions, delay TERAB
#define ROW_ERASE_PROGRAM_MEMORY    0xF0 // The row addressed by the MSBs of the PC is erased; LSBs are ignored, delay TERAR
#define LOAD_DATA_NVM_UNCHANGE_PC   0x00 // PC is unchanged, delay TDLY
#define LOAD_DATA_NVM_AFTER_WRITE   0x02 // PC=PC+1 after writing, delay TDLY
#define READ_DATA_NVM_UNCHANGE_PC   0xFC // PC is unchanged, delay TDLY
#define READ_DATA_NVM_AFTER_WRITE   0xFE // PC=PC+1 after writing, delay TDLY
#define INCREMENT_ADDRESS           0xF8 // PC=PC+1, delay TDLY
#define BEGIN_INT_TIMED_PROG        0xE0 // Commits latched data to NVM (self timed), delay TPINT
#define BEGIN_EXT_TIMED_PROG        0xC0 // Commits latched data to NVM (externally timed). After TPEXT, end external timed programming command must be issued, delay TPEXT
#define END_EXT_TIMED_PROG          0x82 // Should be issued within required time delay (TPEXT) after begin externally timed programming command, delay TDIS

typedef struct {
    uint16_t Address;
    uint16_t Word;
} icsp_nvm_t;

public void PIC16F188XX_InitICSP(void);
public bool PIC16F188XX_EnterICSP(void);
public void PIC16F188XX_ExitICSP(void);
public uint32_t PIC16F188XX_GetDeviceID(void);
public bool PIC16F188XX_BulkEraseMemory(void);
public int8_t PIC16F188XX_NVM_StreamOut(void (*pStreamFnc)(uint8_t c));
public int8_t PIC16F188XX_NVM_Write(uint32_t Addr, const uint8_t *pData, int Len);

#endif