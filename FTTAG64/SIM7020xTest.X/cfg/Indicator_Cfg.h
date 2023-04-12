#ifndef INDICATOR_CFG_H
#define INDICATOR_CFG_H

#define NUM_OF_INDICATORS       4
#define IND_ACTIVELOGIC         1
#define IND_INACTIVELOGIC       0

#define LED1_SetState           ST_LED_SetValue
#define RLED_SetHigh()          Indicator_SetState(0, 1, 0, IND_LOOP_FOREVER)
#define RLED_SetLow()           Indicator_SetState(0, 0, 1, IND_LOOP_FOREVER)
#define RLED_OneShot(Ton)       Indicator_SetState(0, Ton, 1, 1)
#define RLED_Toggle(Ton, Toff)  Indicator_SetState(0, Ton, Toff, IND_LOOP_FOREVER)

#define LED2_SetState           RX_LED_SetValue
#define GLED_SetHigh()          Indicator_SetState(1, 1, 0, IND_LOOP_FOREVER)
#define GLED_SetLow()           Indicator_SetState(1, 0, 1, IND_LOOP_FOREVER)
#define GLED_OneShot(Ton)       Indicator_SetState(1, Ton, 1, 1)
#define GLED_Toggle(Ton, Toff)  Indicator_SetState(1, Ton, Toff, IND_LOOP_FOREVER)

#define LED3_SetState           TX_LED_SetValue
#define BLED_SetHigh()          Indicator_SetState(2, 1, 0, IND_LOOP_FOREVER)
#define BLED_SetLow()           Indicator_SetState(2, 0, 1, IND_LOOP_FOREVER)
#define BLED_OneShot(Ton)       Indicator_SetState(2, Ton, 1, 1)
#define BLED_Toggle(Ton, Toff)  Indicator_SetState(2, Ton, Toff, IND_LOOP_FOREVER)

#define LED4_SetState           TG_MCLR_N_SetValue
#define MCLR_TRIG_SetHigh()     Indicator_SetState(3, 1, 0, IND_LOOP_FOREVER)
#define MCLR_TRIG_SetLow()      Indicator_SetState(3, 0, 1, IND_LOOP_FOREVER)
#define MCLR_TRIG_OneShot(Ton)  Indicator_SetState(3, Ton, 1, 1)

#endif