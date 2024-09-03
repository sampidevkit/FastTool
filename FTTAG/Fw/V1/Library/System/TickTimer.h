#ifndef TICKTIMER_H
#define TICKTIMER_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "TickTimer_Cfg.h"
#endif

#ifndef Tick_Timer_ActionWhileDelay
#define Tick_Timer_ActionWhileDelay(time) ClrWdt()
#endif

#if defined(__XC32) || defined(__XC16) || defined(__XC8)
#ifdef __XC32
#ifdef USE_SOFT_TMR
#define tick_t  uint64_t
#else
#define tick_t  uint32_t
#endif
#else
#define tick_t  uint32_t
#endif
#elif defined(__WIN32)
#define tick_t  uint32_t
#else
#error "Tick timer is not implemented for this platform"
#endif

typedef enum {
#if !defined(__WIN32) && defined(__XC32)
    US,
#endif
    MS,
    SEC
} tick_timer_type_t;

typedef struct {
    tick_t Start;
    tick_t Duration;
} __attribute_packed__ elapse_t;

typedef struct {
    volatile bool Timeout;
    tick_t Start;
    tick_t Duration;
} __attribute_packed__ tick_timer_t;

#if defined(__XC32) || defined(__WIN32)
extern volatile uint32_t TickTimer_SoftTmr;
#else
extern volatile uint16_t TickTimer_SoftTmr;
#endif

public tick_t Tick_Timer_Get_TickVal(void);
public void Tick_Timer_Init(void);
public void Delay(uint32_t Time, tick_timer_type_t TickType); // Do not use in multi-task mode
public bool Tick_Timer_Is_Over(tick_timer_t *pTick, uint32_t Time, tick_timer_type_t TickType);

#define Tick_Timer_Reset(x)                 (x.Timeout=1)
#define Tick_Timer_CallBack()               (TickTimer_SoftTmr++)

#ifdef __XC32
#define Delay_Us(Time)                      Delay(Time, US)
#define delay_us(t)                         Delay_Us(t)
#define __delay_us(t)                       Delay_Us(t)
#define Tick_GetTimeUs()                    (Tick_Timer_Get_TickVal() / TICK_PER_US)
#define Tick_Timer_Is_Over_Us(pTick, Time)  Tick_Timer_Is_Over(&pTick, Time, US)

#ifdef USE_SYS_SLEEP
#define system_sleep_us(t)                  Delay(t, US)
#endif
#endif

#define Delay_Ms(Time)                      Delay(Time, MS)
#define Delay_Sec(Time)                     Delay(Time, SEC)
#define delay_ms(t)                         Delay_Ms(t)
#define delay_sec(t)                        Delay_Sec(t)

#ifndef __XC8
#define __delay_ms(t)                       Delay_Ms(t)
#endif

#define __delay_sec(t)                      Delay_Sec(t)

#ifdef USE_SYS_SLEEP
#define system_sleep_ms(t)                  Delay(t, MS)
#define system_sleep_sec(t)                 Delay(t, SEC)
#endif

#define Tick_GetTimeMs()                    (Tick_Timer_Get_TickVal() / TICK_PER_MS)
#define Tick_GetTimeSec()                   (Tick_Timer_Get_TickVal() / TICK_PER_SEC)
#define Tick_Timer_Is_Over_Ms(pTick, Time)  Tick_Timer_Is_Over(&pTick, Time, MS)
#define Tick_Timer_Is_Over_Sec(pTick, Time) Tick_Timer_Is_Over(&pTick, Time, SEC)
#define Elapse_Create(name, t)              do{name.Start=Tick_Timer_Get_TickVal(); name.Duration=t*TICK_PER_MS;}while(0)
#define Elapse_Get(name)                    ((Tick_Timer_Get_TickVal()-name.Start)>name.Duration?1:0)
#define Elapse_Update(name)                 name.Start=Tick_Timer_Get_TickVal()

#endif