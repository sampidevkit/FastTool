/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*DBG_RXD_InterruptHandler)(void);
static void (*DBG_TXD_InterruptHandler)(void);
static void (*SCL_InterruptHandler)(void);
static void (*SDA_InterruptHandler)(void);
static void (*VIO_OUT_InterruptHandler)(void);
static void (*VIO_SEN_InterruptHandler)(void);
static void (*IO_PA3_InterruptHandler)(void);
static void (*IO_PA4_InterruptHandler)(void);
static void (*IO_PA5_InterruptHandler)(void);
static void (*BT_SET_N_InterruptHandler)(void);
static void (*RLED1_N_InterruptHandler)(void);
static void (*VCP_RESET_N_InterruptHandler)(void);
static void (*BLED2_N_InterruptHandler)(void);
static void (*RLED2_N_InterruptHandler)(void);
static void (*BLED1_N_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0xC1;
    PORTC.DIR = 0xC;
    PORTD.DIR = 0xF0;
    PORTF.DIR = 0x0;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x41;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0xB0;
    PORTF.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x8;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x0;
    PORTF.PIN7CTRL = 0x0;

  /* EVGENCTRL registers Initialization */

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x1;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCDROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x2;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    DBG_RXD_SetInterruptHandler(DBG_RXD_DefaultInterruptHandler);
    DBG_TXD_SetInterruptHandler(DBG_TXD_DefaultInterruptHandler);
    SCL_SetInterruptHandler(SCL_DefaultInterruptHandler);
    SDA_SetInterruptHandler(SDA_DefaultInterruptHandler);
    VIO_OUT_SetInterruptHandler(VIO_OUT_DefaultInterruptHandler);
    VIO_SEN_SetInterruptHandler(VIO_SEN_DefaultInterruptHandler);
    IO_PA3_SetInterruptHandler(IO_PA3_DefaultInterruptHandler);
    IO_PA4_SetInterruptHandler(IO_PA4_DefaultInterruptHandler);
    IO_PA5_SetInterruptHandler(IO_PA5_DefaultInterruptHandler);
    BT_SET_N_SetInterruptHandler(BT_SET_N_DefaultInterruptHandler);
    RLED1_N_SetInterruptHandler(RLED1_N_DefaultInterruptHandler);
    VCP_RESET_N_SetInterruptHandler(VCP_RESET_N_DefaultInterruptHandler);
    BLED2_N_SetInterruptHandler(BLED2_N_DefaultInterruptHandler);
    RLED2_N_SetInterruptHandler(RLED2_N_DefaultInterruptHandler);
    BLED1_N_SetInterruptHandler(BLED1_N_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for DBG_RXD at application runtime
*/
void DBG_RXD_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_RXD_InterruptHandler = interruptHandler;
}

void DBG_RXD_DefaultInterruptHandler(void)
{
    // add your DBG_RXD interrupt custom code
    // or set custom function using DBG_RXD_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DBG_TXD at application runtime
*/
void DBG_TXD_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DBG_TXD_InterruptHandler = interruptHandler;
}

void DBG_TXD_DefaultInterruptHandler(void)
{
    // add your DBG_TXD interrupt custom code
    // or set custom function using DBG_TXD_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SCL at application runtime
*/
void SCL_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SCL_InterruptHandler = interruptHandler;
}

void SCL_DefaultInterruptHandler(void)
{
    // add your SCL interrupt custom code
    // or set custom function using SCL_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SDA at application runtime
*/
void SDA_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SDA_InterruptHandler = interruptHandler;
}

void SDA_DefaultInterruptHandler(void)
{
    // add your SDA interrupt custom code
    // or set custom function using SDA_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for VIO_OUT at application runtime
*/
void VIO_OUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VIO_OUT_InterruptHandler = interruptHandler;
}

void VIO_OUT_DefaultInterruptHandler(void)
{
    // add your VIO_OUT interrupt custom code
    // or set custom function using VIO_OUT_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for VIO_SEN at application runtime
*/
void VIO_SEN_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VIO_SEN_InterruptHandler = interruptHandler;
}

void VIO_SEN_DefaultInterruptHandler(void)
{
    // add your VIO_SEN interrupt custom code
    // or set custom function using VIO_SEN_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA3 at application runtime
*/
void IO_PA3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA3_InterruptHandler = interruptHandler;
}

void IO_PA3_DefaultInterruptHandler(void)
{
    // add your IO_PA3 interrupt custom code
    // or set custom function using IO_PA3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA4 at application runtime
*/
void IO_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA4_InterruptHandler = interruptHandler;
}

void IO_PA4_DefaultInterruptHandler(void)
{
    // add your IO_PA4 interrupt custom code
    // or set custom function using IO_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA5 at application runtime
*/
void IO_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA5_InterruptHandler = interruptHandler;
}

void IO_PA5_DefaultInterruptHandler(void)
{
    // add your IO_PA5 interrupt custom code
    // or set custom function using IO_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BT_SET_N at application runtime
*/
void BT_SET_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BT_SET_N_InterruptHandler = interruptHandler;
}

void BT_SET_N_DefaultInterruptHandler(void)
{
    // add your BT_SET_N interrupt custom code
    // or set custom function using BT_SET_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RLED1_N at application runtime
*/
void RLED1_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RLED1_N_InterruptHandler = interruptHandler;
}

void RLED1_N_DefaultInterruptHandler(void)
{
    // add your RLED1_N interrupt custom code
    // or set custom function using RLED1_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for VCP_RESET_N at application runtime
*/
void VCP_RESET_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    VCP_RESET_N_InterruptHandler = interruptHandler;
}

void VCP_RESET_N_DefaultInterruptHandler(void)
{
    // add your VCP_RESET_N interrupt custom code
    // or set custom function using VCP_RESET_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BLED2_N at application runtime
*/
void BLED2_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BLED2_N_InterruptHandler = interruptHandler;
}

void BLED2_N_DefaultInterruptHandler(void)
{
    // add your BLED2_N interrupt custom code
    // or set custom function using BLED2_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for RLED2_N at application runtime
*/
void RLED2_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    RLED2_N_InterruptHandler = interruptHandler;
}

void RLED2_N_DefaultInterruptHandler(void)
{
    // add your RLED2_N interrupt custom code
    // or set custom function using RLED2_N_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BLED1_N at application runtime
*/
void BLED1_N_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BLED1_N_InterruptHandler = interruptHandler;
}

void BLED1_N_DefaultInterruptHandler(void)
{
    // add your BLED1_N interrupt custom code
    // or set custom function using BLED1_N_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       DBG_RXD_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       DBG_TXD_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       VIO_SEN_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       IO_PA3_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       IO_PA4_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       IO_PA5_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       RLED1_N_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       VCP_RESET_N_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       SCL_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       SDA_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       BT_SET_N_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       VIO_OUT_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       BLED2_N_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       RLED2_N_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       BLED1_N_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/