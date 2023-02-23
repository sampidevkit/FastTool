#include "libcomp.h"
#include "Indicator.h"
#include "Timer/SystemTick.h"
#include "Tasks/TaskManager.h"

#if(NUM_OF_INDICATORS>=2)
#ifndef LED2_SetState
#define LED2_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED2_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=3)
#ifndef LED3_SetState
#define LED3_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED3_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=4)
#ifndef LED4_SetState
#define LED4_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED4_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=5)
#ifndef LED5_SetState
#define LED5_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED5_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=6)
#ifndef LED6_SetState
#define LED6_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED6_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=7)
#ifndef LED7_SetState
#define LED7_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED7_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=8)
#ifndef LED8_SetState
#define LED8_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED8_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=9)
#ifndef LED9_SetState
#define LED9_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED9_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>=10)
#ifndef LED10_SetState
#define LED10_SetState(x) Indicator_DummyIo(x)
#warning "Please define LED10_SetState function"
#endif
#endif

#if(NUM_OF_INDICATORS>10)
#error "This driver supports maximum 10 LED indicators"
#endif

typedef struct INDICATOR_CONTEXT
{
    uint8_t Task;
    uint16_t Ton;
    uint16_t Toff;
    uint16_t Loop;
    tick_timer_t Tick;
    void (*pIO)(bool);
} indicator_cxt_t;

private uint8_t IndIdx;
private indicator_cxt_t IndCxt[NUM_OF_INDICATORS];

private void Indicator_DummyIo(bool Logic)
{

}

private void Indicator_Process(indicator_cxt_t *pIndCxt)
{
    if(pIndCxt==NULL)
        return;

    switch(pIndCxt->Task)
    {
        case 0:
            if(Tick_Timer_Is_Over_Ms(pIndCxt->Tick, pIndCxt->Ton))
            {
                pIndCxt->pIO(IND_INACTIVELOGIC);

                if(pIndCxt->Loop==IND_LOOP_FOREVER)
                    pIndCxt->Task=0x01;
                else if(pIndCxt->Loop>1)
                {
                    pIndCxt->Loop--;
                    pIndCxt->Task=0x01;
                }
                else
                    pIndCxt->Task=0xFF;
            }
            break;

        case 1:
            if(Tick_Timer_Is_Over_Ms(pIndCxt->Tick, pIndCxt->Toff))
            {
                pIndCxt->Task=0x00;
                pIndCxt->pIO(IND_ACTIVELOGIC);
            }
            break;

        default:
            break;
    }
}

private new_simple_task_t(Indicator_Tasks)
{
    Indicator_Process(&IndCxt[IndIdx++]);

    if(IndIdx>=NUM_OF_INDICATORS)
        IndIdx=0;

    Task_Done();
}

public void Indicator_Init(void)
{
    for(IndIdx=0; IndIdx<NUM_OF_INDICATORS; IndIdx++)
    {
        IndCxt[IndIdx].Loop=0;
        IndCxt[IndIdx].Task=0;
        Tick_Timer_Reset(IndCxt[IndIdx].Tick);

        switch(IndIdx)
        {
            case 0:
                IndCxt[IndIdx].pIO=LED1_SetState;
                break;

#if(NUM_OF_INDICATORS>=2)
            case 1:
                IndCxt[IndIdx].pIO=LED2_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=3)
            case 2:
                IndCxt[IndIdx].pIO=LED3_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=4)
            case 3:
                IndCxt[IndIdx].pIO=LED4_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=5)
            case 4:
                IndCxt[IndIdx].pIO=LED5_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=6)
            case 5:
                IndCxt[IndIdx].pIO=LED6_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=7)
            case 6:
                IndCxt[IndIdx].pIO=LED7_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=8)
            case 7:
                IndCxt[IndIdx].pIO=LED8_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=9)
            case 8:
                IndCxt[IndIdx].pIO=LED9_SetState;
                break;
#endif

#if(NUM_OF_INDICATORS>=10)
            case 9:
                IndCxt[IndIdx].pIO=LED10_SetState;
                break;
#endif                

            default:
                break;
        }
    }

    IndIdx=0;
    TaskManager_Create_NewSimpleTask(Indicator_Tasks);
}

public void Indicator_SetState(uint8_t Idx, uint16_t TOn, uint16_t TOff, uint16_t Loop)
{
    if(Idx>=NUM_OF_INDICATORS)
        return;

    IndCxt[Idx].Task=0xFF;
    // Update new config
    if(TOn==0)
        IndCxt[Idx].pIO(IND_INACTIVELOGIC);
    else if(TOff==0)
        IndCxt[Idx].pIO(IND_ACTIVELOGIC);
    else
    {
        IndCxt[Idx].Ton=TOn;
        IndCxt[Idx].Toff=TOff;
        IndCxt[Idx].Loop=Loop;

        if(Loop>0)
        {
            IndCxt[Idx].Task=0;
            IndCxt[Idx].pIO(IND_ACTIVELOGIC);
            Tick_Timer_Reset(IndCxt[Idx].Tick);
        }
        else
            IndCxt[Idx].pIO(IND_INACTIVELOGIC);
    }
}

public void Indicator_Stop(uint8_t Idx)
{
    if(Idx>=NUM_OF_INDICATORS)
        return;

    IndCxt[Idx].pIO(IND_INACTIVELOGIC);
    IndCxt[Idx].Task=0xFF;
}