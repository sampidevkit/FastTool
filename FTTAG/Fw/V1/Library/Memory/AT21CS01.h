#ifndef AT21CS01_H
#define AT21CS01_H

#include "Common/LibDef.h"

#ifdef COMMON_LIB_CFG
#include "Common_Lib_Cfg.h"
#else
#include "AT21CS01_Cfg.h"
#endif

#define NO_DEVICE_DETECTED                  0xFF

#define AT21CS01_SWI_SUCCESS                ( 0)
#define AT21CS01_SWI_GENERAL_ERROR          (-1)
#define AT21CS01_SWI_WRITE_NACK             (-2)
#define AT21CS01_SWI_READ_NACK              (-3)
#define AT21CS01_SWI_REG_LOCKED             (-4)
#define AT21CS01_SWI_INVALID_EEPROM_ADDRESS (-5)
#define AT21CS01_SWI_INVALID_SIZE           (-6)
#define AT21CS01_SWI_OUT_OF_BOUNDS          (-7)
#define SWI_SUCCESS                         ( 0)

#define EEPROM_ADDRESS                      0x0A
#define SECREGACCESS                        0x0B
#define LOCKSECREG                          0x02
#define ROMZONEREGACCESS                    0x07
#define FREEZEROMZONESTATE                  0x01
#define MFGIDEAD                            0x0C
#define STDSPEEDMODE                        0x0D
#define HIGHSPEEDMODE                       0x0E

#define ROMZONEREG_MEMZONE0                 ((uint8_t)0x01)
#define ROMZONEREG_MEMZONE1                 ((uint8_t)0x02)
#define ROMZONEREG_MEMZONE2                 ((uint8_t)0x04)
#define ROMZONEREG_MEMZONE3                 ((uint8_t)0x08)

uint8_t  read_mfg_id(uint8_t dev_addr, uint8_t *buf);
uint8_t  read_security_register(uint8_t dev_addr,uint8_t parm1, uint8_t parm2, uint8_t *buf);
uint8_t  chk_high_speed_mode(uint8_t dev_addr, uint8_t *buf);
uint8_t  chk_std_speed_mode(uint8_t dev_addr, uint8_t *buf);
uint8_t  set_std_speed_mode(uint8_t dev_addr, uint8_t *buf);
uint8_t  set_high_speed_mode(uint8_t dev_addr, uint8_t *buf);
uint8_t  freeze_rom_zone_register(uint8_t dev_addr, uint8_t *buf);
uint8_t  reading_rom_zone_register(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buf);
uint8_t  writing_rom_zone_register(uint8_t dev_addr, uint8_t reg_addr, uint8_t *buf);
uint8_t  freeze_rom_zone_state(uint8_t dev_addr, uint8_t *buf);
uint8_t  lock_security_register(uint8_t dev_addr, uint8_t *buf);
uint8_t  write_security_register(uint8_t dev_addr, uint8_t arg1,uint8_t arg2, uint8_t *buf);
uint8_t  check_lock_command(uint8_t dev_addr, uint8_t *buf);
uint8_t  read_memory(uint8_t dev_addr, uint8_t mem_addr, uint8_t rlen,uint8_t *buf);
uint8_t  write_memory(uint8_t dev_addr, uint8_t mem_addr, uint8_t wlen,uint8_t *buf);
uint8_t  write_memory_buffer(uint8_t dev_addr, uint8_t mem_addr, uint8_t wlen,uint8_t *buf);
uint8_t  set_vcc_level(uint16_t vcc);
uint16_t get_current_meas(void);
uint8_t  scan_swi_device_addr (void);

#endif	
