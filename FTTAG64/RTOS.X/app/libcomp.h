#ifndef LIBCOMP_H
#define LIBCOMP_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "tmr2.h"
#include "tmr3.h"
#include "system.h"
#include "watchdog.h"
#include "pin_manager.h"
#include "Bootloader/Bootloader.h"
#include "Common/Button.h"
#include "Timer/SystemTick.h"

#define BOOTLOADER_TASK_PRIORITY    (tskIDLE_PRIORITY+1)
#define APPLICATION_TASK_PRIORITY   (tskIDLE_PRIORITY+2)
#define USB_CDC_TASK_PRIORITY       (tskIDLE_PRIORITY+3)

#endif