/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  PIC32MM0256GPM036
    The generated drivers are tested against the following:
        Compiler          :  XC32 v2.50
        MPLAB             :  MPLAB X v5.50
*/
/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    // Enable Multi Vector Configuration
    INTCONbits.MVEC = 1;
    
    //    UERI: UART 1 Error
    //    Priority: 1
        IPC13bits.U1EIP = 1;
    //    Sub Priority: 2
        IPC13bits.U1EIS = 2;
    //    UTXI: UART 1 Transmission
    //    Priority: 1
        IPC13bits.U1TXIP = 1;
    //    Sub Priority: 1
        IPC13bits.U1TXIS = 1;
    //    URXI: UART 1 Reception
    //    Priority: 1
        IPC13bits.U1RXIP = 1;
    //    Sub Priority: 0
        IPC13bits.U1RXIS = 0;
    //    MICI: I2C 1 Master
    //    Priority: 2
        IPC16bits.I2C1MIP = 2;
    //    Sub Priority: 0
        IPC16bits.I2C1MIS = 0;
    //    SICI: I2C 1 Slave
    //    Priority: 2
        IPC16bits.I2C1SIP = 2;
    //    Sub Priority: 1
        IPC16bits.I2C1SIS = 1;
    //    MICI: I2C 2 Master
    //    Priority: 3
        IPC17bits.I2C2MIP = 3;
    //    Sub Priority: 0
        IPC17bits.I2C2MIS = 0;
    //    SICI: I2C 2 Slave
    //    Priority: 3
        IPC17bits.I2C2SIP = 3;
    //    Sub Priority: 1
        IPC17bits.I2C2SIS = 1;
}
