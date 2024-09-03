#include "libcomp.h"
#include "sd_spi.h"
#include "sd_spi_private.h"
#include "sd_spi_fileio.h"
#include "FileIO/fileio.h"
#include "FileIO/fileio_private.h"

// Description:  Used for the mass-storage library to determine capacity
uint32_t finalLBA;
uint16_t gMediaSectorSize;
uint8_t gSDMode;
static FILEIO_MEDIA_INFORMATION mediaInformation;
static SD_SPI_ASYNC_IO ioInfo; //Declared global context, for fast/code efficient access
static uint8_t gSDMediaState=SD_SPI_STATE_NOT_INITIALIZED;

bool SD_SPI_MediaDetect(void)
{
    return SD_SPI_CDGet();
}

uint16_t SD_SPI_SectorSizeRead(void)
{
    return gMediaSectorSize;
}

uint32_t SD_SPI_CapacityRead(void)
{
    return (finalLBA);
}

bool SD_SPI_MediaDeinitialize(void)
{
    // close the spi bus
    DRV_SPI_Deinitialize(config->index);

    // deselect the device
    (*tmp)(1);

    gSDMediaState=SD_SPI_STATE_NOT_INITIALIZED;

    return true;
}

bool SD_SPI_SectorRead(uint32_t sectorAddress, uint8_t* buffer)
{
    SD_SPI_ASYNC_IO info;
    uint8_t status;

    //Initialize info structure for using the SD_SPI_AsyncReadTasks() function.
    info.wNumBytes=512;
    info.dwBytesRemaining=512;
    info.pBuffer=buffer;
    info.dwAddress=sectorAddress;
    info.bStateVariable=SD_SPI_ASYNC_READ_QUEUED;

    //Blocking loop, until the state machine finishes reading the sector,
    //or a timeout or other error occurs.  SD_SPI_AsyncReadTasks() will always
    //return either SD_SPI_ASYNC_READ_COMPLETE or SD_SPI_ASYNC_READ_FAILED eventually 
    //(could take awhile in the case of timeout), so this won't be a totally
    //infinite blocking loop.
    while(1)
    {
        status=SD_SPI_AsyncReadTasks(config, &info);
        if(status==SD_SPI_ASYNC_READ_COMPLETE)
        {
            return true;
        }
        else if(status==SD_SPI_ASYNC_READ_ERROR)
        {
            return false;
        }
    }

    //Impossible to get here, but we will return a value anyay to avoid possible 
    //compiler warnings.
    return false;
}

bool SD_SPI_SectorWrite(uint32_t sectorAddress, uint8_t* buffer, bool allowWriteToZero)
{
    static SD_SPI_ASYNC_IO info;
    uint8_t status;

    if(allowWriteToZero==false)
    {
        if(sectorAddress==0x00000000)
        {
            return false;
        }
    }

    //Initialize structure so we write a single sector worth of data.
    info.wNumBytes=512;
    info.dwBytesRemaining=512;
    info.pBuffer=buffer;
    info.dwAddress=sectorAddress;
    info.bStateVariable=SD_SPI_ASYNC_WRITE_QUEUED;

    //Repeatedly call the write handler until the operation is complete (or a
    //failure/timeout occurred).
    while(1)
    {
        status=SD_SPI_AsyncWriteTasks(config, &info);
        if(status==SD_SPI_ASYNC_WRITE_COMPLETE)
        {
            return true;
        }
        else if(status==SD_SPI_ASYNC_WRITE_ERROR)
        {
            return false;
        }
    }
    return true;
}

bool SD_SPI_WriteProtectStateGet(void)
{
    return (*config->wpFunc)();
}

