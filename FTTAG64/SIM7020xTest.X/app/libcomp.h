#ifndef LIBCOMP_H
#define LIBCOMP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "usb/usb.h"
#include "system.h"
#include "uart2.h"
#include "rtcc.h"
#include "memory/flash.h"
#include "watchdog.h"
#include "pin_manager.h"
#include "Bootloader/Bootloader.h"
#include "Common/Button.h"
#include "Common/Util.h"
#include "Common/LibDef.h"
#include "Tasks/TaskManager.h"
#include "Timer/Wdt.h"
#include "Timer/SystemTick.h"
#include "USB/USB_CDC_Debug.h"

#define USB_CDC_DISABLE_LED
//#undef __db
//#define __db(...)

#endif