#ifndef SD_SPI_PRIVATE_H
#define SD_SPI_PRIVATE_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "sd_spi_cfg.h"
#endif

#ifdef __XC8__
// Description: This macro is used to initialize a PIC18 SPI module with a 4x prescale divider
#define   SYNC_MODE_FAST    0x00
// Description: This macro is used to initialize a PIC18 SPI module with a 16x prescale divider
#define   SYNC_MODE_MED     0x01
// Description: This macro is used to initialize a PIC18 SPI module with a 64x prescale divider
#define   SYNC_MODE_SLOW    0x02
#elif defined __XC32__
// Description: This macro is used to initialize a PIC32 SPI module
#define   SYNC_MODE_FAST    0x3E
// Description: This macro is used to initialize a PIC32 SPI module
#define   SYNC_MODE_SLOW    0x3C
#else
// Description: This macro indicates the SPI enable bit for 16-bit PICs
#ifndef MASTER_ENABLE_ON
#define  MASTER_ENABLE_ON   0x0020
#endif
// Description: This macro is used to initialize a 16-bit PIC SPI module
#ifndef SYNC_MODE_FAST
#define   SYNC_MODE_FAST    0x3E
#endif
// Description: This macro is used to initialize a 16-bit PIC SPI module
#ifndef SYNC_MODE_SLOW
#define   SYNC_MODE_SLOW    0x3C
#endif
// Description: This macro is used to initialize a 16-bit PIC SPI module secondary prescaler
#ifndef SEC_PRESCAL_1_1
#define  SEC_PRESCAL_1_1    0x001c
#endif
// Description: This macro is used to initialize a 16-bit PIC SPI module primary prescaler
#ifndef PRI_PRESCAL_1_1
#define  PRI_PRESCAL_1_1    0x0003
#endif
#endif
// Description: This macro represents an SD card start single data block token (used for single block writes)
#define SD_SPI_DATA_START_TOKEN                  0xFE
// Description: This macro represents an SD card start multi-block data token (used for multi-block writes)
#define SD_SPI_DATA_START_MULTI_BLOCK_TOKEN      0xFC
// Description: This macro represents an SD card stop transmission token.  This is used when finishing a multi block write sequence.
#define SD_SPI_DATA_STOP_TRAN_TOKEN              0xFD
// Description: This macro represents an SD card data accepted token
#define SD_SPI_DATA_ACCEPTED                     0x05
// Description: This macro indicates that the SD card expects to transmit or receive more data
#define SD_SPI_MORE_DATA_EXPECTED                (!0)
// Description: This macro indicates that the SD card does not expect to transmit or receive more data
#define SD_SPI_NO_DATA_EXPECTED                  0
// Description: This macro represents a floating SPI bus condition
#define SD_SPI_FLOATING_BUS_TOKEN                0xFF
// The SDMMC Commands
// Description: This macro defines the command code to reset the SD card
#define     SD_SPI_COMMAND_GO_IDLE_STATE                          0
// Description: This macro defines the command code to initialize the SD card
#define     SD_SPI_COMMAND_SEND_OP_COND                           1
// Description: This macro defined the command code to check for sector addressing
#define     SD_SPI_COMMAND_SEND_IF_COND                           8
// Description: This macro defines the command code to get the Card Specific Data
#define     SD_SPI_COMMAND_SEND_CSD                               9
// Description: This macro defines the command code to get the Card Information
#define     SD_SPI_COMMAND_SEND_CID                               10
// Description: This macro defines the command code to stop transmission during a multi-block read
#define     SD_SPI_COMMAND_STOP_TRANSMISSION                      12
// Description: This macro defines the command code to get the card status information
#define     SD_SPI_COMMAND_SEND_STATUS                            13
// Description: This macro defines the command code to set the block length of the card
#define     SD_SPI_COMMAND_SET_BLOCK_LENGTH                       16
// Description: This macro defines the command code to read one block from the card
#define     SD_SPI_COMMAND_READ_SINGLE_BLOCK                      17
// Description: This macro defines the command code to read multiple blocks from the card
#define     SD_SPI_COMMAND_READ_MULTI_BLOCK                       18
// Description: This macro defines the command code to tell the media how many blocks to pre-erase (for faster multi-block writes to follow)
//Note: This is an "application specific" command.  This tells the media how many blocks to pre-erase for the subsequent WRITE_MULTI_BLOCK
#define     SD_SPI_COMMAND_SET_WRITE_BLOCK_ERASE_COUNT            23
// Description: This macro defines the command code to write one block to the card
#define     SD_SPI_COMMAND_WRITE_SINGLE_BLOCK                     24
// Description: This macro defines the command code to write multiple blocks to the card
#define     SD_SPI_COMMAND_WRITE_MULTI_BLOCK                      25
// Description: This macro defines the command code to set the address of the start of an erase operation
#define     SD_SPI_COMMAND_TAG_SECTOR_START                       32
// Description: This macro defines the command code to set the address of the end of an erase operation
#define     SD_SPI_COMMAND_TAG_SECTOR_END                         33
// Description: This macro defines the command code to erase all previously selected blocks
#define     SD_SPI_COMMAND_ERASE                                  38
//Description: This macro defines the command code to intitialize an SD card and provide the CSD register value.
//Note: this is an "application specific" command (specific to SD cards) and must be preceded by cmdAPP_CMD.
#define     SD_SPI_COMMAND_SD_SEND_OP_COND                        41
// Description: This macro defines the command code to begin application specific command inputs
#define     SD_SPI_COMMAND_APP_CMD                                55
// Description: This macro defines the command code to get the OCR register information from the card
#define     SD_SPI_COMMAND_READ_OCR                               58
// Description: This macro defines the command code to disable CRC checking
#define     SD_SPI_COMMAND_CRC_ON_OFF                             59

