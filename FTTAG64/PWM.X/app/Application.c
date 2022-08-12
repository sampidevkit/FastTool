#include "libcomp.h"
#include "Application.h"

static tick_t Tick;
uint16_t Duty1, Duty2, Duty3;

static void Duty_Reset(void)
{
    __db("\nPresent duty: %d, %d, %d", Duty1, Duty2, Duty3);
    __db("\nDuty reset");
    Duty1=0;
    Duty2=0;
    Duty3=0;
    Tick_Reset(Tick);
}

void Application_Init(void)
{
    Duty_Reset();
    MOD_Button_SetSinglePress_Event(Duty_Reset);
}

void Application_Tasks(void)
{
    if(Tick_Is_Over_Ms(&Tick, 50))
    {
        CCP4RA=Duty1;
        CCP5RA=Duty2;
        CCP6RA=Duty3;

        Duty1+=3;
        Duty2+=5;
        Duty3+=7;

        if(CCP4PR>0)
            Duty1%=CCP4PR;

        if(CCP5PR>0)
            Duty2%=CCP5PR;

        if(CCP6PR>0)
            Duty3%=CCP6PR;
    }
}