#ifndef BOOTLOADER_H
#define	BOOTLOADER_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "Bootloader_Cfg.h"
#endif

#ifndef USE_BOOTLOADER_BUILTIN_EXCEPTION
#define USE_BOOTLOADER_BUILTIN_EXCEPTION
#endif

#ifndef BOOTLOADER_DISABLE_INFO
#define BOOTLOADER_DISABLE_INFO
#endif

#ifndef BLD_Trigger_GetState
#define BLD_Trigger_GetState()   (1)
#warning "No trigger signal for bootloader"
#endif

#ifndef BLD_BUFFER_SIZE
#define BLD_BUFFER_SIZE         48
#endif

public void BootLoader_Initialize(void);
public void BootLoader_Deinitialize(void);
public void BootLoader_Tasks(void);

#endif