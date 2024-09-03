#ifndef WDT_CFG_H
#define WDT_CFG_H

#define ClrWdt()                WATCHDOG_TimerClear()
#define WDT_Task_UserCb()
#define WDT_STT_LED_Toggle()    do{RX_LED_Toggle(); TX_LED_Toggle();}while(0)
#define WDT_STT_LED_SetHigh()   do{RX_LED_SetHigh(); TX_LED_SetLow();}while(0)
#define WDT_STT_LED_SetLow()    do{RX_LED_SetLow(); TX_LED_SetHigh();}while(0)

#endif