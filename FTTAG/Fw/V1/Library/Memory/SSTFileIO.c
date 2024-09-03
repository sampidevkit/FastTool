#include "SSTFileIO.h"
#include "SST25xx.h"

public void SST_FILEIO_Format(void)
{
    SST_Chip_Erase();
}

public uint8_t SST_FILEIO_FileCount(void)
{
    
}

public sst_fileio_t *SST_FILEIO_FileCreate(const char *pFileName)
{
    
}

public bool SST_FILEIO_FileWrite(sst_fileio_t *pFile, const uint8_t *pData, uint32_t Len)
{
    
}

public bool SST_FILEIO_FileRead(sst_fileio_t *pFile, uint8_t *pData, uint32_t *pLen)
{
    
}

public void SST_FILEIO_FileDelete(const char *pFileName)
{
    
}

public sst_fileio_t *SST_FILEIO_Search(const char *pFileName)
{
    
}