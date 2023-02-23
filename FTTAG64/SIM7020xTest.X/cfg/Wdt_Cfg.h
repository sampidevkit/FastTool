#ifndef WDT_CFG_H
#define WDT_CFG_H

#define ClrWdt()                WATCHDOG_TimerClear()
#define WDT_STT_LED_Toggle()    ST_LED_Toggle()
#define WDT_STT_LED_SetHigh()   ST_LED_SetHigh()
#define WDT_STT_LED_SetLow()    ST_LED_SetLow()

#endif