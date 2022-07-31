#include <p32xxxx.h>
#include <sys/asm.h>
#include "ISR_Support.h"

/* Copy this line to your C source
void __attribute__((vector (_TIMER_2_VECTOR), interrupt(IPL2SOFT))) TMR2_ISR(); 
void TMR2_ISR_HANDLER(void)*/

       .set    nomips16
       .set    noreorder

       .extern TMR2_ISR_HANDLER
       .extern xISRStackTop
       .global TMR2_ISR

       .set    noreorder
       .set    noat
       .ent    TMR2_ISR

TMR2_ISR:

       portSAVE_CONTEXT
   jal TMR2_ISR_HANDLER
   nop
       portRESTORE_CONTEXT

   .end        TMR2_ISR
