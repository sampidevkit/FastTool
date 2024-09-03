#include "Icsp.h"
#include "libcomp.h"

// External variables defined in Icsp.h
public bool icsp_initialized=0;
public icsp_state_t icsp_state={.val=0x00};

int int2hexstr(uint8_t *pStr, uint32_t Val) // <editor-fold defaultstate="collapsed" desc="Convert integer to hex string">
{
    uint8_t i, j, k;

    pStr[0]='0';
    pStr[1]='x';

    for(i=0, k=0; i<8; i++)
    {
        j=(uint8_t) (Val>>28);

        if((j>0)||(k>0))
        {
            if(j<10)
                pStr[k+2]=j+'0';
            else
                pStr[k+2]=(j-10)+'A';

            k++;
        }

        Val<<=4;
    }

    if(k==0)
    {
        pStr[k+2]='0';
        k++;
        pStr[k+2]='0';
        k++;
    }

    pStr[k+2]=',';
    k++;
    pStr[k+2]=' ';
    k++;

    return k+2; // length
} // </editor-fold>

int str_cpy(uint8_t *pDes, const uint8_t *pSrc) // <editor-fold defaultstate="collapsed" desc="Copy string to buffer, return source length">
{
    int i=0;

    while(*pSrc!=0x00)
    {
        *pDes=*pSrc;
        pDes++;
        pSrc++;
        i++;
    }

    *pDes=0x00;

    return i;
} // </editor-fold>

public void icsp_log(icsp_stt_code_t LogCode, uint32_t *Arg1, uint32_t *Arg2, const uint8_t *Arg3) // <editor-fold defaultstate="collapsed" desc="Write the last state of process in full message">
{
#ifdef ICSP_LOG_HW_INFO
    static int hw_info_len=0;
#endif

    int i;

    if(LogCode==ICSP_LOG_SUCCESS)
    {
#ifndef ICSP_LOG_HW_INFO
        i=0;
        i+=str_cpy(&Icsp_Log_Buffer[i], Arg3);
        i+=str_cpy(&Icsp_Log_Buffer[i], ", ID: ");
        i+=int2hexstr(&Icsp_Log_Buffer[i], *Arg1);
        i+=str_cpy(&Icsp_Log_Buffer[i], "OK");
#else
        if(hw_info_len==0)
        {
            hw_info_len=Hardware_Info(&Icsp_Log_Buffer[0]);
            i=hw_info_len;
            i+=str_cpy(&Icsp_Log_Buffer[i], Arg3);
            i+=str_cpy(&Icsp_Log_Buffer[i], ", ID: ");
            i+=int2hexstr(&Icsp_Log_Buffer[i], *Arg1);
            i+=str_cpy(&Icsp_Log_Buffer[i], "OK");
        }
#endif
    }
    else
    {
#ifndef ICSP_LOG_HW_INFO
        i=0;
#else
        hw_info_len=0;
        i=Hardware_Info(&Icsp_Log_Buffer[0]);
#endif

        switch(LogCode)
        {
            case ICSP_LOG_INVALID_ADDR: // 1
                i+=str_cpy(&Icsp_Log_Buffer[i], "INVALID_ADDR: ");
                break;

            case ICSP_LOG_ADDR_NOT_ALIG_DWORD: // 2
                i+=str_cpy(&Icsp_Log_Buffer[i], "ADDR_NOT_ALIG_DWORD: ");
                break;

            case ICSP_LOG_LEN_NOT_MUL_ROW: // 3
                i+=str_cpy(&Icsp_Log_Buffer[i], "LEN_NOT_MUL_ROW: ");
                break;

            case ICSP_LOG_ADDR_NOT_ALIG_ROW: // 4
                i+=str_cpy(&Icsp_Log_Buffer[i], "ADDR_NOT_ALIG_ROW: ");
                break;

            case ICSP_LOG_LEN_NOT_MUL_PAGE: // 5
                i+=str_cpy(&Icsp_Log_Buffer[i], "LEN_NOT_MUL_PAGE: ");
                break;

            case ICSP_LOG_ADDR_NOT_ALIG_PAGE: // 6
                i+=str_cpy(&Icsp_Log_Buffer[i], "ADDR_NOT_ALIG_PAGE: ");
                break;

            case ICSP_LOG_CHIPID_ERROR: // 7
                i+=str_cpy(&Icsp_Log_Buffer[i], "CHIPID: ");
                break;

            case ICSP_LOG_ROW_PROG_ERROR: // 8
                i+=str_cpy(&Icsp_Log_Buffer[i], "ROW_PROG: ");
                break;

            case ICSP_LOG_READ_ERROR: // 9
                i+=str_cpy(&Icsp_Log_Buffer[i], "READ: ");
                break;

            case ICSP_LOG_ERASE_ERROR: // A
                i+=str_cpy(&Icsp_Log_Buffer[i], "ERASE: ");
                break;

            case ICSP_LOG_NOT_BLANK_ERROR: // B
                i+=str_cpy(&Icsp_Log_Buffer[i], "NOT_BLANK: ");
                break;

            case ICSP_LOG_CHECKSUM_ERROR: // C
                i+=str_cpy(&Icsp_Log_Buffer[i], "CHECKSUM: ");
                break;

            case ICSP_LOG_DWORD_PROG_ERROR: // D
                i+=str_cpy(&Icsp_Log_Buffer[i], "DWORD_PROG: ");
                break;

            case ICSP_LOG_INTERNAL_ERROR: // E
            default:
                i+=str_cpy(&Icsp_Log_Buffer[i], "INTERNAL: ");
                break;
        }

        if(Arg1!=NULL)
            i+=int2hexstr(&Icsp_Log_Buffer[i], *Arg1);

        if(Arg2!=NULL)
            i+=int2hexstr(&Icsp_Log_Buffer[i], *Arg2);

        i+=str_cpy(&Icsp_Log_Buffer[i], "ERROR");
    }
} // </editor-fold>