// Description: Enumeration of different SD response types

typedef enum {
    SD_SPI_RESPONSE_R1, // R1 type response
    SD_SPI_RESPONSE_R1b, // R1b type response
    SD_SPI_RESPONSE_R2, // R2 type response
    SD_SPI_RESPONSE_R3, // R3 type response
    SD_SPI_RESPONSE_R7 // R7 type response
} RESP;

// Summary: SD card command data structure
// Description: The SD_SPI_COMMAND structure is used to create a command table of information needed for each relevant SD command

typedef struct {
    uint8_t CmdCode; // The command code
    uint8_t CRC; // The CRC value for that command
    RESP responsetype; // The response type
    uint8_t moredataexpected; // Set to MOREDATA or NODATA, depending on whether more data is expected or not
} SD_SPI_COMMAND;

// Summary: An SD command packet
// Description: This union represents different ways to access an SD card command packet

typedef union {
    // This structure allows array-style access of command uint8_ts

    struct {
#ifdef __XC8__
        uint8_t field[6]; // uint8_t array
#else
        uint8_t field[7];
#endif
    };
    // This structure allows uint8_t-wise access of packet command uint8_ts

    struct {
        uint8_t crc; // The CRC uint8_t
#if defined __XC16__
        uint8_t c30filler; // Filler space (since bitwise declarations can't cross a uint16_t boundary)
#elif defined __XC32__
        uint8_t c32filler[3]; // Filler space (since bitwise declarations can't cross a uint32_t boundary)
#endif

        uint8_t addr0; // Address uint8_t 0
        uint8_t addr1; // Address uint8_t 1
        uint8_t addr2; // Address uint8_t 2
        uint8_t addr3; // Address uint8_t 3
        uint8_t cmd; // Command code uint8_t
    };
    // This structure allows bitwise access to elements of the command uint8_ts

    struct {
        uint8_t END_BIT : 1; // Packet end bit
        uint8_t CRC7 : 7; // CRC value
        uint32_t address; // Address
        uint8_t CMD_INDEX : 6; // Command code
        uint8_t TRANSMIT_BIT : 1; // Transmit bit
        uint8_t START_BIT : 1; // Packet start bit
    };
} SD_SPI_CMD_PACKET;

// Summary: The format of an R1 type response
// Description: This union represents different ways to access an SD card R1 type response packet.

typedef union {
    uint8_t _byte; // uint8_t-wise access
    // This structure allows bitwise access of the response

    struct {
        unsigned IN_IDLE_STATE : 1; // Card is in idle state
        unsigned ERASE_RESET : 1; // Erase reset flag
        unsigned ILLEGAL_CMD : 1; // Illegal command flag
        unsigned CRC_ERR : 1; // CRC error flag
        unsigned ERASE_SEQ_ERR : 1; // Erase sequence error flag
        unsigned ADDRESS_ERR : 1; // Address error flag
        unsigned PARAM_ERR : 1; // Parameter flag   
        unsigned B7 : 1; // Unused bit 7
    };
} SD_SPI_RESPONSE_1;

// Summary: The format of an R2 type response
// Description: This union represents different ways to access an SD card R2 type response packet

typedef union {
    uint16_t _uint16_t;

    struct {
        uint8_t _byte0;
        uint8_t _byte1;
    };

    struct {
        unsigned IN_IDLE_STATE : 1;
        unsigned ERASE_RESET : 1;
        unsigned ILLEGAL_CMD : 1;
        unsigned CRC_ERR : 1;
        unsigned ERASE_SEQ_ERR : 1;
        unsigned ADDRESS_ERR : 1;
        unsigned PARAM_ERR : 1;
        unsigned B7 : 1;
        unsigned CARD_IS_LOCKED : 1;
        unsigned WP_ERASE_SKIP_LK_FAIL : 1;
        unsigned ERROR : 1;
        unsigned CC_ERROR : 1;
        unsigned CARD_ECC_FAIL : 1;
        unsigned WP_VIOLATION : 1;
        unsigned ERASE_PARAM : 1;
        unsigned OUTRANGE_CSD_OVERWRITE : 1;
    };
} SD_SPI_RESPONSE_2;

// Summary: The format of an R7 or R3 type response
// Description: This union represents different ways to access an SD card R7 type response packet.

