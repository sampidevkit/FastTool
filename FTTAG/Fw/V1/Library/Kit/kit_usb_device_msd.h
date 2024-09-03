#ifndef KIT_USB_DEVICE_MSD_H
#define KIT_USB_DEVICE_MSD_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_usb_device_cfg.h"
#endif

public void KIT_USB_Device_MSD_Init(void);
public void KIT_USB_Device_MSD_Deinit(void);
public void KIT_USB_Device_MSD_Tasks(void *);
public void KIT_USB_Device_MSD_EventInit(void);

#endif