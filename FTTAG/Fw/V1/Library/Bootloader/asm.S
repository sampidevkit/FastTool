/*
    ** file: asm.S
    */
#include <xc.h>
#include "BLD_Target_Device.h"
    
    .text
    .set noreorder 
/*********************************************************************
* void appFunction(void)
* This function jump specified address
********************************************************************/
.global appFunction
.ent appFunction
appFunction:
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    jals APP_RESET_ADDRESS /* 0x9D005000 */
    nop
    
.end appFunction     
    