public void icsp_delay_ms(uint32_t t) // <editor-fold defaultstate="collapsed" desc="Long delay">
{
    Delay_Ms(t);
} // </editor-fold>

public void icsp_delay_us(uint32_t t) // <editor-fold defaultstate="collapsed" desc="Local delay function">
{
    tick_t Start=Tick_Timer_Get_TickVal();
    tick_t Duration=t*TICK_PER_US;

    while((Tick_Timer_Get_TickVal()-Start)<Duration)
        ClrWdt();
} // </editor-fold>

public uint32_t icsp_convert4x8to32(const uint8_t *pArr) // <editor-fold defaultstate="collapsed" desc="Convert 4x8bit to 32bit">
{
    uint32_t Value=pArr[3];

    Value<<=8;
    Value|=pArr[2];
    Value<<=8;
    Value|=pArr[1];
    Value<<=8;
    Value|=pArr[0];

    return Value;
} // </editor-fold>

public uint16_t icsp_convert2x8to16(const uint8_t *pArr) // <editor-fold defaultstate="collapsed" desc="Convert 2x8bit to 16bit">
{
    uint32_t Value=pArr[1];

    Value<<=8;
    Value|=pArr[0];

    return Value;
} // </editor-fold>

public void icsp_memcpy32(uint32_t *pDes, const uint32_t *pSrc, uint32_t Len) // <editor-fold defaultstate="collapsed" desc="Copy 32bit data">
{
    while(Len>0)
    {
        *pDes=*pSrc;
        pDes++;
        pSrc++;
        Len--;
    }
} // </editor-fold>

public void icsp_memcpy16(uint16_t *pDes, const uint16_t *pSrc, uint16_t Len) // <editor-fold defaultstate="collapsed" desc="Copy 16bit data">
{
    while(Len>0)
    {
        *pDes=*pSrc;
        pDes++;
        pSrc++;
        Len--;
    }
} // </editor-fold>

public void icsp_memset32(uint32_t *pDes, uint32_t Value, uint32_t Len) // <editor-fold defaultstate="collapsed" desc="Set value for 32bit memory">
{
    uint32_t i;

    for(i=0; i<Len; i++)
    {
        *pDes=Value;
        pDes++;
    }
} // </editor-fold>

public void icsp_memset16(uint16_t *pDes, uint16_t Value, uint16_t Len) // <editor-fold defaultstate="collapsed" desc="Set value for 16bit memory">
{
    uint16_t i;

    for(i=0; i<Len; i++)
    {
        *pDes=Value;
        pDes++;
    }
} // </editor-fold>

public void icsp_memset8(uint8_t *pDes, uint8_t Value, uint16_t Len) // <editor-fold defaultstate="collapsed" desc="Set value for 8bit memory">
{
    uint16_t i;

    for(i=0; i<Len; i++)
    {
        *pDes=Value;
        pDes++;
    }
} // </editor-fold>

public bool icsp_valid_address_check(uint32_t startAddress, uint32_t length) // <editor-fold defaultstate="collapsed" desc="Check valid address">
{
    uint32_t endAddress;

#if(TARGET_CPU_TYPE>8)
    endAddress=startAddress+(4*length)-1;
#else
    endAddress=startAddress+(length/2)-1;
#endif

#ifdef TARGET_PFM_START
    if((startAddress>=TARGET_PFM_START)&&(endAddress<=TARGET_PFM_END))
        return 1;
#endif

#ifdef TARGET_BFM_START
    if((startAddress>=TARGET_BFM_START)&&(endAddress<=TARGET_BFM_END))
        return 1;
#endif

#ifdef TARGET_CFG_START
    if((startAddress>=TARGET_CFG_START)&&(endAddress<=TARGET_CFG_END))
        return 1;
#endif

#ifdef TARGET_UDID_START
    if((startAddress>=TARGET_UDID_START)&&(endAddress<=TARGET_UDID_END))
        return 1;
#endif

#ifdef TARGET_UID_START
    if((startAddress>=TARGET_UID_START)&&(endAddress<=TARGET_UID_END))
        return 1;
#endif

#ifdef TARGET_EEP_START
#if(TARGET_CPU_TYPE==8)
    endAddress=startAddress+length-1;
#endif

    if((startAddress>=TARGET_EEP_START)&&(endAddress<=TARGET_EEP_END))
        return 1;
#endif

    // ICSP_Debug("invalid address %08X to %08X\n", startAddress, endAddress);
    icsp_log(ICSP_LOG_INVALID_ADDR, &startAddress, &endAddress, NULL);

    return 0;
} // </editor-fold>

