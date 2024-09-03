#ifndef ICSP_H
#define	ICSP_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "Icsp_Cfg.h"
#endif

typedef enum {
    ICSP_LOG_SUCCESS = 0, // 0
    ICSP_LOG_INVALID_ADDR, // 1
    ICSP_LOG_ADDR_NOT_ALIG_DWORD, // 2
    ICSP_LOG_LEN_NOT_MUL_ROW, // 3
    ICSP_LOG_ADDR_NOT_ALIG_ROW, // 4
    ICSP_LOG_LEN_NOT_MUL_PAGE, // 5
    ICSP_LOG_ADDR_NOT_ALIG_PAGE, // 6
    ICSP_LOG_CHIPID_ERROR, // 7
    ICSP_LOG_ROW_PROG_ERROR, // 8
    ICSP_LOG_READ_ERROR, // 9
    ICSP_LOG_ERASE_ERROR, // A
    ICSP_LOG_NOT_BLANK_ERROR, // B
    ICSP_LOG_CHECKSUM_ERROR, // C
    ICSP_LOG_DWORD_PROG_ERROR, // D
    ICSP_LOG_INTERNAL_ERROR // E
} icsp_stt_code_t;

#ifndef ICSP_LOG_LEN
#error "Please define ICSP_LOG_LEN in Icsp_Cfg.h" 
#endif

#ifndef Icsp_Log_Buffer
#error "Please define Icsp_Log_Buffer in Icsp_Cfg.h" 
#endif

typedef union {
    uint8_t val;

    struct {
        uint8_t busy : 1; // ICSP state: 0- running mode, 1- ICSP mode
        uint8_t row_ready : 1; // 0- no data, 1- data is ready
        uint8_t uid_ready : 1; // 0- no data, 1- data is ready
        uint8_t cfg_ready : 1; // 0- no data, 1- data is ready
        uint8_t eep_ready : 1; // 0- no data, 1- data is ready
        uint8_t rfu : 6;
    };
} icsp_state_t;

extern icsp_state_t icsp_state;
extern bool icsp_initialized;

#define ICSP_Is_Inprogress()    (icsp_state.busy==1?1:0)
#define ICSP_Is_Initialized()   (icsp_initialized==1)

public void icsp_log(icsp_stt_code_t LogCode, uint32_t *Arg1, uint32_t *Arg2, const uint8_t *Arg3);
public void icsp_delay_ms(uint32_t t);
public void icsp_delay_us(uint32_t t);
public uint32_t icsp_convert4x8to32(const uint8_t *pArr);
public uint16_t icsp_convert2x8to16(const uint8_t *pArr);
public void icsp_memcpy32(uint32_t *pDes, const uint32_t *pSrc, uint32_t Len);
public void icsp_memcpy16(uint16_t *pDes, const uint16_t *pSrc, uint16_t Len);
public void icsp_memset32(uint32_t *pDes, uint32_t Value, uint32_t Len);
public void icsp_memset16(uint16_t *pDes, uint16_t Value, uint16_t Len);
public void icsp_memset8(uint8_t *pDes, uint8_t Value, uint16_t Len);
public bool icsp_valid_address_check(uint32_t startAddress, uint32_t length);
public bool icsp_row_aligned_address_check(uint32_t Address, uint32_t length);
public bool icsp_page_aligned_address_check(uint32_t Address, uint32_t length);
public bool ICSP_Init(bool EraseDis);
public void ICSP_Deinit(void);

#endif