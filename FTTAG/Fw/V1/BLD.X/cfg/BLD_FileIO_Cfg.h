#ifndef BLD_FILEIO_CFG_H
#define BLD_FILEIO_CFG_H

#define __FIXED_INFO_SIZE__
#define __INFO_ADDRESS__    0x9D00C000
#define __PROJECT_NAME__    "FAST TOOL"
#define __HARDWARE_ID__     "SAMM-FTTAG"
#define __OWNER__           "SAMPI"
//#define BLD_FileIo_Log_Buffer       App_Log_Buffer // defined in libcomp.h

#define __CUSTOM_INFO__     __PROJECT_NAME__ " " __HARDWARE_ID__ \
                            "\nOwner: " __OWNER__ "\nBLD Rel: " __DATE__ "-" __TIME__ 

#endif