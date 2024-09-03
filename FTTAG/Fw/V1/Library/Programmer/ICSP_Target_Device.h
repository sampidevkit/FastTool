#ifndef NVM_TARGET_DEVICE_H
#define NVM_TARGET_DEVICE_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "Icsp_Cfg.h"
#endif

#if defined(TARGET_MCU_PIC32MM0064GPM028)||defined(TARGET_MCU_PIC32MM0128GPM028) \
||defined(TARGET_MCU_PIC32MM0256GPM028)||defined(TARGET_MCU_PIC32MM0064GPM036) \
||defined(TARGET_MCU_PIC32MM0128GPM036)||defined(TARGET_MCU_PIC32MM0256GPM036) \
||defined(TARGET_MCU_PIC32MM0064GPM048)||defined(TARGET_MCU_PIC32MM0128GPM048) \
||defined(TARGET_MCU_PIC32MM0256GPM048)||defined(TARGET_MCU_PIC32MM0064GPM064) \
||defined(TARGET_MCU_PIC32MM0128GPM064)||defined(TARGET_MCU_PIC32MM0256GPM064)

#define TARGET_CPU_TYPE         32 // bit
/* Ref to DS60001387D-page 43 */
#define __TARGET_NAME__         "PIC32MM0xxxGPM0yy"
#define TARGET_ID_COUNT         12 // 12 supported devices
#define TARGET_ID_LIST          0x07708053, 0x07710053, 0x07718053, 0x0770A053, \
                                0x07712053, 0x0771A053, 0x0772C053, 0x07734053, \
                                0x0773C053, 0x0770E053, 0x07716053, 0x0771E053
#define TARGET_ID_NAME          {"PIC32MM0064GPM028"},{"PIC32MM0128GPM028"}, \
                                {"PIC32MM0256GPM028"},{"PIC32MM0064GPM036"}, \
                                {"PIC32MM0128GPM036"},{"PIC32MM0256GPM036"}, \
                                {"PIC32MM0064GPM048"},{"PIC32MM0128GPM048"}, \
                                {"PIC32MM0256GPM048"},{"PIC32MM0064GPM064"}, \
                                {"PIC32MM0128GPM064"},{"PIC32MM0256GPM064"}
#define TARGET_PAGE_WORD_SIZE   512 // (words)
#define TARGET_PAGE_WORD_MASK   0xFFFFFE00
#define TARGET_PAGE_BYTE_SIZE   2048 // (bytes)
#define TARGET_PAGE_BYTE_MASK   0xFFFFF800
#define TARGET_ROW_WORD_SIZE    64 // (words)
#define TARGET_ROW_WORD_MASK    0xFFFFFFC0
#define TARGET_ROW_BYTE_SIZE    256 // (bytes)
#define TARGET_ROW_BYTE_MASK    0xFFFFF800
/* Index of Flash memory partition */
#define TARGET_PFM_START        0x1D000000
#define TARGET_PFM_END          0x1D03FFFF
#define TARGET_PFM_BYTE_LENGTH  (TARGET_PFM_END-TARGET_PFM_START+1)
#define TARGET_PFM_WORD_LENGTH  (TARGET_PFM_BYTE_LENGTH/4)
#define TARGET_BFM_START        0x1FC00000
#define TARGET_BFM_END          0x1FC016FF
#define TARGET_BFM_BYTE_LENGTH  (TARGET_BFM_END-TARGET_BFM_START+1)
#define TARGET_BFM_WORD_LENGTH  (TARGET_BFM_BYTE_LENGTH/4)
#define TARGET_CFG_START        0x1FC01700
#define TARGET_CFG_END          0x1FC017FF
#define TARGET_CFG_BYTE_LENGTH  (TARGET_CFG_END-TARGET_CFG_START+1)
#define TARGET_CFG_WORD_LENGTH  (TARGET_CFG_BYTE_LENGTH/4)
// #define TARGET_UDID_START       0x1FC41840
// #define TARGET_UDID_END         0x1FC41853
// #define TARGET_UDID_BYTE_LENGTH (TARGET_UDID_END-TARGET_UDID_START+1)
// #define TARGET_UDID_WORD_LENGTH (TARGET_UDID_BYTE_LENGTH/4)

#define GetRowAddress(Addr)     (Addr&TARGET_ROW_BYTE_MASK)
#define GetPageAddress(Addr)    (Addr&TARGET_PAGE_BYTE_MASK)
#define GetRowIndex(Addr)       (Addr-GetRowAddress(Addr))
#define GetDWordStartAddr(Addr) (Addr&0xFFFFFFF8)

#elif defined(TARGET_MCU_PIC16F188XX)|| \
defined(TARGET_MCU_PIC16LF18854)||defined(TARGET_MCU_PIC16F18854)|| \
defined(TARGET_MCU_PIC16LF18855)||defined(TARGET_MCU_PIC16F18855)|| \
defined(TARGET_MCU_PIC16LF18856)||defined(TARGET_MCU_PIC16F18856)|| \
defined(TARGET_MCU_PIC16LF18857)||defined(TARGET_MCU_PIC16F18857)|| \
defined(TARGET_MCU_PIC16LF18875)||defined(TARGET_MCU_PIC16F18875)|| \
defined(TARGET_MCU_PIC16LF18876)||defined(TARGET_MCU_PIC16F18876)|| \
defined(TARGET_MCU_PIC16LF18877)||defined(TARGET_MCU_PIC16F18877)

