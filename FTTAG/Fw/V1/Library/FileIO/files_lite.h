#ifndef FILES_LITE_H
#define FILES_LITE_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "files_lite_cfg.h"
#endif

// semantic versioning
#ifndef FILES_MAJOR
#define FILES_MAJOR             1 // change only when incompatible changes are made
#endif

#ifndef FILES_MINOR
#define FILES_MINOR             0 // change when adding functionality or fixing bugs
#endif

// this release date
#ifndef FILES_YEAR
#define FILES_YEAR              2020
#endif

#ifndef FILES_MONTH
#define FILES_MONTH             1   // January=1, February=2 ..
#endif

#ifndef FILES_DAY
#define FILES_DAY               1  // Day:1..31
#endif

#ifndef ROOT_ENTRY_SIZE
#define ROOT_ENTRY_SIZE         32  // standard root entry size
#endif

#ifndef ENTRY_FILE_SIZE_OFFSET
#define ENTRY_FILE_SIZE_OFFSET  28  // offset to entry.file_size field
#endif

#ifndef ENTRY_CLUSTER
#define ENTRY_CLUSTER           26  // offset of entry.cluster
#endif

void MasterBootRecordGet(uint8_t* buffer, uint8_t seg);
void VolumeBootRecordGet(uint8_t*buffer, uint8_t seg);
void FATRecordGet(uint8_t* buffer, uint8_t seg);
void FATRecordSet(uint8_t* buffer, uint8_t seg);
void RootRecordGet(uint8_t* buffer, uint8_t seg);
void RootRecordSet(uint8_t* buffer, uint8_t seg);
void RootRecordInit(void);
void FATRecordInit(void);

#endif