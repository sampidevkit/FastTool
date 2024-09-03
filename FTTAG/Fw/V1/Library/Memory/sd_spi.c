#include "libcomp.h"
#include "sd_spi.h"

private uint8_t gSDMode;
private SD_SPI_ASYNC_IO ioInfo;
private uint8_t gSDMediaState=SD_SPI_STATE_NOT_INITIALIZED;
private spi_speed_mode=0;

private const SD_SPI_COMMAND sdmmc_cmdtable[]=// <editor-fold defaultstate="collapsed" desc="SD MMC command table">
{
    // CMD, CRC, RESPONSE
    {SD_SPI_COMMAND_GO_IDLE_STATE, 0x95, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SEND_OP_COND, 0xF9, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SEND_IF_COND, 0x87, SD_SPI_RESPONSE_R7, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SEND_CSD, 0xAF, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_SEND_CID, 0x1B, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_STOP_TRANSMISSION, 0xC3, SD_SPI_RESPONSE_R1b, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SEND_STATUS, 0xAF, SD_SPI_RESPONSE_R2, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SET_BLOCK_LENGTH, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_READ_SINGLE_BLOCK, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_READ_MULTI_BLOCK, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_WRITE_SINGLE_BLOCK, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_WRITE_MULTI_BLOCK, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_MORE_DATA_EXPECTED},
    {SD_SPI_COMMAND_TAG_SECTOR_START, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_TAG_SECTOR_END, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_ERASE, 0xDF, SD_SPI_RESPONSE_R1b, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_APP_CMD, 0x73, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_READ_OCR, 0x25, SD_SPI_RESPONSE_R7, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_CRC_ON_OFF, 0x25, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SD_SEND_OP_COND, 0xFF, SD_SPI_RESPONSE_R7, SD_SPI_NO_DATA_EXPECTED},
    {SD_SPI_COMMAND_SET_WRITE_BLOCK_ERASE_COUNT, 0xFF, SD_SPI_RESPONSE_R1, SD_SPI_NO_DATA_EXPECTED}
}; // </editor-fold>

public void SD_SPI_Deinitialize(void) // <editor-fold defaultstate="collapsed" desc="SPI deinitialize">
{
    
} // </editor-fold>

public void SD_SPI_Initialize(bool SpMode) // <editor-fold defaultstate="collapsed" desc="SPI initialize">
{
    SD_SPI_Deinitialize();
    
    if(SpMode) // high speed
    {
        
    }
    else // low speed
    {
        
    }
} // </editor-fold>

public SD_SPI_RESPONSE SD_SPI_SendCmd(uint8_t cmd, uint32_t address) // <editor-fold defaultstate="collapsed" desc="Send command">
{
    SD_SPI_RESPONSE response;
    SD_SPI_CMD_PACKET CmdPacket;
    uint16_t timeout;
    uint32_t longTimeout;

    SD_SPI_CSSet(0);
    CmdPacket.cmd=sdmmc_cmdtable[cmd].CmdCode;
    CmdPacket.address=address;
    CmdPacket.crc=sdmmc_cmdtable[cmd].CRC;
    CmdPacket.TRANSMIT_BIT=1;
    DRV_SPI_Put(config->index, CmdPacket.cmd);
    DRV_SPI_Put(config->index, CmdPacket.addr3);
    DRV_SPI_Put(config->index, CmdPacket.addr2);
    DRV_SPI_Put(config->index, CmdPacket.addr1);
    DRV_SPI_Put(config->index, CmdPacket.addr0);
    DRV_SPI_Put(config->index, CmdPacket.crc);

    if(cmd==SD_SPI_STOP_TRANSMISSION)
        DRV_SPI_Get(config->index);

    timeout=SD_SPI_NCR_TIMEOUT;

    do
    {
        response.r1._byte=DRV_SPI_Get(config->index);
        timeout--;
    }
    while((response.r1._byte==SD_SPI_FLOATING_BUS_TOKEN) && (timeout!=0));

    if(sdmmc_cmdtable[cmd].responsetype==SD_SPI_RESPONSE_R2)
    {
        response.r2._byte1=response.r1._byte;
        response.r2._byte0=DRV_SPI_Get(config->index);
    }
    else if(sdmmc_cmdtable[cmd].responsetype==SD_SPI_RESPONSE_R1b)
    {
        longTimeout=SD_SPI_WRITE_TIMEOUT;

        do
        {
            response.r1._byte=DRV_SPI_Get(config->index);
            longTimeout--;
        }
        while((response.r1._byte==0x00) && (longTimeout!=0));

        response.r1._byte=0x00;
    }
    else if(sdmmc_cmdtable[cmd].responsetype==SD_SPI_RESPONSE_R7)
    {
        response.r7.bytewise.argument._byte3=DRV_SPI_Get(config->index);
        response.r7.bytewise.argument._byte2=DRV_SPI_Get(config->index);
        response.r7.bytewise.argument._byte1=DRV_SPI_Get(config->index);
        response.r7.bytewise.argument._byte0=DRV_SPI_Get(config->index);
    }

    DRV_SPI_Put(config->index, 0xFF);

    if(!(sdmmc_cmdtable[cmd].moredataexpected))
        SD_SPI_CSSet(1);

    return (response);
} // </editor-fold>