FILEIO_MEDIA_INFORMATION * SD_SPI_MediaInitialize(void)
{
    uint16_t timeout;
    SD_SPI_RESPONSE response;
    uint8_t CSDResponse[20];
    uint8_t count, index;
    uint32_t c_size;
    uint8_t c_size_mult;
    uint8_t block_len;
    DRV_SPI_INIT_DATA spiInitData;

#ifdef __DEBUG_UART
    InitUART();
#endif

    //Initialize global variables.  Will get updated later with valid data once
    //the data is known.
    gSDMediaState=SD_SPI_STATE_NOT_INITIALIZED;
    mediaInformation.errorCode=MEDIA_NO_ERROR;
    mediaInformation.validityFlags.value=0;
    finalLBA=0x00000000; //Will compute a valid size later, from the CSD register values we get from the card
    gSDMode=SD_SPI_MODE_NORMAL; //Will get updated later with real value, once we know based on initialization flow.

    (*config->csFunc)(1); //Initialize Chip Select line (1 = card not selected)

    //MMC media powers up in the open-drain mode and cannot handle a clock faster
    //than 400kHz. Initialize SPI port to <= 400kHz
    SD_SPI_SPIInitialize_Slow(config);

#ifdef __DEBUG_UART  
    PrintROMASCIIStringUART("\r\n\r\nInitializing Media\r\n");
#endif

    //Media wants the longer of: Vdd ramp time, 1 ms fixed delay, or 74+ clock pulses.
    //According to spec, CS should be high during the 74+ clock pulses.
    //In practice it is preferable to wait much longer than 1ms, in case of
    //contact bounce, or incomplete mechanical insertion (by the time we start
    //accessing the media). 
    Delayms(30);
    (*config->csFunc)(1);
    //Generate 80 clock pulses.
    for(timeout=0; timeout<10u; timeout++)
        SD_SPI_SPI_Put_Slow(config->index, 0xFF);


    // Send CMD0 (with CS = 0) to reset the media and put SD cards into SPI mode.
    timeout=100;
    do
    {
        //Toggle chip select, to make media abandon whatever it may have been doing
        //before.  This ensures the CMD0 is sent freshly after CS is asserted low,
        //minimizing risk of SPI clock pulse master/slave synchronization problems, 
        //due to possible application noise on the SCK line.
        (*config->csFunc)(1);
        SD_SPI_SPI_Put_Slow(config->index, 0xFF); //Send some "extraneous" clock pulses.  If a previous
        //command was terminated before it completed normally,
        //the card might not have received the required clocking
        //following the transfer.
        (*config->csFunc)(0);
        timeout--;

        //Send CMD0 to software reset the device
        response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_GO_IDLE_STATE, 0x0);
    }
    while((response.r1._byte!=0x01) && (timeout!=0));
    //Check if all attempts failed and we timed out.  Normally, this won't happen,
    //unless maybe the SD card was busy, because it was previously performing a
    //read or write operation, when it was interrupted by the microcontroller getting
    //reset or power cycled, without also resetting or power cycling the SD card.
    //In this case, the SD card may still be busy (ex: trying to respond with the 
    //read request data), and may not be ready to process CMD0.  In this case,
    //we can try to recover by issuing CMD12 (STOP_TRANSMISSION).
    if(timeout==0)
    {
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("Media failed CMD0 too many times. R1 response uint8_t = ");
        PrintRAMuint8_tsUART(((unsigned char*) &response+1), 1);
        UARTSendLineFeedCarriageReturn();
        PrintROMASCIIStringUART("Trying CMD12 to recover.\r\n");
#endif

        (*config->csFunc)(1);
        SD_SPI_SPI_Put_Slow(config->index, 0xFF); //Send some "extraneous" clock pulses.  If a previous
        //command was terminated before it completed normally,
        //the card might not have received the required clocking
        //following the transfer.
        (*config->csFunc)(0);

        //Send CMD12, to stop any read/write transaction that may have been in progress
        response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_STOP_TRANSMISSION, 0x0); //Blocks until SD card signals non-busy
        //Now retry to send send CMD0 to perform software reset on the media
        response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_GO_IDLE_STATE, 0x0);
        if(response.r1._byte!=0x01) //Check if card in idle state now.
        {
            //Card failed to process CMD0 yet again.  At this point, the proper thing
            //to do would be to power cycle the card and retry, if the host 
            //circuitry supports disconnecting the SD card power.  Since the
            //SD/MMC PICtail+ doesn't support software controlled power removal
            //of the SD card, there is nothing that can be done with this hardware.
            //Therefore, we just give up now.  The user needs to physically 
            //power cycle the media and/or the whole board.
#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("Media still failed CMD0. Cannot initialize card, returning.\r\n");
#endif   
            mediaInformation.errorCode=MEDIA_CANNOT_INITIALIZE;
            return &mediaInformation;
        }
        else
        {
            //Card successfully processed CMD0 and is now in the idle state.
#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("Media successfully processed CMD0 after CMD12.\r\n");
#endif        
        }
    }//if(timeout == 0) [for the CMD0 transmit loop]
    else
    {
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("Media successfully processed CMD0.\r\n");
#endif        
    }


    //Send CMD8 (SEND_IF_COND) to specify/request the SD card interface condition (ex: indicate what voltage the host runs at).
    //0x000001AA --> VHS = 0001b = 2.7V to 3.6V.  The 0xAA LSB is the check pattern, and is arbitrary, but 0xAA is recommended (good blend of 0's and '1's).
    //The SD card has to echo back the check pattern correctly however, in the R7 response.
    //If the SD card doesn't support the operating voltage range of the host, then it may not respond.
    //If it does support the range, it will respond with a type R7 response packet (6 uint8_ts/48 bits).	        
    //Additionally, if the SD card is MMC or SD card v1.x spec device, then it may respond with
    //invalid command.  If it is a v2.0 spec SD card, then it is mandatory that the card respond
    //to CMD8.
    response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_SEND_IF_COND, 0x1AA); //Note: If changing "0x1AA", CRC value in table must also change.
    if(((response.r7.bytewise.argument._returnVal&0xFFF)==0x1AA) && (!response.r7.bitwise.bits.ILLEGAL_CMD))
    {
        //If we get to here, the device supported the CMD8 command and didn't complain about our host
        //voltage range.
        //Most likely this means it is either a v2.0 spec standard or high capacity SD card (SDHC)
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("Media successfully processed CMD8. Response = ");
        PrintRAMuint8_tsUART(((unsigned char*) &response+1), 4);
        UARTSendLineFeedCarriageReturn();
#endif

        //Send CMD58 (Read OCR [operating conditions register]).  Response type is R3, which has 5 uint8_ts.
        //uint8_t 4 = normal R1 response uint8_t, uint8_ts 3-0 are = OCR register value.
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("Sending CMD58.\r\n");
#endif
        response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_READ_OCR, 0x0);
        //Now that we have the OCR register value in the response packet, we could parse
        //the register contents and learn what voltage the SD card wants to run at.
        //If our host circuitry has variable power supply capability, it could 
        //theoretically adjust the SD card Vdd to the minimum of the OCR to save power.

        //Now send CMD55/ACMD41 in a loop, until the card is finished with its internal initialization.
        //Note: SD card specs recommend >= 1 second timeout while waiting for ACMD41 to signal non-busy.
        for(timeout=0; timeout<0xFFFF; timeout++)
        {
            //Send CMD55 (lets SD card know that the next command is application specific (going to be ACMD41)).
            SD_SPI_SendMediaCmd_Slow(config, SD_SPI_APP_CMD, 0x00000000);

            //Send ACMD41.  This is to check if the SD card is finished booting up/ready for full frequency and all
            //further commands.  Response is R3 type (6 uint8_ts/48 bits, middle four uint8_ts contain potentially useful data).
            //Note: When sending ACMD41, the HCS bit is bit 30, and must be = 1 to tell SD card the host supports SDHC
            response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_SD_SEND_OP_COND, 0x40000000); //bit 30 set

            //The R1 response should be = 0x00, meaning the card is now in the "standby" state, instead of
            //the "idle" state (which is the default initialization state after CMD0 reset is issued).  Once
            //in the "standby" state, the SD card is finished with basic initialization and is ready 
            //for read/write and other commands.
            if(response.r1._byte==0)
            {
#ifdef __DEBUG_UART  
                PrintROMASCIIStringUART("Media successfully processed CMD55/ACMD41 and is no longer busy.\r\n");
#endif
                break; //Break out of for() loop.  Card is finished initializing.
            }
        }
        if(timeout>=0xFFFF)
        {
#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("Media Timeout on CMD55/ACMD41.\r\n");
#endif
            mediaInformation.errorCode=MEDIA_CANNOT_INITIALIZE;
        }


        //Now send CMD58 (Read OCR register).  The OCR register contains important
        //info we will want to know about the card (ex: standard capacity vs. SDHC).
        response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_READ_OCR, 0x0);

        //Now check the CCS bit (OCR bit 30) in the OCR register, which is in our response packet.
        //This will tell us if it is a SD high capacity (SDHC) or standard capacity device.
        if(response.r7.bytewise.argument._returnVal&0x40000000) //Note the HCS bit is only valid when the busy bit is also set (indicating device ready).
        {
            gSDMode=SD_SPI_MODE_HC;

#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("Media successfully processed CMD58: SD card is SDHC v2.0 (or later) physical spec type.\r\n");
#endif
        }
        else
        {
            gSDMode=SD_SPI_MODE_NORMAL;

#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("Media successfully processed CMD58: SD card is standard capacity v2.0 (or later) spec.\r\n");
#endif
        }
        //SD Card should now be finished with initialization sequence.  Device should be ready
        //for read/write commands.

    }//if(((response.r7.bytewise._returnVal & 0xFFF) == 0x1AA) && (!response.r7.bitwise.bits.ILLEGAL_CMD))
    else
    {
        //The CMD8 wasn't supported.  This means the card is not a v2.0 card.
        //Presumably the card is v1.x device, standard capacity (not SDHC).

#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("CMD8 Unsupported: Media is most likely MMC or SD 1.x device.\r\n");
#endif


        (*config->csFunc)(1); // deselect the devices
        Delayms(1);
        (*config->csFunc)(0); // select the device

        //The CMD8 wasn't supported.  This means the card is definitely not a v2.0 SDHC card.
        gSDMode=SD_SPI_MODE_NORMAL;
        // According to the spec CMD1 must be repeated until the card is fully initialized
        timeout=0x1FFF;
        do
        {
            //Send CMD1 to initialize the media.
            response=SD_SPI_SendMediaCmd_Slow(config, SD_SPI_SEND_OP_COND, 0x00000000); //When argument is 0x00000000, this queries MMC cards for operating voltage range
            timeout--;
        }
        while((response.r1._byte!=0x00) && (timeout!=0));
        // see if it failed
        if(timeout==0)
        {
#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("CMD1 failed.\r\n");
#endif

            mediaInformation.errorCode=MEDIA_CANNOT_INITIALIZE;
            (*config->csFunc)(1); // deselect the devices
        }
        else
        {
#ifdef __DEBUG_UART  
            PrintROMASCIIStringUART("CMD1 Successfully processed, media is no longer busy.\r\n");
#endif

            //Set read/write block length to 512 bytes.  Note: commented out since
            //this theoretically isn't necessary, since all cards v1 and v2 are 
            //required to support 512 byte block size, and this is supposed to be
            //the default size selected on cards that support other sizes as well.
            //response = SD_SPI_SendMediaCmd_Slow(SET_BLOCKLEN, 0x00000200);    //Set read/write block length to 512 uint8_ts
        }

    }


    //Temporarily deselect device
    (*config->csFunc)(1);

    //Basic initialization of media is now complete.  The card will now use push/pull
    //outputs with fast drivers.  Therefore, we can now increase SPI speed to 
    //either the maximum of the microcontroller or maximum of media, whichever 
    //is slower.  MMC media is typically good for at least 20Mbps SPI speeds.  
    //SD cards would typically operate at up to 25Mbps or higher SPI speeds.
    spiInitData.mode=0;
    spiInitData.spibus_mode=SPI_BUS_MODE_2;
