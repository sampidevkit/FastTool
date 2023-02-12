#ifndef LIBCOMP_H
#define LIBCOMP_H

#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "usb/usb.h"
#include "system.h"
#include "watchdog.h"
#include "pin_manager.h"
#include "Common/Util.h"
#include "Timer/SystemTick.h"
#include "USB/USB_CDC_Debug.h"
#include "drivers/i2c_master.h"

#define MOD_GetValue()   BT_N_GetValue()
#include "Common/Button.h"

#define USE_DEFAULT_BUTTON
#include "Bootloader/Bootloader.h"

#endif