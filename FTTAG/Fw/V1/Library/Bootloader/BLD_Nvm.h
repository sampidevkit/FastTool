#ifndef BLD_NVM_H
#define	BLD_NVM_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "BLD_Nvm_Cfg.h"
#endif

#ifndef bld_nvm_write_log
#define bld_nvm_write_log(...)
#endif

#ifndef bld_nvm_write_error_log
#define bld_nvm_write_error_log(line)
#endif

#ifndef BLD_Nvm_Lock
#define BLD_Nvm_Lock()
#endif

#ifndef BLD_Nvm_UnLock
#define BLD_Nvm_UnLock()
#endif

#ifndef BLD_Nvm_SystemReboot
#define BLD_Nvm_SystemReboot() BootLoader_Deinitialize()
#endif

#if defined(BLD_NVM_TARGET_DEVICE_PIC18)
#include "BLD_Nvm_PIC18.h"
#elif defined(BLD_NVM_TARGET_DEVICE_PIC32)
#include "BLD_Nvm_PIC32.h"
#else
#error "Not support device"
#endif

#endif