#ifndef CRC32_H
#define CRC32_H

#include "Common/LibDef.h"
#include "crc_cfg.h"

public uint32_t crc32(const uint8_t *buffer, uint32_t len);

#endif