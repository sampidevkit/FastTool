#ifndef ICSP_FILEIO_H
#define ICSP_FILEIO_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "ICSP_FileIO_Cfg.h"
#endif

#include "FileIO/fileio_lite.h"
#include "Programmer/Icsp.h"

//---------------------------------------------------------------------------------------
// The size (in number of sectors) of the desired usable data portion of the MSD volume
//---------------------------------------------------------------------------------------
// Note1: Windows 7 appears to require a minimum capacity of at least 13 sectors.
// Note2: Drive (re)formatting is NOT applicable
#ifndef DRV_CONFIG_DRIVE_CAPACITY
#define DRV_CONFIG_DRIVE_CAPACITY 4096          // * 512 byte = useable drive volume
#endif
//--------------------------------------------------------------------------
// Number of Sectors per Cluster
//--------------------------------------------------------------------------
#ifndef DRV_SECTORS_PER_CLUSTER
#define DRV_SECTORS_PER_CLUSTER     8           // * 512 byte = cluster size (4kB)
#endif
//--------------------------------------------------------------------------
// Maximum files supported
//--------------------------------------------------------------------------
// DRV_MAX_NUM_FILES_IN_ROOT must be a multiple of 16
// Note: Even if DRV_MAX_NUM_FILES_IN_ROOT is 16, this does not
// necessarily mean the drive will always work with 16 files.  The drive will
// suppport "up to" 16 files, but other limits could be hit first, even before
// the drive is full.  The RootDirectory0[] sector could get full with less
// files, especially if the files are using long filenames.
#ifndef DRV_MAX_NUM_FILES_IN_ROOT
#define DRV_MAX_NUM_FILES_IN_ROOT 16
#endif
// Note: If only 1 FAT sector is used, assuming 12-bit (1.5 uint8_t) FAT entry size
// (ex: FAT12 filesystem), then the total FAT entries that can fit in a single 512
// uint8_t FAT sector is (512 uint8_ts) / (1.5 uint8_ts/entry) = 341 entries.
// This allows the FAT table to reference up to 341*512 * SectorsPerCluster (bytes)
// If SectorPerCluster == 8 (4kB Cluster) ==> 1.4MB  of space.
#ifndef DRV_NUM_RESERVED_SECTORS
#define DRV_NUM_RESERVED_SECTORS 1
#endif

#ifndef DRV_NUM_VBR_SECTORS
#define DRV_NUM_VBR_SECTORS 1
#endif

#ifndef DRV_NUM_FAT_SECTORS
#define DRV_NUM_FAT_SECTORS 1
#endif

#define DRV_NUM_ROOT_SECTORS ((DRV_MAX_NUM_FILES_IN_ROOT+15)/16) //+15 because the compiler truncates
#define DRV_OVERHEAD_SECTORS (\
            DRV_NUM_RESERVED_SECTORS + \
            DRV_NUM_VBR_SECTORS + \
            DRV_NUM_ROOT_SECTORS + \
            DRV_NUM_FAT_SECTORS)
#define DRV_TOTAL_DISK_SIZE (\
            DRV_OVERHEAD_SECTORS + \
            DRV_CONFIG_DRIVE_CAPACITY)
#define DRV_PARTITION_SIZE (uint32_t)(DRV_TOTAL_DISK_SIZE - 1)  //-1 is to exclude the sector used for the MBR


//---------------------------------------------------------
//Do some build time error checking
//---------------------------------------------------------

#if (FILEIO_CONFIG_MEDIA_SECTOR_SIZE != 512)
#error "The current implementation of internal flash MDD only supports a media sector size of 512.  Please modify your selected value in the FSconfig.h file."
#endif

#if (DRV_MAX_NUM_FILES_IN_ROOT != 16) && \
    (DRV_MAX_NUM_FILES_IN_ROOT != 32) && \
    (DRV_MAX_NUM_FILES_IN_ROOT != 48) && \
    (DRV_MAX_NUM_FILES_IN_ROOT != 64)
#error "Number of root file entries must be a multiple of 16.  Please adjust the definition in the FSconfig.h file."
#endif

uint16_t ICSP_FileIo_InfoSize(void);
void ICSP_FileIo_InfoGet(uint8_t *pD, uint8_t seg);
uint8_t ICSP_FileIo_MediaDetect(void* config);
FILEIO_MEDIA_INFORMATION * ICSP_FileIo_MediaInitialize(void* config);
uint8_t ICSP_FileIo_SectorRead(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg);
uint8_t ICSP_FileIo_SectorWrite(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg);
uint16_t ICSP_FileIo_SectorSizeRead(void* config);
uint32_t ICSP_FileIo_CapacityRead(void* config);
uint8_t ICSP_FileIo_WriteProtectStateGet(void* config);
void ICSP_FileIo_Initialize(void);

#endif