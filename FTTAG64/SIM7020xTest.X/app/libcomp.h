#ifndef LIBCOMP_H
#define LIBCOMP_H
/* *********************************************************** System library */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* ************************************************************** MCC library */
#include "clock.h"
#include "system.h"
#include "pin_manager.h"
#include "usb/usb_device_cdc.h"

/* ****************************************************** Application library */
#include "Bootloader/Bootloader.h"
#include "Common/Button.h"
#include "Common/Util.h"
#include "Common/AtCmd.h"
#include "Common/Indicator.h"
#include "Common/debug.h"
#include "Tasks/TaskManager.h"
#include "Timer/Wdt.h"
#include "Timer/SystemTick.h"
#include "USB/USB_CDC_Debug.h"

#define CELL_PWR_EN_SetLow()
#define CELL_PWR_EN_SetHigh()

#endif