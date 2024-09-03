#include "SST25xx.h"
#include "project.h"
#include "System/TickTimer.h"

#if(0)
#include <stdio.h>

#define debug(...)   printf(__VA_ARGS__)
#else
#define debug(...)
#endif

#define SST_Make_Address(address) do{sstCMD[1]=(uint8_t) (address>>16); sstCMD[2]=(uint8_t) (address>>8); sstCMD[3]=(uint8_t) address;}while(0)

private uint8_t sstCMD[6];

/* [Chip select On/Off=1/0][data buffer][write length][read length][Chip select On/Off=1/0] */
private void SPI_Xfer(bool enCS, uint8_t *data, uint8_t lenIn, uint8_t lenOut, bool dnCS)
{
    uint8_t i;

    if(enCS)
    {
        FLASH_SPI_Open();
        FLASH_NCS_SetLow();
    }

    for(i=0; i<lenIn; i++)
        FLASH_SPI_Exchange8bit(data[i]);

    for(i=0; i<lenOut; i++)
        data[i]=FLASH_SPI_Exchange8bit(0xFF);

    if(dnCS)
    {
        FLASH_NCS_SetHigh();
        FLASH_SPI_Close();
    }
}

private void SST_Enable_Write(void)// Private function
{
    sstCMD[0]=SST_WRITE_EN;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
}

private void SST_Disable_Write(void)// Private function
{
    sstCMD[0]=SST_WRITE_DIS;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
}

private void SST_Poll_WR_Status(void)// Private function
{
    sstCMD[0]=SST_POLL_WR_STATUS;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
}

private uint8_t SST_Read_Status(void)// Private function
{
    sstCMD[0]=SST_READ_STATUS;
    SPI_Xfer(1, sstCMD, 1, 1, 1);

    return sstCMD[0];
}

private void SST_Write_Status(uint8_t stt)// Private function
{
    sstCMD[0]=SST_WRITE_STATUS_EN;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
    sstCMD[0]=SST_WRITE_STATUS;
    sstCMD[1]=stt;
    SPI_Xfer(1, sstCMD, 2, 0, 1);
}

private void SST_Check_Busy(void)// Private function
{
    while(SST_Read_Status()&0x01);
}

public void SST_Chip_Erase(void)// Public function
{
    SST_Enable_Write();
    sstCMD[0]=SST_BULK_ERASE;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
    SST_Check_Busy();
}

public void SST_Sector_Erase(uint32_t BAddr)// Public function
{
    SST_Enable_Write();
    sstCMD[0]=SST_SECTOR_ERASE;
    SST_Make_Address(BAddr);
    SPI_Xfer(1, sstCMD, 4, 0, 1);
    SST_Check_Busy();
}

public void SST_Read_nByte(uint32_t BAddr, uint32_t len, uint8_t *buffer)// Public function
{
    SST_Check_Busy();
    sstCMD[0]=SST_FAST_READ_DATA;
    SST_Make_Address(BAddr);
    sstCMD[4]=0x00;
    SPI_Xfer(1, sstCMD, 5, 0, 0);
    SPI_Xfer(0, buffer, 0, len, 1);
}

public void SST_Write_Byte(uint32_t Addr, uint8_t data)// Public function
{
    SST_Check_Busy();
    SST_Enable_Write();
    sstCMD[0]=SST_BYTE_PROG;
    SST_Make_Address(Addr);
    sstCMD[4]=data;
    SPI_Xfer(1, sstCMD, 5, 0, 1);
    SST_Disable_Write();
}

public void SST_Write_nByte(uint32_t BAddr, uint16_t len, const uint8_t *data)// Public function
{
    uint16_t i;
#if(SST_USE_AAI)
    // Auto Address Increment (AAI) Word-Program
    SST_Check_Busy();
    SST_Enable_Write();
    sstCMD[0]=SST_WORD_PROG;
    SST_Make_Address(BAddr);
    sstCMD[4]=data[0];
    sstCMD[5]=data[1];
    SPI_Xfer(1, sstCMD, 6, 0, 1);
    SST_Check_Busy();

    for(i=2; i<len; i+=2)
    {
        sstCMD[0]=SST_WORD_PROG;
        sstCMD[1]=data[i];
        sstCMD[2]=data[i+1];
        SPI_Xfer(1, sstCMD, 3, 0, 1);
        SST_Check_Busy();
    }

    SST_Disable_Write();
#else
    for(i=0; i<len; i++)
        SST_Write_Byte(BAddr+i, *data++);
#endif
}

public void SST_Protect(sst_protect_range_t range)// Private function
{
    SST_Enable_Write();
    sstCMD[0]=SST_WRITE_STATUS;
    sstCMD[1]=FLASH_PROTECT_UNLOCK;
    SPI_Xfer(1, sstCMD, 2, 0, 1);
    SST_Enable_Write();
    sstCMD[0]=range|FLASH_PROTECT_LOCK;
    SPI_Xfer(1, sstCMD, 1, 0, 1);
}

public bool SST_Init(void)// Public function
{
    uint8_t tryTimes=0;

LOOP:
    sstCMD[0]=SST_READ_JDECID;
    SPI_Xfer(1, sstCMD, 1, 3, 1);

    if((sstCMD[0]!=JEDEC_ID_BYTE0)||(sstCMD[1]!=JEDEC_ID_BYTE1)||(sstCMD[2]!=JEDEC_ID_BYTE2))// SST JDEC ID is always 0xBF25xx
    {
        debug("\n%02X%02X%02X", sstCMD[0], sstCMD[1], sstCMD[2]);

        if(++tryTimes==0)
            return 0; // Try 256 times after return error

        goto LOOP;
    }

    SST_Write_Status(0);

    return 1;
}