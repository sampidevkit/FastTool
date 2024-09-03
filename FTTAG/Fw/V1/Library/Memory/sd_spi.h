#ifndef SD_SPI_H
#define SD_SPI_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "sd_spi_cfg.h"
#endif

#include "sd_spi_private.h"

// Response codes for the SD_SPI_AsyncReadTasks() function.
#define SD_SPI_ASYNC_READ_COMPLETE               0x00
#define SD_SPI_ASYNC_READ_BUSY                   0x01
#define SD_SPI_ASYNC_READ_NEW_PACKET_READY       0x02
#define SD_SPI_ASYNC_READ_ERROR                  0xFF
// SD_SPI_AsyncReadTasks() state machine variable values. These are used internally to sd_spi.c.
#define SD_SPI_ASYNC_READ_COMPLETE               0x00
#define SD_SPI_ASYNC_READ_QUEUED                 0x01 // Initialize to this to start a read sequence
#define SD_SPI_ASYNC_READ_WAIT_START_TOKEN       0x03
#define SD_SPI_ASYNC_READ_NEW_PACKET_READY       0x02
#define SD_SPI_ASYNC_READ_ABORT                  0xFE
#define SD_SPI_ASYNC_READ_ERROR                  0xFF
// Possible return values when calling SD_SPI_AsyncWriteTasks()
#define SD_SPI_ASYNC_WRITE_COMPLETE              0x00
#define SD_SPI_ASYNC_WRITE_SEND_PACKET           0x02
#define SD_SPI_ASYNC_WRITE_BUSY                  0x03
#define SD_SPI_ASYNC_WRITE_ERROR                 0xFF
// SD_SPI_AsyncWriteTasks() state machine variable values. These are used internally to sd_spi.c.
#define SD_SPI_ASYNC_WRITE_COMPLETE              0x00
#define SD_SPI_ASYNC_WRITE_QUEUED                0x01 // Initialize to this to start a write sequence
#define SD_SPI_ASYNC_WRITE_TRANSMIT_PACKET       0x02
#define SD_SPI_ASYNC_WRITE_MEDIA_BUSY            0x03
#define SD_SPI_ASYNC_STOP_TOKEN_SENT_WAIT_BUSY   0x04
#define SD_SPI_ASYNC_WRITE_ABORT                 0xFE
#define SD_SPI_ASYNC_WRITE_ERROR                 0xFF
// Status
#define SD_SPI_STATE_NOT_INITIALIZED             0
#define SD_SPI_STATE_READY_FOR_COMMAND           1
#define SD_SPI_STATE_BUSY                        2

typedef struct {
    uint16_t wNumBytes; // Number of bytes to attempt to read or write in the next call to MDD_SDSPI_AsyncReadTasks() or MDD_SDSPI_AsyncWriteTasks.  May be updated between calls to the handler.
    uint32_t dwBytesRemaining; // Should be initialized to the total number of uint8_ts that you wish to read or write.  This value is allowed to be greater than a single block size of the media.
    uint8_t* pBuffer; // Pointer to where the read/written uint8_ts should be copied to/from.  May be updated between calls to the handler function.
    uint32_t dwAddress; // Starting block address to read or to write to on the media.  Should only get initialized, do not modify after that.
    uint8_t bStateVariable; // State machine variable.  Should get initialized to ASYNC_READ_QUEUED or ASYNC_WRITE_QUEUED to start an operation.  After that, do not modify until the read or write is complete.
} SD_SPI_ASYNC_IO;

public SD_SPI_RESPONSE SD_SPI_SendCmd(uint8_t cmd, uint32_t address);
public void SD_SPI_Deinitialize(void);
public void SD_SPI_Initialize(bool SpMode);
public uint8_t SD_SPI_AsyncReadTasks(SD_SPI_ASYNC_IO*);
public uint8_t SD_SPI_AsyncWriteTasks(SD_SPI_ASYNC_IO*);

#endif