#define TARGET_CPU_TYPE         8 // bit
/* Ref to DS60001387D-page 43 */
#if defined(TARGET_MCU_PIC16LF18854)
#define __TARGET_NAME__         "PIC16LF18854"
#define TARGET_ID               0x306B
#elif defined(TARGET_MCU_PIC16F18854)
#define __TARGET_NAME__         "PIC16F18854"
#define TARGET_ID               0x306A
#elif defined(TARGET_MCU_PIC16LF18855)
#define __TARGET_NAME__         "PIC16LF18855"
#define TARGET_ID               0x306E
#elif defined(TARGET_MCU_PIC16F18855)
#define __TARGET_NAME__         "PIC16F18855"
#define TARGET_ID               0x306C
#elif defined(TARGET_MCU_PIC16LF18856)
#define __TARGET_NAME__         "PIC16LF18856"
#define TARGET_ID               0x3072
#elif defined(TARGET_MCU_PIC16F18856)
#define __TARGET_NAME__         "PIC16F18856"
#define TARGET_ID               0x3070
#elif defined(TARGET_MCU_PIC16LF18857)
#define __TARGET_NAME__         "PIC16LF18857"
#define TARGET_ID               0x3076
#elif defined(TARGET_MCU_PIC16F18857)
#define __TARGET_NAME__         "PIC16F18857"
#define TARGET_ID               0x3074
#elif defined(TARGET_MCU_PIC16LF18875)
#define __TARGET_NAME__         "PIC16LF18875"
#define TARGET_ID               0x306F
#elif defined(TARGET_MCU_PIC16F18875)
#define __TARGET_NAME__         "PIC16F18875"
#define TARGET_ID               0x306D
#elif defined(TARGET_MCU_PIC16LF18876)
#define __TARGET_NAME__         "PIC16LF18876"
#define TARGET_ID               0x3073
#elif defined(TARGET_MCU_PIC16F18876)
#define __TARGET_NAME__         "PIC16F18876"
#define TARGET_ID               0x3071
#elif defined(TARGET_MCU_PIC16LF18877)
#define __TARGET_NAME__         "PIC16LF18877"
#define TARGET_ID               0x3077
#elif defined(TARGET_MCU_PIC16F18877)
#define __TARGET_NAME__         "PIC16F18877"
#define TARGET_ID               0x3075
#else
#define __TARGET_NAME__         "PIC16F188XX"
#define TARGET_ID_MIN           0x306A
#define TARGET_ID_MAX           0x3077
#endif
// Set Row==Page
#define TARGET_PAGE_WORD_SIZE   32 // (words)
#define TARGET_PAGE_WORD_MASK   0xFFE0
#define TARGET_PAGE_BYTE_SIZE   64 // (bytes)
#define TARGET_PAGE_BYTE_MASK   0xFFC0
#define TARGET_ROW_WORD_SIZE    32 // (words)
#define TARGET_ROW_WORD_MASK    0xFFE0
#define TARGET_ROW_BYTE_SIZE    64 // (bytes)
#define TARGET_ROW_BYTE_MASK    0xFFC0
/* Index of Flash memory partition */
// Program Flash Memory
#define TARGET_PFM_START        0x0000
#define TARGET_PFM_END          0x7FFF 
#define TARGET_PFM_WORD_LENGTH  (TARGET_PFM_END-TARGET_PFM_START+1)
// User IDs
#define TARGET_UID_START        0x8000
#define TARGET_UID_END          0x8003
#define TARGET_UID_WORD_LENGTH  (TARGET_UID_END-TARGET_UID_START+1)
// Revision ID
#define TARGET_RID_START        0x8005
#define TARGET_RID_END          0x8005
#define TARGET_RID_WORD_LENGTH  (TARGET_RID_END-TARGET_RID_START+1)
// Device ID
#define TARGET_DID_START        0x8006
#define TARGET_DID_END          0x8006
#define TARGET_DID_WORD_LENGTH  (TARGET_DID_END-TARGET_DID_START+1)
// Configuration Word
#define TARGET_CFG_START        0x8007
#define TARGET_CFG_END          0x800B
#define TARGET_CFG_WORD_LENGTH  (TARGET_CFG_END-TARGET_CFG_START+1)
#define TARGET_CFG_WORD1_MASK   0b01011010001000
#define TARGET_CFG_WORD2_MASK   0b00000100011101 // LSB (MCLRE bit) RE3 pin function is always MCLR in LVP mode 
#define TARGET_CFG_WORD3_MASK   0b00000010000000
#define TARGET_CFG_WORD4_MASK   0b10111111111100 // MSB (LVP bit) is always 1 in Low voltage programming mode
#define TARGET_CFG_WORD5_MASK   0b11111111111100
// User Data Memory (EEPROM)
#define TARGET_EEP_START        0xF000
#define TARGET_EEP_END          0xF0FF
#define TARGET_EEP_BYTE_LENGTH  (TARGET_EEP_END-TARGET_EEP_START+1)
#define TARGET_EEP_WORD_LENGTH  (TARGET_EEP_BYTE_LENGTH/2)

#define GetRowAddress(Addr)     (Addr&TARGET_ROW_WORD_MASK)
#define GetRowIndex(Addr)       (Addr-GetRowAddress(Addr))
#else
#error "Please define your chip memory"
#endif
#endif