public bool icsp_row_aligned_address_check(uint32_t Address, uint32_t length) // <editor-fold defaultstate="collapsed" desc="Check aligned and boundary address of row">
{
    uint32_t tmp;

    if(icsp_valid_address_check(Address, length)) // Check boundary
    {
        tmp=TARGET_ROW_WORD_SIZE;

        if((Address&(tmp-1))==0)
        {
#if(TARGET_CPU_TYPE>8)
            Address+=(4*length);
#else
            Address+=(2*length);
#endif

            if((Address&(tmp-1))==0)
                return 1;

            // ICSP_Debug("Length %08X isn't multiple of row %d\n", length, TARGET_ROW_WORD_SIZE);
            icsp_log(ICSP_LOG_LEN_NOT_MUL_ROW, &length, &tmp, NULL);
        }
        else
        {
            // ICSP_Debug("Address %08X isn't aligned by row %d\n", Address, TARGET_ROW_WORD_SIZE);
            icsp_log(ICSP_LOG_ADDR_NOT_ALIG_ROW, &Address, &tmp, NULL);
        }
    }

    return 0;
} // </editor-fold>

public bool icsp_page_aligned_address_check(uint32_t Address, uint32_t length) // <editor-fold defaultstate="collapsed" desc="Check aligned and boundary address of page">
{
    uint32_t tmp;

    if(icsp_valid_address_check(Address, length)) // Check boundary
    {
        tmp=TARGET_PAGE_WORD_SIZE;

        if((Address&(tmp-1))==0)
        {
#if(TARGET_CPU_TYPE>8)
            Address+=(4*length);
#else
            Address+=(2*length);
#endif

            if((Address&(tmp-1))==0)
                return 1;

            // ICSP_Debug("Length %08X isn't multiple of page %d\n", length, TARGET_PAGE_WORD_SIZE);
            icsp_log(ICSP_LOG_LEN_NOT_MUL_PAGE, &length, &tmp, NULL);
        }
        else
        {
            // ICSP_Debug("Address %08X isn't aligned by page %d\n", Address, TARGET_PAGE_WORD_SIZE);
            icsp_log(ICSP_LOG_ADDR_NOT_ALIG_PAGE, &length, &tmp, NULL);
        }
    }

    return 0;
} // </editor-fold>

public void ICSP_Deinit(void) // <editor-fold defaultstate="collapsed" desc="Deinit ICSP Mode">
{
    ICSP_VDDTG_EN_SetLow(); // disable target VDD
    ICSP_VBUS_EN_N_SetHigh(); // disable ICSP VBUS
    ICSP_Exit();
    icsp_state.val=0x00;
    ICSP_Deinit_UserCb();
    ICSP_Deinit_Indicator();
    ICSP_VDDTG_EN_SetHigh();
    ICSP_VBUS_EN_N_SetDigitalInput(); // release ICSP VBUS pin
} // </editor-fold>

public bool ICSP_Init(bool EraseDis) // <editor-fold defaultstate="collapsed" desc="Init ICSP Mode">
{
    if(ICSP_VDDTG_EN_GetValue()==0)
        ICSP_VDDTG_EN_SetHigh(); // enable target VDD

    if(ICSP_VBUS_EN_N_GetValue()==1)
    {
        ICSP_VBUS_EN_N_SetLow(); // enable ICSP VBUS
        ICSP_VBUS_EN_N_SetDigitalOutput();
    }

    if(icsp_state.busy==0)
    {
        ICSP_Init_Indicator();
        ICSP_Init_UserCb();
        __delay_ms(50);

        if(ICSP_Entry())
        {
            icsp_initialized=1;

            if(EraseDis)
                icsp_state.busy=1;
            else if(ICSP_ChipErase()) // Erase chip
            {
                if(ICSP_DownloadPE())
                {
                    if(ICSP_BlankCheck()) // Check blank   
                        icsp_state.busy=1;
                    else
                        ICSP_Error_Indicator();
                }
                else
                    ICSP_Error_Indicator();
            }
            else
                ICSP_Error_Indicator();
        }
        else
            ICSP_Error_Indicator();
    }

    if(icsp_state.busy==0)
        ICSP_Deinit();

    return icsp_state.busy;
} // </editor-fold>
