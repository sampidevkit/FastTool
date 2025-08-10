#include <stdio.h>
#include "VCP_Debug.h"
#include "common/Debug.h"

void _mon_putc(char c)
{
    VCP_Debug_Write(c);
    
    while(!VCP_Debug_IsTxDone())
        SYS_Wait();
}

void debug_port_write(uint8_t c)
{
    VCP_Debug_Write(c);
    
    while(!VCP_Debug_IsTxDone())
        SYS_Wait();
}
