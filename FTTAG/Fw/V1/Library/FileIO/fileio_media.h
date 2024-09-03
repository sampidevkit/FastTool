#ifndef FILEIO_MEDIA_H
#define FILEIO_MEDIA_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "fileio_cfg.h"
#endif

// Enumeration to define media error types

typedef enum {
    MEDIA_NO_ERROR, // No errors
    MEDIA_DEVICE_NOT_PRESENT, // The requested device is not present
    MEDIA_CANNOT_INITIALIZE // Cannot initialize media
} FILEIO_MEDIA_ERRORS;

// Media information flags.  The driver's MediaInitialize function will return a pointer to one of these structures.

typedef struct {
    FILEIO_MEDIA_ERRORS errorCode; // The status of the initialization FILEIO_MEDIA_ERRORS
    // Flags

    union {
        uint8_t value;

        struct {
            uint8_t sectorSize : 1; // The sector size parameter is valid.
            uint8_t maxLUN : 1; // The max LUN parameter is valid.
        } bits;
    } validityFlags;

    uint16_t sectorSize; // The sector size of the target device.
    uint8_t maxLUN; // The maximum Logical Unit Number of the device.
} FILEIO_MEDIA_INFORMATION;

#endif