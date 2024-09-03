#ifndef SD_SPI_FILEIO_H
#define SD_SPI_FILEIO_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "TaskManager_Cfg.h"
#endif

#include "sd_spi.h"
#include "FileIO/fileio_media.h"

bool SD_SPI_MediaDetect(void);
FILEIO_MEDIA_INFORMATION * SD_SPI_MediaInitialize(void);
bool SD_SPI_MediaDeinitialize(void);
uint32_t SD_SPI_CapacityRead(void);
uint16_t SD_SPI_SectorSizeRead(void);
bool SD_SPI_SectorRead(uint32_t sector_addr, uint8_t * buffer);
bool SD_SPI_SectorWrite(uint32_t sector_addr, uint8_t * buffer, bool allowWriteToZero);
bool SD_SPI_WriteProtectStateGet(void);

#endif
