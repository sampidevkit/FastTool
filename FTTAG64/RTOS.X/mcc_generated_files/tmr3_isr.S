#include <p32xxxx.h>
#include <sys/asm.h>
#include "ISR_Support.h"

/* Copy this line to your C source
void __attribute__((vector (_TIMER_2_VECTOR), interrupt(IPL2SOFT))) TMR3_ISR(); 
void TMR3_ISR_HANDLER(void)*/

       .set    nomips16
       .set    noreorder

       .extern TMR3_ISR_HANDLER
       .extern xISRStackTop
       .global TMR3_ISR

       .set    noreorder
       .set    noat
       .ent    TMR3_ISR

TMR3_ISR:

       portSAVE_CONTEXT
   jal TMR3_ISR_HANDLER
   nop
       portRESTORE_CONTEXT

   .end        TMR3_ISR
