#include "Wdt.h"
#include "libcomp.h"

#ifndef SYSTEM_RegUnlock
#define SYSTEM_RegUnlock()
#endif

private tick_timer_t Tick={1, 0, 0};

public void SYS_SoftReset(void) // <editor-fold defaultstate="collapsed" desc="Software reset">
{
    SYSTEM_RegUnlock();
    
#ifdef __XC32
    RSWRSTSET=1;
	/* read RSWRST register to trigger reset */
    unsigned int dummy=RSWRST;
#elif defined(__XC16)
    asm ("RESET");
#elif defined(__XC8)
    RESET();
#else
    // implement your code
#endif
    
    while(1);
} // </editor-fold>

public new_simple_task_t(WDT_Tasks) // <editor-fold defaultstate="collapsed" desc="WDT tasks">
{
    if(Tick_Timer_Is_Over_Ms(Tick, 500))
    {
        ClrWdt();
        WDT_STT_LED_Toggle();
    }
    
    WDT_Task_UserCb();
    
    Task_Done();
} // </editor-fold>

public void WDT_Enable(void) // <editor-fold defaultstate="collapsed" desc="WDT enable">
{
    WDT_STT_LED_SetHigh();
    TaskManager_Create_NewSimpleTask(WDT_Tasks);
} // </editor-fold>

public void WDT_Disable(void) // <editor-fold defaultstate="collapsed" desc="WDT disable">
{
    WDT_STT_LED_SetLow();
    TaskManager_End_Task(WDT_Tasks);
} // </editor-fold>