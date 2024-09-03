#ifndef HEXPARSING_H
#define	HEXPARSING_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "HexParsing_Cfg.h"
#endif

#ifndef HEX_DATA_SIZE
#define HEX_DATA_SIZE   16
#endif

// Data type of Intel hex
#define HEX_RECTYPE_DAT 0x00 // Data
#define HEX_RECTYPE_EOF 0x01 // End Of File
#define HEX_RECTYPE_ESA 0x02 // Extended Segment Address
#define HEX_RECTYPE_SSA 0x03 // Start Segment Address
#define HEX_RECTYPE_ELA 0x04 // Extended Linear Address
#define HEX_RECTYPE_SLA 0x05 // Start Linear Address

typedef struct {
    uint32_t Value;
    uint32_t ExtSeg;
    uint32_t ExtLin;
} hex_addr_t;

typedef struct {
    uint8_t ByteCount;
    hex_addr_t Address;
    uint8_t RecordType;
    uint8_t Data[HEX_DATA_SIZE];
    uint8_t Checksum;
} hex_t;

typedef unsigned long _paddr_t;

#ifndef write_error_log
#define write_error_log(line)   // do{err=line; icsp_log(ICSP_LOG_INTERNAL_ERROR, &err, NULL);}while(0)
#warning "No error log"
#endif

#ifndef HEXPARSE_StreamOut
#define HEXPARSE_StreamOut(c)
#endif

public int8_t HEXPARSE_Hex2Integer(int8_t c, uint8_t NumOfDigit, uint32_t *pVal, uint8_t *pCks);
public int8_t HEXPARSE_Tasks(int8_t c);
public void HEXPARSE_PutLine(uint8_t *pData, uint8_t Len);

#endif