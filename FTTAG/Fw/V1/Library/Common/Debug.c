#include "Debug.h"
#include "libcomp.h"

// extern variable 
public sem_declare(sys_debug);

private bool(*StreamerFunction)(const char c);

public void _mon_putc(char c) // <editor-fold defaultstate="collapsed" desc="be used for printf function">
{
    if(StreamerFunction!=NULL)
    {
        while(!StreamerFunction(c));
    }
} // </editor-fold>

public void Debug_SetStreamFnc(bool(*pStrFnc)(const char c)) // <editor-fold defaultstate="collapsed" desc="Set stream function">
{
    Disable_Global_Interrupt();
    StreamerFunction=pStrFnc;
    Enable_Global_Interrupt();
} // </editor-fold>