typedef union {

    struct {
        uint8_t _byte; // byte-wise access

        union {
            //Note: The SD card argument response field is 32-bit, big endian format.
            //However, the C compiler stores 32-bit values in little endian in RAM.
            //When writing to the _returnVal/argument bytes, make sure to byte
            //swap the order from which it arrived over the SPI from the SD card.
            uint32_t _returnVal;

            struct {
                uint8_t _byte0;
                uint8_t _byte1;
                uint8_t _byte2;
                uint8_t _byte3;
            };
        } argument;
    } bytewise;
    // This structure allows bitwise access of the response

    struct {

        struct {
            unsigned IN_IDLE_STATE : 1; // Card is in idle state
            unsigned ERASE_RESET : 1; // Erase reset flag
            unsigned ILLEGAL_CMD : 1; // Illegal command flag
            unsigned CRC_ERR : 1; // CRC error flag
            unsigned ERASE_SEQ_ERR : 1; // Erase sequence error flag
            unsigned ADDRESS_ERR : 1; // Address error flag
            unsigned PARAM_ERR : 1; // Parameter flag   
            unsigned B7 : 1; // Unused bit 7
        } bits;
        uint32_t _returnVal;
    } bitwise;
} SD_SPI_RESPONSE_7;

// Summary: A union of responses from an SD card
// Description: The SD_SPI_RESPONSE union represents any of the possible responses that an SD card can return after
//              being issued a command.

typedef union {
    SD_SPI_RESPONSE_1 r1;
    SD_SPI_RESPONSE_2 r2;
    SD_SPI_RESPONSE_7 r7;
} SD_SPI_RESPONSE;

// Description: A delay prescaler
#define SD_SPI_DELAY_PRESCALER       (uint8_t)8
// Description: An approximation of the number of cycles per delay loop of overhead
#define SD_SPI_DELAY_OVERHEAD        (uint8_t)5
// Description: An approximate calculation of how many times to loop to delay 1 ms in the Delayms function
#define SD_SPI_MILLISECOND_DELAY     (uint16_t)((SYS_CLK_FrequencyInstructionGet()/SD_SPI_DELAY_PRESCALER/(uint16_t)1000) - SD_SPI_DELAY_OVERHEAD)
// Description: Media Response Delay Timeout Values
#define SD_SPI_NCR_TIMEOUT           (uint16_t)20          //uint8_t times before command response is expected (must be at least 8)
#define SD_SPI_NAC_TIMEOUT           (uint32_t)0x40000     //SPI uint8_t times we should wait when performing read operations (should be at least 100ms for SD cards)
#define SD_SPI_WRITE_TIMEOUT         (uint32_t)0xA0000     //SPI uint8_t times to wait before timing out when the media is performing a write operation (should be at least 250ms for SD cards).

// Summary: An enumeration of SD commands
// Description: This enumeration corresponds to the position of each command in the sdmmc_cmdtable array
//              These macros indicate to the SD_SPI_SendCmd function which element of the sdmmc_cmdtable array
//              to retrieve command code information from.

typedef enum {
    SD_SPI_GO_IDLE_STATE,
    SD_SPI_SEND_OP_COND,
    SD_SPI_SEND_IF_COND,
    SD_SPI_SEND_CSD,
    SD_SPI_SEND_CID,
    SD_SPI_STOP_TRANSMISSION,
    SD_SPI_SEND_STATUS,
    SD_SPI_SET_BLOCK_LENGTH,
    SD_SPI_READ_SINGLE_BLOCK,
    SD_SPI_READ_MULTI_BLOCK,
    SD_SPI_WRITE_SINGLE_BLOCK,
    SD_SPI_WRITE_MULTI_BLOCK,
    SD_SPI_TAG_SECTOR_START,
    SD_SPI_TAG_SECTOR_END,
    SD_SPI_ERASE,
    SD_SPI_APP_CMD,
    SD_SPI_READ_OCR,
    SD_SPI_CRC_ON_OFF,
    SD_SPI_SD_SEND_OP_COND,
    SD_SPI_SET_WRITE_BLOCK_ERASE_COUNT
} SD_SPI_COMMAND_INDEX;

#define SD_SPI_MODE_NORMAL               0
#define SD_SPI_MODE_HC                   1
//Constants
#define SD_SPI_MEDIA_BLOCK_SIZE          512u  //Should always be 512 for v1 and v2 devices.
#define SD_SPI_WRITE_RESPONSE_TOKEN_MASK 0x1F  //Bit mask to AND with the write token response uint8_t from the media, to clear the don't care bits.
// Description: A macro to send clock cycles to dummy-write the CRC
#define SD_SPI_CRCSend(i)                do{DRV_SPI_Put(i, 0xFF); DRV_SPI_Put(i, 0xFF);}while(0)
// Description: A macro to send 8 clock cycles for SD timing requirements
#define SD_SPI_Send8ClockCycles(i)       DRV_SPI_Put(i, 0xFF)
#endif