public uint8_t SD_SPI_AsyncReadTasks(SD_SPI_ASYNC_IO* info) // <editor-fold defaultstate="collapsed" desc="Async read task">
{
    uint8_t bData;
    SD_SPI_RESPONSE response;
    private uint16_t blockCounter;
    private uint32_t longTimeoutCounter;
    private bool SingleBlockRead;

    switch(info->bStateVariable)
    {
        case SD_SPI_ASYNC_READ_COMPLETE:
            return SD_SPI_ASYNC_READ_COMPLETE;

        case SD_SPI_ASYNC_READ_QUEUED:
            gSDMediaState=SD_SPI_STATE_BUSY;
            blockCounter=SD_SPI_MEDIA_BLOCK_SIZE;
            ioInfo= *info;

            if(gSDMode==SD_SPI_MODE_NORMAL)
                ioInfo.dwAddress<<=9;

            if(ioInfo.dwBytesRemaining<=SD_SPI_MEDIA_BLOCK_SIZE)
            {
                SingleBlockRead=true;
                response=SD_SPI_SendCmd(config, SD_SPI_READ_SINGLE_BLOCK, ioInfo.dwAddress);
            }
            else
            {
                SingleBlockRead=false;
                response=SD_SPI_SendCmd(config, SD_SPI_READ_MULTI_BLOCK, ioInfo.dwAddress);
            }

            if(response.r1._byte!=0x00)
            {
                info->bStateVariable=SD_SPI_ASYNC_READ_ABORT;
                return SD_SPI_ASYNC_READ_BUSY;
            }

            longTimeoutCounter=SD_SPI_NAC_TIMEOUT;
            info->bStateVariable=SD_SPI_ASYNC_READ_WAIT_START_TOKEN;
            return SD_SPI_ASYNC_READ_BUSY;

        case SD_SPI_ASYNC_READ_WAIT_START_TOKEN:
            if(longTimeoutCounter!=0x00000000)
            {
                longTimeoutCounter--;
                bData=DRV_SPI_Get(config->index);

                if(bData!=SD_SPI_FLOATING_BUS_TOKEN)
                {
                    if(bData==SD_SPI_DATA_START_TOKEN)
                    {
                        info->bStateVariable=SD_SPI_ASYNC_READ_NEW_PACKET_READY;
                        return SD_SPI_ASYNC_READ_NEW_PACKET_READY;
                    }
                    else
                    {
                        info->bStateVariable=SD_SPI_ASYNC_READ_ABORT;
                        return SD_SPI_ASYNC_READ_BUSY;
                    }
                }
                else
                    return SD_SPI_ASYNC_READ_BUSY;
            }
            else
            {
                info->bStateVariable=SD_SPI_ASYNC_READ_ABORT;
                return SD_SPI_ASYNC_READ_BUSY;
            }

        case SD_SPI_ASYNC_READ_NEW_PACKET_READY:
            if(ioInfo.dwBytesRemaining!=0x00000000)
            {
                ioInfo.wNumBytes=info->wNumBytes;
                ioInfo.pBuffer=info->pBuffer;
                ioInfo.dwBytesRemaining-=ioInfo.wNumBytes;
                blockCounter-=ioInfo.wNumBytes;
                DRV_SPI_GetBuffer(config->index, ioInfo.pBuffer, ioInfo.wNumBytes);

                if(blockCounter==0)
                {
                    DRV_SPI_Get(config->index);
                    DRV_SPI_Get(config->index);

                    if(ioInfo.dwBytesRemaining!=0x00000000)
                        info->bStateVariable=SD_SPI_ASYNC_READ_WAIT_START_TOKEN;

                    blockCounter=SD_SPI_MEDIA_BLOCK_SIZE;
                    return SD_SPI_ASYNC_READ_BUSY;
                }

                return SD_SPI_ASYNC_READ_NEW_PACKET_READY;
            }
            else
            {
                if(SingleBlockRead==false)
                    SD_SPI_SendCmd(config, SD_SPI_STOP_TRANSMISSION, 0x00000000);

                SD_SPI_CSSet(1); // De-select media
                SD_SPI_Send8ClockCycles(config->index);
                info->bStateVariable=SD_SPI_ASYNC_READ_COMPLETE;
                gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
                return SD_SPI_ASYNC_READ_COMPLETE;
            }

        case SD_SPI_ASYNC_READ_ABORT:
            info->bStateVariable=SD_SPI_ASYNC_READ_ERROR;
            response=SD_SPI_SendCmd(config, SD_SPI_STOP_TRANSMISSION, 0x00000000);

        case SD_SPI_ASYNC_READ_ERROR:
        default:
            SD_SPI_CSSet(1);
            SD_SPI_Send8ClockCycles(config->index);
            gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
            return SD_SPI_ASYNC_READ_ERROR;
    }

    return SD_SPI_ASYNC_READ_ERROR;
} // </editor-fold>

