#include "libcomp.h"
#include "Application.h"

static struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t phase;
} Rgb;

static tick_t Tick;

static void Duty_Reset(void)
{
    __db("\nPresent duty: %d, %d, %d", Rgb.red, Rgb.green, Rgb.blue);
    __db("\nDuty reset");
    Rgb.red=255;
    Rgb.green=255;
    Rgb.blue=1;
    Rgb.phase=0;
    Tick_Reset(Tick);
}

void Application_Init(void)
{
    Rgb.red=255;
    Rgb.green=255;
    Rgb.blue=1;
    Rgb.phase=0;
    Tick_Reset(Tick);
    MOD_Button_SetSinglePress_Event(Duty_Reset);
}

void Application_Tasks(void)
{
    if(Tick_Is_Over_Ms(&Tick, 50))
    {
        switch(Rgb.phase)
        {
            default:
            case 0: // R max,       G decrease, B increase
                if(Rgb.green>1)
                {
                    Rgb.green--;
                    Rgb.blue++;
                }
                else
                {
                    Rgb.phase=1;
                    __db("\nDuty: %d, %d, %d", Rgb.red, Rgb.green, Rgb.blue);
                    __db("\nNew phase: %d", Rgb.phase);
                }
                break;

            case 1: // R decrease,  G increase,      B max
                if(Rgb.red>1)
                {
                    Rgb.red--;
                    Rgb.green++;
                }
                else
                {
                    Rgb.phase=2;
                    __db("\nDuty: %d, %d, %d", Rgb.red, Rgb.green, Rgb.blue);
                    __db("\nNew phase: %d", Rgb.phase);
                }
                break;

            case 2: // R increase,  G max, B decrese
                if(Rgb.blue>1)
                {
                    Rgb.blue--;
                    Rgb.red++;
                }
                else
                {
                    Rgb.phase=0;
                    __db("\nDuty: %d, %d, %d", Rgb.red, Rgb.green, Rgb.blue);
                    __db("\nNew phase: %d", Rgb.phase);
                }
                break;
        }

        CCP4RA=Rgb.red;
        CCP5RA=Rgb.green;
        CCP6RA=Rgb.blue;
    }
}