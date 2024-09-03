#ifndef KIT_USB_DEVICE_GENERIC_H
#define	KIT_USB_DEVICE_GENERIC_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_usb_device_cfg.h"
#endif

public bool KIT_USB_Device_GEN_Streaming(const char c);
public void KIT_USB_Device_GEN_TxTask(void *i);
public void KIT_USB_Device_GEN_RxTask(void *i);
public void KIT_USB_Device_GEN_EventInit(void);
public void KIT_USB_Device_GEN_Init(void);
public void KIT_USB_Device_GEN_Deinit(void);

#endif