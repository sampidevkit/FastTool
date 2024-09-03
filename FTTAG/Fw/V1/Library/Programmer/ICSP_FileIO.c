#include "libcomp.h"
#include "ICSP_FileIO.h"

#ifndef ICSP_FileIo_Media_GetState
#define ICSP_FileIo_Media_GetState()        1
#endif

#ifndef ICSP_FileIo_WriteProtect_GetState
#define ICSP_FileIo_WriteProtect_GetState() 0
#endif

// <editor-fold defaultstate="collapsed" desc="Definition">
private FILEIO_MEDIA_INFORMATION mediaInformation;

#ifndef USE_BLD_INFO
private const uint8_t _Icsp_Project_Info[]={
    __PROJECT_NAME__"\n"
    __HARDWARE_ID__"\n"
    __TARGET_NAME__"\n"
    "Rel: " __DATE__ "-" __TIME__
    "\n" __WEBSITE__ "\n"
    "Status: "
};

#define ICSP_PROJECT_INFO_LEN   ((sizeof(_Icsp_Project_Info) / sizeof((_Icsp_Project_Info)[0]))-1)
#define Icsp_Project_Info(x)    _Icsp_Project_Info[x]
#else

//private uint8_t Icsp_Project_Info(uint32_t idx)
//{
//    uint8_t data[4];
//    uint32_t *pD=(uint32_t *)data;
//    
//    *pD=FLASH_ReadWord((idx&0xFFFFFFFC)+__INFO_ADDRESS__);
//    idx=idx&0x03;
//    
//    return data[idx];
//}
//
//private uint32_t Icsp_Project_Info_Len(void)
//{
//    static uint32_t __info_len=0;
//    
//    if(__info_len==0)
//    {
//        while(Icsp_Project_Info(__info_len)!=0)
//            __info_len++;
//    }
//    
//    return __info_len;
//}

#define Icsp_Project_Info(x)    0
#define ICSP_PROJECT_INFO_LEN   0 //Icsp_Project_Info_Len()
#endif
// </editor-fold>

uint16_t ICSP_FileIo_InfoSize(void) // <editor-fold defaultstate="collapsed" desc="Get size of INFO.TXT file">
{
    return (uint16_t) (ICSP_PROJECT_INFO_LEN+strlen(Icsp_Log_Buffer)); // length of file does not include EOF
} // </editor-fold>

void ICSP_FileIo_InfoGet(uint8_t *pD, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Get 1 segment of data log">
{
    uint32_t i, j, k;
    uint32_t idx=seg*MSD_IN_EP_SIZE;

    for(i=0; i<MSD_IN_EP_SIZE; i++)
    {
        j=idx+i;

        if(j<ICSP_PROJECT_INFO_LEN)
            *pD=Icsp_Project_Info(j);
        else
        {
            k=(j-ICSP_PROJECT_INFO_LEN);

            if(k<strlen(Icsp_Log_Buffer))
                *pD=Icsp_Log_Buffer[k];
            else
                *pD=0xFF;
        }

        pD++;
    }
} // </editor-fold>

FILEIO_MEDIA_INFORMATION * ICSP_FileIo_MediaInitialize(void* config) // <editor-fold defaultstate="collapsed" desc="Media initialize">
{
    if(!ICSP_Is_Initialized())
    {
        ICSP_Init(1);
        ICSP_Deinit();
    }

    mediaInformation.validityFlags.bits.sectorSize=true;
    mediaInformation.sectorSize=FILEIO_CONFIG_MEDIA_SECTOR_SIZE;
    mediaInformation.errorCode=MEDIA_NO_ERROR;

    return &mediaInformation;
} // </editor-fold>

uint8_t ICSP_FileIo_MediaDetect(void* config) // <editor-fold defaultstate="collapsed" desc="Check target chip ready or not">
{
    return ICSP_FileIo_Media_GetState();
} // </editor-fold>

uint8_t ICSP_FileIo_WriteProtectStateGet(void* config) // <editor-fold defaultstate="collapsed" desc="Check write protection state">
{
    return ICSP_FileIo_WriteProtect_GetState();
} // </editor-fold>

uint16_t ICSP_FileIo_SectorSizeRead(void* config) // <editor-fold defaultstate="collapsed" desc="Get sector size">
{
    return FILEIO_CONFIG_MEDIA_SECTOR_SIZE;
} // </editor-fold>

uint32_t ICSP_FileIo_CapacityRead(void* config) // <editor-fold defaultstate="collapsed" desc="Get capacity">
{
    return ((uint32_t) DRV_TOTAL_DISK_SIZE-1);
} // </editor-fold>

uint8_t ICSP_FileIo_SectorRead(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Read sector">
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
            ICSP_FileIo_InfoGet(buffer, seg);
            break;

        default:
            break;
    }

    return true;
} // </editor-fold>

uint8_t ICSP_FileIo_SectorWrite(void* config, uint32_t sector_addr, uint8_t* buffer, uint8_t seg) // <editor-fold defaultstate="collapsed" desc="Write sector">
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
        {
            // icsp_log(ICSP_LOG_INTERNAL_ERROR, NULL, NULL);
            return false;
        }
    }

    return true;
} // </editor-fold>