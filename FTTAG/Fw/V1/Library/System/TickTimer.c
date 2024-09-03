#include "libcomp.h"
#include "TickTimer.h"

#if defined(__XC32) || defined(__WIN32)
volatile uint32_t TickTimer_SoftTmr=0;
#else
volatile uint16_t TickTimer_SoftTmr=0;
#endif

public tick_t Tick_Timer_Get_TickVal(void) // <editor-fold defaultstate="collapsed" desc="Get tick value">
{
#ifdef __WIN32
    return clock();
#else
#ifdef USE_SOFT_TMR
    tick_t CurTick;
    uint32_t CurCount;

    // prevent from overlapping of TickTimer_SoftTmr value
    do
    {
        CurCount=TickTimer_SoftTmr;
        CurTick=CurCount;

#ifdef __XC32
        CurTick<<=32;
#else
        CurTick<<=16;
#endif
        CurTick|=Tick_Timer_Read();
    }
    while(TickTimer_SoftTmr!=CurCount);

    return CurTick;
#else
    return Tick_Timer_Read();
#endif
#endif
} // </editor-fold>

public bool Tick_Timer_Is_Over(tick_timer_t *pTick, uint32_t Time, tick_timer_type_t TickType) // <editor-fold defaultstate="collapsed" desc="Check tick over microsecond">
{
    if(pTick->Timeout)
    {
        pTick->Timeout=0;

#if !defined(__WIN32) && defined(__XC32)
        if(TickType==US)
            pTick->Duration=TICK_PER_US*Time;
        else if(TickType==MS)
#else
        if(TickType==MS)
#endif
            pTick->Duration=TICK_PER_MS*Time;
        else
            pTick->Duration=TICK_PER_SEC*Time;

        pTick->Start=Tick_Timer_Get_TickVal();
    }

    if((Tick_Timer_Get_TickVal()-pTick->Start)>=pTick->Duration)
    {
        pTick->Timeout=1;
        return 1;
    }

    return 0;
} // </editor-fold>

public void Delay(uint32_t Time, tick_timer_type_t TickType) // <editor-fold defaultstate="collapsed" desc="Delay">
{
#ifndef USE_SYS_SLEEP
    tick_t Duration;
    tick_t Start=Tick_Timer_Get_TickVal();

#if !defined(__WIN32) && defined(__XC32)
    if(TickType==US)
        Duration=TICK_PER_US*Time;
    else if(TickType==MS)
#else
    if(TickType==MS)
#endif
        Duration=TICK_PER_MS*Time;
    else
        Duration=TICK_PER_SEC*Time;

    while((Tick_Timer_Get_TickVal()-Start)<Duration)
        Tick_Timer_ActionWhileDelay(NULL);
#else
#if !defined(__WIN32) && defined(__XC32)
    if(TickType==MS)
        Time*=1000;
    else if(TickType==SEC)
        Time*=1000000;
#else
    if(TickType==SEC)
        Time*=1000;
#endif
    Tick_Timer_ActionWhileDelay(Time);
#endif
} // </editor-fold>

public void Tick_Timer_Init(void) // <editor-fold defaultstate="collapsed" desc="Tick timer initialize, call first and 1 time">
{
    Disable_Coretimer_Interrupt();
    TickTimer_SoftTmr=0;
#ifdef Tick_Timer_Set_SwTmr_Isr
    Tick_Timer_Set_SwTmr_Isr(Tick_Timer_CallBack);
#else
#warning "Please define macro Tick_Timer_Set_SwTmr_Isr(Tmr_Isr) point to timer ISR function"
#endif
    Enable_Coretimer_Interrupt();

#ifdef __WIN32
    srand((unsigned int) time(NULL));
#endif
} // </editor-fold>