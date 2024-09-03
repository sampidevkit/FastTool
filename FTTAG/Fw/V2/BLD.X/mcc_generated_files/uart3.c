/**
  UART3 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    uart3.c

  @Summary
    This is the generated driver implementation file for the UART3 driver using Foundation Services Library

  @Description
    This header file provides implementations for driver APIs for UART3.
    Generation Information :
        Product Revision  :  Foundation Services Library - pic24-dspic-pic32mm : v1.26
        Device            :  PIC32MM0256GPM036
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.42
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
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
  Section: Included Files
*/
#include <xc.h>
#include "uart3.h"

/**
  Section: UART3 APIs
*/

void UART3_Initialize(void)
{
    // Set the UART3 module to the options selected in the user interface.

    // STSEL 1; PDSEL 8N; RTSMD disabled; OVFDIS disabled; ACTIVE disabled; RXINV disabled; WAKE disabled; BRGH enabled; IREN disabled; ON enabled; SLPEN disabled; SIDL disabled; ABAUD disabled; LPBACK disabled; UEN TX_RX; CLKSEL SYSCLK; 
    U3MODE = (0x28008 & ~(1<<15)); // disabling UART ON bit  
    // UTXISEL TX_ONE_CHAR; UTXINV disabled; ADDR 0; MASK 0; URXEN disabled; OERR disabled; URXISEL RX_ONE_CHAR; UTXBRK disabled; UTXEN disabled; ADDEN disabled; 
    U3STA = 0x0;
    // BaudRate = 115200; Frequency = 24000000 Hz; BRG 51; 
    U3BRG = 0x33;
     
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U3STASET = _U3STA_UTXEN_MASK;
    U3MODESET = _U3MODE_ON_MASK;  // enabling UART ON bit
    U3STASET = _U3STA_URXEN_MASK; 
}

uint8_t UART3_Read(void)
{
    while(!(U3STAbits.URXDA == 1))
    {
    }

    if ((U3STAbits.OERR == 1))
    {
        U3STACLR = _U3STA_OERR_MASK;
    }

    return U3RXREG;
}

void UART3_Write(uint8_t txData)
{
    while(U3STAbits.UTXBF == 1)
    {
    }

    U3TXREG = txData;    // Write the data byte to the USART.
}

bool UART3_IsRxReady(void)
{
    return U3STAbits.URXDA;
}

bool UART3_IsTxReady(void)
{
    return (U3STAbits.TRMT && U3STAbits.UTXEN );
}

bool UART3_IsTxDone(void)
{
    return U3STAbits.TRMT;
}

/* !!! Deprecated API - This function may not be supported in a future release !!! */
UART3_STATUS __attribute__((deprecated)) UART3_StatusGet (void)
{
    return U3STA;
}

/* !!! Deprecated API - This function may not be supported in a future release !!! */
bool __attribute__((deprecated)) UART3_DataReady(void)
{
    return UART3_IsRxReady();
}

/* !!! Deprecated API - This function may not be supported in a future release !!! */
bool __attribute__((deprecated)) UART3_is_tx_ready(void)
{
    return UART3_IsTxReady();
}

/* !!! Deprecated API - This function may not be supported in a future release !!! */
bool __attribute__((deprecated)) UART3_is_rx_ready(void)
{
    return UART3_IsRxReady();
}

/* !!! Deprecated API - This function may not be supported in a future release !!! */
bool __attribute__((deprecated)) UART3_is_tx_done(void)
{
    return UART3_IsTxDone();
}

