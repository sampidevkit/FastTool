#ifndef DEBUG_H
#define	DEBUG_H

#include "Common/LibDef.h"
#include "System/TaskManager.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "Debug_Cfg.h"
#endif

typedef enum DEBUG_MASK_TYPE {
    DEBUG_NONE_MASK = 0,
    DEBUG_ERROR,
    DEBUG_WARNING,
    DEBUG_INFO
} debug_mask_t;

extern sem_declare_t(sys_debug);

public void Debug_SetStreamFnc(bool (*pStrFnc)(const char c));

#define task_debug(...)     mutex_lock(sys_debug, printf(__VA_ARGS__))
#define nontask_debug(...)  sem_wait(sys_debug, printf(__VA_ARGS__))

#endif