#ifndef SSTFILEIO_H
#define	SSTFILEIO_H

#include "user_app_config.h"

#if(USE_SST_FLASH)

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "SSTFileIO_Cfg.h"
#endif

typedef struct {
    uint16_t BeginAddr;
    uint16_t EndAddr;
    uint16_t AccessAddr;
} sst_fileio_t;

public void SST_FILEIO_Format(void);
public uint8_t SST_FILEIO_FileCount(void);
public sst_fileio_t *SST_FILEIO_FileCreate(const char *pFileName);
public bool SST_FILEIO_FileWrite(sst_fileio_t *pFile, const uint8_t *pData, uint32_t Len);
public bool SST_FILEIO_FileRead(sst_fileio_t *pFile, uint8_t *pData, uint32_t *pLen);
public void SST_FILEIO_FileDelete(const char *pFileName);
public sst_fileio_t *SST_FILEIO_Search(const char *pFileName);

#endif
#endif