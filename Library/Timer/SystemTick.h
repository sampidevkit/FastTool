#ifndef SYSTEMTICK_H
#define SYSTEMTICK_H

#include <stdint.h>
#include <stdbool.h>

#define TICK_PER_MS     12000
#define TICK_PER_US     12
#define Tick_Reset(cxt) cxt.Over=1

typedef struct {
    bool Over;
    uint32_t Begin;
    uint32_t End;
} tick_t;

void __delay_us(uint32_t t);
void __delay_ms(uint32_t t);
bool Tick_Is_Over(tick_t *pTick, uint32_t us);

#define Tick_Get()                  (_CP0_GET_COUNT())
#define Tick_Dif(tk1, tk2)          ((tk1)-(tk2))
#define Tick_Dif_Us(tk1, tk2)       (((tk1)-(tk2))/TICK_PER_US)
#define Tick_Dif_Ms(tk1, tk2)       (((tk1)-(tk2))/TICK_PER_MS)
#define Tick_Is_Over_Us(pTick, us)  Tick_Is_Over(pTick, us)
#define Tick_Is_Over_Ms(pTick, ms)  Tick_Is_Over(pTick, 1000*(ms))

#endif