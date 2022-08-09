#ifndef UTIL_H
#define UTIL_H

#include "LibDef.h"

typedef struct {
    uint8_t idx;
    const uint8_t *pStr;
} strcmp_t;

#define StrCmp_Init(cxt, src) do{cxt.idx=0; cxt.pStr=(uint8_t*)src;}while(0)

/* ******************************************************** STRING PROCESSING */
public uint8_t UpperCase(uint8_t Data);
public uint8_t LowerCase(uint8_t Data);
public void str_uppercase(uint8_t *pData);
public void str_lowercase(uint8_t *pData);
public bool FindString(uint8_t c, size_t *pIdx, const uint8_t *pStrSample);
uint16_t Copy_Str2Break(const uint8_t *pDatain, uint8_t break_byte, uint8_t *pDataout);
uint16_t str_len2break(const uint8_t *pData, uint8_t break_byte);
public bool str_cmp(const uint8_t *pDatain, int Len, const uint8_t *pSample);
public bool str_cmp_without_case(const uint8_t *pDatain, int Len, const uint8_t *pSample);
public int str_remove(char *p, char c);
public void str_sremove(char *str, char c, uint8_t amount);
public uint16_t str_nremove(char *p, const char *c);
public uint8_t str_is_number(char c);
public uint16_t str_count(const char *p, char c);
public int str_1st_index(const char *p, char c);
public char *str_first(const char *p, char c);
public char *str_last(const char *p, char c);
public uint32_t Parse(const uint8_t *c, uint8_t num);
public bool is_printable(uint8_t c);
public int8_t StrCmp(strcmp_t *pCxt, uint8_t c);
public bool findSString(uint8_t *pDatain, int LenS, const uint8_t *pSample);
public bool delSString(uint8_t *pDatain, const uint8_t *pSample);
/* ************************************************** CRYPTOGRAPHY PROCESSING */
uint16_t crc_ccitt(uint16_t crc, const uint8_t *buf_p, size_t size);
public uint16_t Crc16_Calc(const uint8_t *pData, uint16_t len);
public uint16_t Mask(uint8_t *pData, uint16_t len);
public uint16_t UnMask(uint8_t *pData, uint16_t len);
public uint8_t CalcSum8(const void *pData, uint16_t len);
/* ****************************************************** DATA TYPE CONVERTER */
public uint32_t Swap_nBits(uint32_t Value, uint8_t nBit);
public uint16_t Swap_2Bytes(uint16_t Value);
public void Convert16to2x8(uint16_t Value, uint8_t *pArr);
public void Convert32to4x8(uint32_t Value, uint8_t *pArr);
public uint16_t Convert2x8to16(const uint8_t *pArr);
public uint32_t Convert4x8to32(const uint8_t *pArr);
public int32_t ConvertStr2Integer(const uint8_t *pArr);
public uint32_t StrHex2Int(uint8_t *p);
public int BinSearch(const uint8_t *pSource, int Size);
public void PrintHex(const uint8_t *pSource, int Size, int NumOfCol);
public uint8_t bits_reverse_8(uint8_t value);
public uint32_t bits_reverse_16(uint32_t value);
public uint32_t bits_reverse_32(uint32_t value);
public uint32_t bits_mask_32(int width);
public uint32_t bits_insert_32(uint32_t dst, int position, int size, uint32_t src);
public uint8_t Bcd2Hex(uint8_t i);
///* **************************************************************** DATE TIME */
extern const uint8_t DayOfMonth[12];
public bool CheckLeapYear(uint16_t Year);
public uint8_t Calc_DayOfWeek(uint32_t Day, uint32_t Month, uint32_t Year);
public uint8_t Dec2BCD(uint8_t hexvalue);
public uint8_t BCD2Dec(uint8_t bcdvalue);

#endif