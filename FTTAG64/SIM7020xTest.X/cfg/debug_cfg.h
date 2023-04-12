#ifndef DEBUG_CFG_H
#define DEBUG_CFG_H

#include <xc.h>
#include <stdio.h>

#define debug_port_write(b) _mon_putc((char)b)

#endif