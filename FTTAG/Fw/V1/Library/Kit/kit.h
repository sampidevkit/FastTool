#ifndef KIT_H
#define KIT_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_cfg.h"
#endif

#ifndef KIT_STARTUP_DELAY
#define KIT_STARTUP_DELAY 2 // second
#endif

public void KIT_Tasks(void);

#endif