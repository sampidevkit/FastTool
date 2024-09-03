#ifndef DEBUG_CFG_H
#define DEBUG_CFG_H

#include "uart/usart0.h"

static inline void debug_port_write(uint8_t c) {
    while (!USART0_IsTxReady());
    USART0_Write(c);
    while (!USART0_IsTxDone());
}

#endif