#if defined __XC16__ || defined __XC32__
#ifdef __XC32__
    spiInitData.cke=0;
    if(SYS_CLK_FrequencyPeripheralGet()<=20000000)
    {
        spiInitData.baudRate=SPICalculateBRG(SYS_CLK_FrequencyPeripheralGet(), 10000);
    }
    else
    {
        spiInitData.baudRate=SPICalculateBRG(SYS_CLK_FrequencyPeripheralGet(), SPI_FREQUENCY);
    }
    //    		OpenSPI(SPI_START_CFG_1, SPI_START_CFG_2);
#else //else C30 = PIC24/dsPIC devices
#if defined(DRV_SPI_CONFIG_V2_ENABLED)
    spiInitData.cke=0;
    spiInitData.primaryPrescale=0;
    spiInitData.mode=SPI_TRANSFER_MODE_8BIT;
#else
    spiInitData.cke=0;
    spiInitData.primaryPrescale=2;
    spiInitData.secondaryPrescale=7;
#endif
#endif   //#ifdef __XC32__ (and corresponding #else)
#else //must be PIC18 device
    spiInitData.cke=0;
    spiInitData.divider=0; // 4x divider
#endif
    spiInitData.channel=config->index;
    DRV_SPI_Initialize(&spiInitData);

    (*config->csFunc)(0);

    /* Send the CMD9 to read the CSD register */
    timeout=SD_SPI_NCR_TIMEOUT;
    do
    {
        //Send CMD9: Read CSD data structure.
        response=SD_SPI_SendCmd(config, SD_SPI_SEND_CSD, 0x00);
        timeout--;
    }
    while((response.r1._byte!=0x00) && (timeout!=0));
    if(timeout!=0x00)
    {
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("CMD9 Successfully processed: Read CSD register.\r\n");
        PrintROMASCIIStringUART("CMD9 response R1 uint8_t = ");
        PrintRAMuint8_tsUART((unsigned char*) &response, 1);
        UARTSendLineFeedCarriageReturn();
#endif
    }
    else
    {
        //Media failed to respond to the read CSD register operation.
#ifdef __DEBUG_UART  
        PrintROMASCIIStringUART("Timeout occurred while processing CMD9 to read CSD register.\r\n");
#endif

        mediaInformation.errorCode=MEDIA_CANNOT_INITIALIZE;
        (*config->csFunc)(1);
        return &mediaInformation;
    }

    /* According to the simplified spec, section 7.2.6, the card will respond
    with a standard response token, followed by a data block of 16 uint8_ts
    suffixed with a 16-bit CRC.*/
    index=0;
    for(count=0; count<20u; count++)
    {
        CSDResponse[index]=DRV_SPI_Get(config->index);
        index++;
        /* Hopefully the first uint8_t is the datatoken, however, some cards do
        not send the response token before the CSD register.*/
        if((count==0) && (CSDResponse[0]==SD_SPI_DATA_START_TOKEN))
        {
            /* As the first uint8_t was the datatoken, we can drop it. */
            index=0;
        }
    }