public uint8_t SD_SPI_AsyncWriteTasks(SD_SPI_ASYNC_IO* info) // <editor-fold defaultstate="collapsed" desc="Asyns write tasks">
{
    private uint8_t data_byte;
    private uint16_t blockCounter;
    private uint32_t WriteTimeout;
    private uint8_t command;
    uint32_t preEraseBlockCount;
    SD_SPI_RESPONSE response;

    switch(info->bStateVariable)
    {
        case SD_SPI_ASYNC_WRITE_COMPLETE:
            return SD_SPI_ASYNC_WRITE_COMPLETE;

        case SD_SPI_ASYNC_WRITE_QUEUED:
            gSDMediaState=SD_SPI_STATE_BUSY;
            blockCounter=SD_SPI_MEDIA_BLOCK_SIZE;
            ioInfo= *info;

            if(ioInfo.dwBytesRemaining<=SD_SPI_MEDIA_BLOCK_SIZE)
                command=SD_SPI_WRITE_SINGLE_BLOCK;
            else
            {
                command=SD_SPI_WRITE_MULTI_BLOCK;
                preEraseBlockCount=(ioInfo.dwBytesRemaining>>9);

                if(preEraseBlockCount==0)
                    preEraseBlockCount++;

                response=SD_SPI_SendCmd(config, SD_SPI_APP_CMD, 0x00000000);

                if(response.r1._byte==0x00)
                    SD_SPI_SendCmd(config, SD_SPI_SET_WRITE_BLOCK_ERASE_COUNT, preEraseBlockCount);
            }

            if(gSDMode==SD_SPI_MODE_NORMAL)
                ioInfo.dwAddress<<=9;

            response=SD_SPI_SendCmd(config, command, ioInfo.dwAddress);

            if(response.r1._byte!=0x00)
            {
                info->bStateVariable=SD_SPI_ASYNC_WRITE_ERROR;
                return SD_SPI_ASYNC_WRITE_ERROR;
            }
            else
                info->bStateVariable=SD_SPI_ASYNC_WRITE_TRANSMIT_PACKET;

            return SD_SPI_ASYNC_WRITE_SEND_PACKET;

        case SD_SPI_ASYNC_WRITE_TRANSMIT_PACKET:
            if(blockCounter==SD_SPI_MEDIA_BLOCK_SIZE)
            {
                if(command==SD_SPI_WRITE_MULTI_BLOCK)
                    DRV_SPI_Put(config->index, SD_SPI_DATA_START_MULTI_BLOCK_TOKEN);
                else
                    DRV_SPI_Put(config->index, SD_SPI_DATA_START_TOKEN);
            }

            ioInfo.wNumBytes=info->wNumBytes;
            ioInfo.pBuffer=info->pBuffer;
            ioInfo.dwBytesRemaining-=ioInfo.wNumBytes;
            blockCounter-=ioInfo.wNumBytes;
            DRV_SPI_PutBuffer(config->index, ioInfo.pBuffer, ioInfo.wNumBytes);

            if(blockCounter==0)
            {
                blockCounter=SD_SPI_MEDIA_BLOCK_SIZE;
                SD_SPI_CRCSend(config->index);

                if((DRV_SPI_Get(config->index)&SD_SPI_WRITE_RESPONSE_TOKEN_MASK)!=SD_SPI_DATA_ACCEPTED)
                {
                    info->bStateVariable=SD_SPI_ASYNC_WRITE_ABORT;
                    return SD_SPI_ASYNC_WRITE_BUSY;
                }

                info->bStateVariable=SD_SPI_ASYNC_WRITE_MEDIA_BUSY;
                WriteTimeout=SD_SPI_WRITE_TIMEOUT;
                return SD_SPI_ASYNC_WRITE_BUSY;
            }

            return SD_SPI_ASYNC_WRITE_SEND_PACKET;

        case SD_SPI_ASYNC_WRITE_MEDIA_BUSY:
            if(WriteTimeout!=0)
            {
                WriteTimeout--;
                SD_SPI_Send8ClockCycles(config->index);
                data_byte=DRV_SPI_Get(config->index);

                if(data_byte!=0x00)
                {
                    if(ioInfo.dwBytesRemaining==0)
                    {
                        WriteTimeout=SD_SPI_WRITE_TIMEOUT;
                        if(command==SD_SPI_WRITE_MULTI_BLOCK)
                        {
                            DRV_SPI_Put(config->index, SD_SPI_DATA_STOP_TRAN_TOKEN);
                            SD_SPI_Send8ClockCycles(config->index);
                            info->bStateVariable=SD_SPI_ASYNC_STOP_TOKEN_SENT_WAIT_BUSY;
                            return SD_SPI_ASYNC_WRITE_BUSY;
                        }
                        else
                        {
                            SD_SPI_CSSet(1);
                            SD_SPI_Send8ClockCycles(config->index);
                            info->bStateVariable=SD_SPI_ASYNC_WRITE_COMPLETE;
                            gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
                            return SD_SPI_ASYNC_WRITE_COMPLETE;
                        }
                    }
                    info->bStateVariable=SD_SPI_ASYNC_WRITE_TRANSMIT_PACKET;
                    return SD_SPI_ASYNC_WRITE_SEND_PACKET;
                }
                else
                    return SD_SPI_ASYNC_WRITE_BUSY;
            }
            else
            {
                info->bStateVariable=SD_SPI_ASYNC_WRITE_ABORT;
                return SD_SPI_ASYNC_WRITE_BUSY;
            }

        case SD_SPI_ASYNC_STOP_TOKEN_SENT_WAIT_BUSY:
            if(WriteTimeout!=0)
            {
                WriteTimeout--;
                data_byte=DRV_SPI_Get(config->index);

                if(data_byte!=0x00)
                {
                    SD_SPI_CSSet(1);
                    SD_SPI_Send8ClockCycles(config->index);
                    info->bStateVariable=SD_SPI_ASYNC_WRITE_COMPLETE;
                    gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
                    return SD_SPI_ASYNC_WRITE_COMPLETE;
                }

                return SD_SPI_ASYNC_WRITE_BUSY;
            }

        case SD_SPI_ASYNC_WRITE_ABORT:
            SD_SPI_SendCmd(config, SD_SPI_STOP_TRANSMISSION, 0x00000000);
            SD_SPI_CSSet(1);
            SD_SPI_Send8ClockCycles(config->index);
            info->bStateVariable=SD_SPI_ASYNC_WRITE_ERROR;

        default:
            gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
            return SD_SPI_ASYNC_WRITE_ERROR;
    }

    info->bStateVariable=SD_SPI_ASYNC_WRITE_ABORT;
    return SD_SPI_ASYNC_WRITE_BUSY;
} // </editor-fold>