#ifndef KIT_PIC32MM_I2C_H
#define KIT_PIC32MM_I2C_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "kit_pic32mm_i2c_cfg.h"
#endif

#define KIT_I2C_OK      0
#define KIT_I2C_BUSY    1
#define KIT_I2C_ERR     (-1)

/* This library works with I2C [foundation services library by MCHP] + I2CSIMPLE
 * + 16 bit I2CMASTER 
 * Define these macros:
    #define KIT_I2Cx_MasterOpen(slvaddr)         i2c_open(slvaddr)
    #define KIT_I2Cx_MasterClose()               i2c_close()
    #define KIT_I2Cx_MasterSetBuffer(pD, len)    i2c_setBuffer((void*) pD, (size_t) len)
    #define KIT_I2Cx_MasterOperation(rw)         i2c_masterOperation(rw)
 */

#ifdef USE_KIT_I2C1
public int8_t KIT_I2C1_GetState(void);
public void KIT_I2C1_Enable(void); // enabled by user, automatic disable
public void KIT_I2C1_Wait(void);
public void KIT_I2C1_Xfer(uint8_t SlvAddr, uint8_t *pDi, uint8_t Li, uint8_t *pDo, uint8_t Lo);
public void KIT_I2C1_Tasks(void*);
#endif

#ifdef USE_KIT_I2C2
public int8_t KIT_I2C2_GetState(void);
public void KIT_I2C2_Enable(void); // enabled by user, automatic disable
public void KIT_I2C2_Wait(void);
public void KIT_I2C2_Xfer(uint8_t SlvAddr, uint8_t *pDi, uint8_t Li, uint8_t *pDo, uint8_t Lo);
public void KIT_I2C2_Tasks(void*);
#endif

#ifdef USE_KIT_I2C3
public int8_t KIT_I2C3_GetState(void);
public void KIT_I2C3_Enable(void); // enabled by user, automatic disable
public void KIT_I2C3_Wait(void);
public void KIT_I2C3_Xfer(uint8_t SlvAddr, uint8_t *pDi, uint8_t Li, uint8_t *pDo, uint8_t Lo);
public void KIT_I2C3_Tasks(void*);
#endif

#endif