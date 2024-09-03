#include "libcomp.h"
#include "BLD_FileIO.h"
#include "Programmer/HexParsing.h"
#include "BLD_Target_Device.h"

// <editor-fold defaultstate="collapsed" desc="Definition">
private FILEIO_MEDIA_INFORMATION mediaInformation;

#ifdef __FIXED_INFO_SIZE__
#ifdef __INFO_ADDRESS__
private const uint8_t Info[144] __attribute__((address(__INFO_ADDRESS__), space(prog)))=
#else
private const uint8_t Info[144]=
#endif
#else
#ifdef __INFO_ADDRESS__
private const uint8_t Info[] __attribute__((address(__INFO_ADDRESS__), space(prog)))=
#else
private const uint8_t Info[]=
#endif
#endif
{
#ifndef __CUSTOM_INFO__
    __PROJECT_NAME__"\n"
    __HARDWARE_ID__"\n"
    __BLD_NVM_TARGET_DEVICE_NAME__"\n"
    "Rel: " __DATE__ "-" __TIME__
    "\n" __WEBSITE__ "\n"
    "Owner: " __OWNER__ "\n"
#else
    __CUSTOM_INFO__
#endif
#ifdef BLD_FileIo_Log_Buffer
    "Status: "
#endif
};

#define BLD_NVM_INFO_LEN (strlen(Info)-1) //((sizeof(Info) / sizeof((Info)[0]))-1)

// </editor-fold>

uint16_t BLD_FileIo_InfoSize(void) // <editor-fold defaultstate="collapsed" desc="Get size of INFO.TXT file">
{
#ifdef BLD_FileIo_Log_Buffer
    return (uint16_t) (BLD_NVM_INFO_LEN+strlen(BLD_FileIo_Log_Buffer)); // length of file does not include EOF
#else
    return (uint16_t) (BLD_NVM_INFO_LEN);
#endif
} // </editor-fold>

void BLD_FileIo_InfoGet(uint8_t *pD, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Get 1 segment of data log">
{
    uint32_t i, j, k;
    uint32_t idx=seg*MSD_IN_EP_SIZE;

    for(i=0; i<MSD_IN_EP_SIZE; i++)
    {
        j=idx+i;

        if(j<BLD_NVM_INFO_LEN)
            *pD=Info[j];
        else
        {
#ifdef BLD_FileIo_Log_Buffer
            k=(j-BLD_NVM_INFO_LEN);

            if(k<strlen(BLD_FileIo_Log_Buffer))
                *pD=BLD_FileIo_Log_Buffer[k];
            else
                *pD=0xFF;
#else
            *pD=0xFF;
#endif
        }

        pD++;
    }
} // </editor-fold>

FILEIO_MEDIA_INFORMATION * BLD_FileIo_MediaInitialize(void* config) // <editor-fold defaultstate="collapsed" desc="Media initialize">
{
    mediaInformation.validityFlags.bits.sectorSize=true;
    mediaInformation.sectorSize=FILEIO_CONFIG_MEDIA_SECTOR_SIZE;
    mediaInformation.errorCode=MEDIA_NO_ERROR;

    return &mediaInformation;
} // </editor-fold>

uint8_t BLD_FileIo_MediaDetect(void* config) // <editor-fold defaultstate="collapsed" desc="Check target chip ready or not">
{
    return true;
} // </editor-fold>

uint8_t BLD_FileIo_WriteProtectStateGet(void* config) // <editor-fold defaultstate="collapsed" desc="Check write protection state">
{
    return false;
} // </editor-fold>

uint16_t BLD_FileIo_SectorSizeRead(void* config) // <editor-fold defaultstate="collapsed" desc="Get sector size">
{
    return FILEIO_CONFIG_MEDIA_SECTOR_SIZE;
} // </editor-fold>

uint32_t BLD_FileIo_CapacityRead(void* config) // <editor-fold defaultstate="collapsed" desc="Get capacity">
{
    return ((uint32_t) DRV_TOTAL_DISK_SIZE-1);
} // </editor-fold>

uint8_t BLD_FileIo_SectorRead(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Read sector">
{
    memset(buffer, '\0', MSD_IN_EP_SIZE); // empty buffer
    // Read a sector worth of data, and copy it to the specified RAM "buffer"

    switch((uint8_t) sector_addr)
    {
        case 1:
            VolumeBootRecordGet(buffer, seg);
            break;

        case 2:
            FATRecordGet(buffer, seg);
            break;

        case 3:
            RootRecordGet(buffer, seg);
            break;

        case 4: // at most 64 bytes at a time
            BLD_FileIo_InfoGet(buffer, seg);
            break;

        default:
            break;
    }

    return true;
} // </editor-fold>

uint8_t BLD_FileIo_SectorWrite(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Write sector">
{
    uint8_t i;

    if((sector_addr<2)||(sector_addr>=DRV_TOTAL_DISK_SIZE))
        return false;

    if(sector_addr<4)
        return true;

    for(i=0; i<MSD_IN_EP_SIZE; i++) // all remaining data sectors are parsed and programmed directly into the device
    {
        int8_t rslt=HEXPARSE_Tasks(*buffer++);

        if(rslt==PROC_DONE)
            return true;
        else if(rslt==PROC_ERR)
            return false;
    }

    return true;
} // </editor-fold>