#ifdef __DEBUG_UART  
    PrintROMASCIIStringUART("CSD data structure contains: ");
    PrintRAMuint8_tsUART((unsigned char*) &CSDResponse, 20);
    UARTSendLineFeedCarriageReturn();
#endif



    //Extract some fields from the response for computing the card capacity.
    //Note: The structure format depends on if it is a CSD V1 or V2 device.
    //Therefore, need to first determine version of the specs that the card 
    //is designed for, before interpreting the individual fields.

    //-------------------------------------------------------------
    //READ_BL_LEN: CSD Structure v1 cards always support 512 uint8_t
    //read and write block lengths.  Some v1 cards may optionally report
    //READ_BL_LEN = 1024 or 2048 bytes (and therefore WRITE_BL_LEN also
    //1024 or 2048).  However, even on these cards, 512 uint8_t partial reads
    //and 512 uint8_t write are required to be supported.
    //On CSD structure v2 cards, it is always required that READ_BL_LEN 
    //(and therefore WRITE_BL_LEN) be 512 uint8_ts, and partial reads and
    //writes are not allowed.
    //Therefore, all cards support 512 uint8_t reads/writes, but only a subset
    //of cards support other sizes.  For best compatibility with all cards,
    //and the simplest firmware design, it is therefore preferable to 
    //simply ignore the READ_BL_LEN and WRITE_BL_LEN values altogether,
    //and simply hardcode the read/write block size as 512 uint8_ts.
    //-------------------------------------------------------------
    gMediaSectorSize=512u;
    //mediaInformation.sectorSize = gMediaSectorSize;
    mediaInformation.sectorSize=512u;
    mediaInformation.validityFlags.bits.sectorSize=true;
    //-------------------------------------------------------------

    //Calculate the finalLBA (see SD card physical layer simplified spec 2.0, section 5.3.2).
    //In USB mass storage applications, we will need this information to 
    //correctly respond to SCSI get capacity requests.  Note: method of computing 
    //finalLBA depends on CSD structure spec version (either v1 or v2).
    if(CSDResponse[0] & 0xC0) //Check CSD_STRUCTURE field for v2+ struct device
    {
        //Must be a v2 device (or a reserved higher version, that doesn't currently exist)

        //Extract the C_SIZE field from the response.  It is a 22-bit number in bit position 69:48.  This is different from v1.  
        //It spans uint8_ts 7, 8, and 9 of the response.
        c_size=(((uint32_t) CSDResponse[7] & 0x3F)<<16)|((uint16_t) CSDResponse[8]<<8)|CSDResponse[9];

        finalLBA=((uint32_t) (c_size+1) * (uint16_t) (1024u))-1; //-1 on end is correction factor, since LBA = 0 is valid.
    }
    else //if(CSDResponse[0] & 0xC0)	//Check CSD_STRUCTURE field for v1 struct device
    {
        //Must be a v1 device.
        //Extract the C_SIZE field from the response.  It is a 12-bit number in bit position 73:62.  
        //Although it is only a 12-bit number, it spans uint8_ts 6, 7, and 8, since it isn't uint8_t aligned.
        c_size=((uint32_t) CSDResponse[6]<<16)|((uint16_t) CSDResponse[7]<<8)|CSDResponse[8]; //Get the uint8_ts in the correct positions
        c_size&=0x0003FFC0; //Clear all bits that aren't part of the C_SIZE
        c_size=c_size>>6; //Shift value down, so the 12-bit C_SIZE is properly right justified in the uint32_t.

        //Extract the C_SIZE_MULT field from the response.  It is a 3-bit number in bit position 49:47.
        c_size_mult=((uint16_t) ((CSDResponse[9] & 0x03)<<1))|((uint16_t) ((CSDResponse[10] & 0x80)>>7));

        //Extract the BLOCK_LEN field from the response. It is a 4-bit number in bit position 83:80.
        block_len=CSDResponse[5] & 0x0F;

        block_len=1<<(block_len-9); //-9 because we report the size in sectors of 512 uint8_ts each

        //Calculate the finalLBA (see SD card physical layer simplified spec 2.0, section 5.3.2).
        //In USB mass storage applications, we will need this information to 
        //correctly respond to SCSI get capacity requests (which will cause SD_SPI_CapacityRead() to get called).
        finalLBA=((uint32_t) (c_size+1) * (uint16_t) ((uint16_t) 1<<(c_size_mult+2))*block_len)-1; //-1 on end is correction factor, since LBA = 0 is valid.		
    }

    //Turn off CRC7 if we can, might be an invalid cmd on some cards (CMD59)
    //Note: POR default for the media is normally with CRC checking off in SPI 
    //mode anyway, so this is typically redundant.
    SD_SPI_SendCmd(config, SD_SPI_CRC_ON_OFF, 0x0);

    //Now set the block length to media sector size. It should be already set to this.
    SD_SPI_SendCmd(config, SD_SPI_SET_BLOCK_LENGTH, gMediaSectorSize);

    //Deselect media while not actively accessing the card.
    (*config->csFunc)(1);

#ifdef __DEBUG_UART  
    PrintROMASCIIStringUART("Returning from MediaInitialize() function.\r\n");
#endif

    //Finished with the SD card initialization sequence.
    if(mediaInformation.errorCode==MEDIA_NO_ERROR)
    {
        gSDMediaState=SD_SPI_STATE_READY_FOR_COMMAND;
    }
    return &mediaInformation;
}//end MediaInitialize

