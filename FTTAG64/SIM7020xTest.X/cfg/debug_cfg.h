#ifndef DEBUG_CFG_H
#define DEBUG_CFG_H

#include "USB/USB_CDC_Debug.h"

#define debug_port_write(b) _mon_putc((char)b)

#endif