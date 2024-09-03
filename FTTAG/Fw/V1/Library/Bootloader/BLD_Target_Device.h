#ifndef BLD_NVM_TARGET_DEVICE_DEVICE_H
#define BLD_NVM_TARGET_DEVICE_DEVICE_H

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "BLD_Nvm_Cfg.h"
#endif

#if defined(BLD_NVM_TARGET_DEVICE_PIC32)

#if defined(BLD_NVM_TARGET_DEVICE_PIC32MM0256GPM0XX) // tested

#if defined(__32MM0256GPM028_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM028"
#elif defined(__32MM0256GPM036_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM036"
#elif defined(__32MM0256GPM048_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM048"
#elif defined(__32MM0256GPM064_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM064"
#else
#error "Target MCU is not supported"
#endif

// Bootloader size is fixed in 20480 bytes (20kB)
// Application size is 262144-20480=241664 bytes (236kB)
#define BLD_NVM_TARGET_DEVICE_PAGE_SIZE FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS // (bytes)

#ifndef APP_RESET_ADDRESS
#define APP_RESET_ADDRESS               0x9D000000
#endif

#ifndef APP_BEGIN_ADDRESS
#define APP_BEGIN_ADDRESS               0x1D000000
#endif

#ifndef APP_END_ADDRESS
#define APP_END_ADDRESS                 0x1D03AFFF
#endif

#define APP_SIZE_IN_PAGE                118 // (pages)
#define TARGET_PACK_BYTE_MASK           0xFFFFF800 // 2048 bytes/page
#define TARGET_PACK_IDX_MASK            0x7FF // 0 to 2047   

#elif defined(BLD_NVM_TARGET_DEVICE_PIC32MM0128GPM0XX) // not complete

#if defined(__32MM0128GPM028_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM028"
#elif defined(__32MM0128GPM036_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM036"
#elif defined(__32MM0128GPM048_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM048"
#elif defined(__32MM0128GPM064_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0256GPM064"
#else
#error "Target MCU is not supported"
#endif

// Bootloader size is fixed in 20480 bytes (20kB)
// Application size is 131072-20480=110592 bytes (108kB)
#define BLD_NVM_TARGET_DEVICE_PAGE_SIZE FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS // (bytes)

#ifndef APP_RESET_ADDRESS
#define APP_RESET_ADDRESS               0x9D000000
#endif

#ifndef APP_BEGIN_ADDRESS
#define APP_BEGIN_ADDRESS               0x1D000000
#endif

#ifndef APP_END_ADDRESS
#define APP_END_ADDRESS                 0x1D01AFFF
#endif

#define APP_SIZE_IN_PAGE                54 // (pages)
#define TARGET_PACK_BYTE_MASK           0xFFFFF800 // 2048 bytes/page
#define TARGET_PACK_IDX_MASK            0x7FF // 0 to 2047   

#elif defined(BLD_NVM_TARGET_DEVICE_PIC32MM0064GPM0XX) // not complete

#if defined(__32MM0064GPM028_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0064GPM028"
#elif defined(__32MM0064GPM036_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0064GPM036"
#elif defined(__32MM0064GPM048_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0064GPM048"
#elif defined(__32MM0064GPM064_H)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC32MM0064GPM064"
#else
#error "Target MCU is not supported"
#endif

// Bootloader size is fixed in 20480 bytes (20kB)
// Application size is 65536-20480=45056 bytes (44kB)
#define BLD_NVM_TARGET_DEVICE_PAGE_SIZE FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS // (bytes)

#ifndef APP_RESET_ADDRESS
#define APP_RESET_ADDRESS               0x9D000000
#endif

#ifndef APP_BEGIN_ADDRESS
#define APP_BEGIN_ADDRESS               0x1D000000
#endif

#ifndef APP_END_ADDRESS
#define APP_END_ADDRESS                 0x1D00AFFF
#endif

#define APP_SIZE_IN_PAGE                22 // (pages)
#define TARGET_PACK_BYTE_MASK           0xFFFFF800 // 2048 bytes/page
#define TARGET_PACK_IDX_MASK            0x7FF // 0 to 2047   

#endif

#elif defined(BLD_NVM_TARGET_DEVICE_PIC18)
#if defined(_18F27K40)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC18F27K40"
#elif defined(_18LF27K40)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC18LF27K40"
#elif defined(_18F27J13)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC18F27J13"
#elif defined(_18LF27J13)
#define __BLD_NVM_TARGET_DEVICE_NAME__  "PIC18LF27J13"
#else
#error "Target MCU is not supported"
#endif
// Bootloader size is fixed in 20480 bytes (20kB)
// Application size is 131072-20480=110592 bytes (108kB)
#define BLD_NVM_TARGET_DEVICE_PAGE_SIZE ERASE_FLASH_BLOCKSIZE // (bytes)

#ifndef APP_RESET_ADDRESS
#define APP_RESET_ADDRESS               0x5000
#endif

#ifndef APP_INT_VECTOR_HIGH_ADDRESS
#define APP_INT_VECTOR_HIGH_ADDRESS     0x5008
#endif

#ifndef APP_INT_VECTOR_LOW_ADDRESS
#define APP_INT_VECTOR_LOW_ADDRESS      0x5018
#endif

#ifndef APP_BEGIN_ADDRESS
#define APP_BEGIN_ADDRESS               0x5000
#endif

#ifndef APP_END_ADDRESS
#define APP_END_ADDRESS                 (END_FLASH-1)
#endif

#ifndef APP_SIZE_IN_PAGE
#define APP_SIZE_IN_PAGE                ((APP_END_ADDRESS-APP_BEGIN_ADDRESS+1)/BLD_NVM_TARGET_DEVICE_PAGE_SIZE) // (pages)
#endif

#define TARGET_PACK_BYTE_MASK           0xFFFFFF80 // 128 bytes/page
#define TARGET_PACK_IDX_MASK            0x7F // 0 to 127

#else
#error "Please define BLD_NVM_TARGET_DEVICE_... in BLD_Nvm_Cfg.h"
#endif

#endif