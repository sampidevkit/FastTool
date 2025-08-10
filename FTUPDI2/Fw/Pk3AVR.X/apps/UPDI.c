#include "UPDI.h"
#include "uart1.h"
#include "pin_manager.h"
#include "system/TickTimer.h"

void UPDI_SendData(const uint8_t *pD, uint8_t len)
{
    U1MODEbits.UARTEN=1; // enabling UART ON bit
    U1STAbits.UTXEN=1;
    DATA_EN_SetHigh(); // TX enable

    while(len>0)
    {
        while(!UART1_IsTxReady());
        UART1_Write(*pD++);
        len--;
    }

    while(!UART1_IsTxDone());
    DATA_EN_SetLow(); // RX enable
}

void UPDI_SendIdle(void)
{
    LATDbits.LATD4=1;
    U1STAbits.UTXEN=0;
    U1MODEbits.UARTEN=0; // disabling UART ON bit
    DATA_EN_SetHigh(); // TX enable

    DATA_EN_SetLow(); // RX enable
    U1MODEbits.UARTEN=1; // enabling UART ON bit
    U1STAbits.UTXEN=1;
}

void UPDI_SendBreak(void)
{
    LATDbits.LATD4=0;
    U1STAbits.UTXEN=0;
    U1MODEbits.UARTEN=0; // disabling UART ON bit
    DATA_EN_SetHigh(); // TX enable
    __delay_us(100);
    LATDbits.LATD4=0;
    DATA_EN_SetLow(); // RX enable
    U1MODEbits.UARTEN=1; // enabling UART ON bit
    U1STAbits.UTXEN=1;
}

void UPDI_SendSynch(void)
{
    uint8_t syncCode=0x55;

    UPDI_SendData(&syncCode, 1);
}

void UPDI_SendAck(void)
{
    uint8_t syncCode=0x40;

    UPDI_SendData(&syncCode, 1);
}

uint8_t UPDI_ReadData(uint16_t addr)
{
    uint8_t cmd[8];

    cmd[0]=0x55;
    cmd[1]=0xC2;
    cmd[2]=0x88;
    cmd[3]=0x81;
    cmd[4]=0x12;
    UPDI_SendData(cmd, 5);

    cmd[0]=0x55;
    cmd[1]=0x80;
    UPDI_SendData(cmd, 2);

    while(!UART1_IsRxReady());

    do
        cmd[0]=UART1_Read();
    while(UART1_IsRxReady());
    
    return cmd[0];
}
