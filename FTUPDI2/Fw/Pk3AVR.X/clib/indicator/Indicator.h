#ifndef INDICATOR_H
#define	INDICATOR_H

#include "Common/LibDef.h"
#include "Project_Cfg.h"

#ifndef IND_ACTIVELOGIC
#define IND_ACTIVELOGIC         1
#define IND_INACTIVELOGIC       0
#elif(IND_ACTIVELOGIC==1)
#define IND_INACTIVELOGIC       0
#else
#define IND_INACTIVELOGIC       1
#endif

#define IND_LOOP_FOREVER        0xFFFF
#define Indicator_SetHigh(idx)  Indicator_SetState(idx, 1, 0, IND_LOOP_FOREVER)
#define Indicator_SetLow(idx)   Indicator_SetState(idx, 0, 1, IND_LOOP_FOREVER)
#define Indicator_OneShot(idx, Ton) Indicator_SetState(idx, Ton, 1, 1)
#define Indicator_Toggle(idx, Ton, Toff) Indicator_SetState(idx, Ton, Toff, IND_LOOP_FOREVER)

/* ******************************************************* External Prototype */
void LED1_SetState(bool state);
void LED2_SetState(bool state);
void LED3_SetState(bool state);
void LED4_SetState(bool state);
void LED5_SetState(bool state);
void LED6_SetState(bool state);
void LED7_SetState(bool state);
void LED8_SetState(bool state);
void LED9_SetState(bool state);
void LED10_SetState(bool state);

/* ************************************************************************** */
public void Indicator_Init(void);
public void Indicator_Tasks(void *);
public void Indicator_SetState(uint8_t Idx, uint16_t TOn, uint16_t TOff, uint16_t Loop);
public void Indicator_Stop(uint8_t Idx);

#endif