#include "libcomp.h"
#include "ICSP_PIC16F188XX.h"

#ifdef FORCE_ICSP_ENTRY
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...) //printf(__VA_ARGS__)
#endif

// AC/DC characteristics timing requirements for program/verify mode - DS4000175B-page 23
// Programming mode entry and exit, 1INS = 125/3 ns @ FOSC=48MHz
#if(_XTAL_FREQ==24000000)
#define delay_TENTS()   {Nop(); Nop(); Nop();} //icsp_delay_us(1) //do{Nop(); Nop();}while(0) // 100ns                
#define delay_TENTH()   icsp_delay_us(100)
#define delay_TCKL()    {Nop(); Nop(); Nop();} //icsp_delay_us(1) //do{Nop(); Nop();}while(0) // 100ns
#define delay_TCKH()    {Nop(); Nop(); Nop(); Nop(); Nop(); Nop();} //icsp_delay_us(1) //do{Nop(); Nop();}while(0) // 100ns
#define delay_TDS()     {Nop(); Nop(); Nop();} //icsp_delay_us(1) //do{Nop(); Nop();}while(0) // 100ns
#define delay_TDH()     {Nop(); Nop(); Nop();} //icsp_delay_us(1) //do{Nop(); Nop();}while(0) // 100ns
#define delay_TCO()     {Nop(); Nop(); Nop();} //icsp_delay_us(1) //Nop() // 0-80ns
#define delay_TLZD()    {Nop(); Nop(); Nop();} //icsp_delay_us(1) //Nop() // 0-80ns
#define delay_THZD()    {Nop(); Nop(); Nop();} //icsp_delay_us(1) //Nop() // 0-80ns
#define delay_TDLY()    icsp_delay_us(1)
#define delay_TERAB()   icsp_delay_ms(14) // all MCU PIC16(L)F188xx
#define delay_TERAR()   icsp_delay_ms(3) // 2.8ms
#define delay_TPINT()   icsp_delay_ms(6) // 5.6ms
#define delay_TPEXT()   icsp_delay_ms(3) // 2.1ms
#define delay_TDIS()    icsp_delay_us(300)
#define delay_TEXIT()   icsp_delay_us(1)
#else
#define delay_TENTS()                 
#define delay_TENTH()   
#define delay_TCKL()    
#define delay_TCKH()    
#define delay_TDS()     
#define delay_TDH()     
#define delay_TCO()     
#define delay_TLZD()    
#define delay_THZD()    
#define delay_TDLY()    
#define delay_TERAB()   
#define delay_TERAR()   
#define delay_TPINT()   
#define delay_TPEXT()   
#define delay_TDIS()    
#define delay_TEXIT()   
#warning "Please define macros above"
#endif

#ifdef FORCE_ICSP_ENTRY
static FILE *pDecode=NULL;
#endif

static uint16_t PcAddress=TARGET_PFM_START;
// static uint16_t PcAddressBk=TARGET_PFM_START;
static uint16_t RowData[TARGET_ROW_WORD_SIZE];
static uint16_t UserIdData[TARGET_UID_WORD_LENGTH];
static uint16_t CfgData[TARGET_CFG_WORD_LENGTH];
static uint8_t EepromData[TARGET_EEP_BYTE_LENGTH];

private void PIC16F188XX_WriteCommand(uint8_t c) // <editor-fold defaultstate="collapsed" desc="Write a command">
{
    uint8_t i;

    ICSP_PGD_SetValue(ICSP_PGD_GetValue());
    delay_THZD();
    ICSP_PGD_SetDigitalOutput();

    for(i=0; i<8; i++)
    {
        if(c&0x80)
            ICSP_PGD_SetHigh();
        else
            ICSP_PGD_SetLow();

        c<<=1;
        ICSP_PGC_SetHigh();
        delay_TCKH();
        ICSP_PGC_SetLow();
        delay_TCKL();
    }

    ICSP_PGD_SetDigitalInput();
    delay_TDLY();
} // </editor-fold>

private void PIC16F188XX_Write24Bit(uint32_t c) // <editor-fold defaultstate="collapsed" desc="Write 24 bits">
{
    uint8_t i;

    ICSP_PGD_SetValue(ICSP_PGD_GetValue());
    delay_THZD();
    c=(c<<1)&0x7FFFFE;
    ICSP_PGD_SetDigitalOutput();

    for(i=0; i<24; i++)
    {
        if(c&0x00800000)
            ICSP_PGD_SetHigh();
        else
            ICSP_PGD_SetLow();

        c<<=1;
        ICSP_PGC_SetHigh();
        delay_TCKH();
        ICSP_PGC_SetLow();
        delay_TCKL();
    }

    ICSP_PGD_SetDigitalInput();
    delay_TDLY();
} // </editor-fold>

private uint32_t PIC16F188XX_Read24Bit(void) // <editor-fold defaultstate="collapsed" desc="Read 24 bits">
{
    uint8_t i;
    uint32_t c;

    delay_TLZD();
    ICSP_PGD_SetDigitalInput();

    for(i=0, c=0; i<24; i++)
    {
        ICSP_PGC_SetHigh();
        c<<=1;
        delay_TCKH();
        c|=ICSP_PGD_GetValue();
        ICSP_PGC_SetLow();
        delay_TCKL();
    }

    delay_TDLY();
    return ((c>>1)&0x3FFF);
} // </editor-fold>

private void PIC16F188XX_LoadData_NVM_PFM(bool J, uint16_t Instruction) // <editor-fold defaultstate="collapsed" desc="Load data for program flash memory (PFM)">
{
    uint32_t PayloadField=Instruction;

    if(J==1)
        PIC16F188XX_WriteCommand(LOAD_DATA_NVM_AFTER_WRITE);
    else
        PIC16F188XX_WriteCommand(LOAD_DATA_NVM_UNCHANGE_PC);

    PIC16F188XX_Write24Bit(PayloadField);

#ifdef FORCE_ICSP_ENTRY
    debug("%04X ", Instruction);
    fprintf(pDecode, "%04X ", Instruction);
#endif
} // </editor-fold>

private void PIC16F188XX_LoadData_NVM_DFM(bool J, uint8_t EEPData) // <editor-fold defaultstate="collapsed" desc="Load data for data flash memory (DFM)">
{
    uint32_t PayloadField=EEPData;

    if(J==1)
        PIC16F188XX_WriteCommand(LOAD_DATA_NVM_AFTER_WRITE);
    else
        PIC16F188XX_WriteCommand(LOAD_DATA_NVM_UNCHANGE_PC);

    PIC16F188XX_Write24Bit(PayloadField);

#ifdef FORCE_ICSP_ENTRY
    debug("%04X ", EEPData);
    fprintf(pDecode, "%04X ", EEPData);
#endif
} // </editor-fold>

private uint16_t PIC16F188XX_ReadData_NVM_PFM(bool J) // <editor-fold defaultstate="collapsed" desc="Read 14-bit instruction from PFM">
{
    if(J==1)
        PIC16F188XX_WriteCommand(READ_DATA_NVM_AFTER_WRITE);
    else
        PIC16F188XX_WriteCommand(READ_DATA_NVM_UNCHANGE_PC);

    return (uint16_t) PIC16F188XX_Read24Bit();
} // </editor-fold>

private uint8_t PIC16F188XX_ReadData_NVM_DFM(bool J) // <editor-fold defaultstate="collapsed" desc="Read 8-bit data from DFM">
{
    if(J==1)
        PIC16F188XX_WriteCommand(READ_DATA_NVM_AFTER_WRITE);
    else
        PIC16F188XX_WriteCommand(READ_DATA_NVM_UNCHANGE_PC);

    return (uint8_t) PIC16F188XX_Read24Bit();
    ;
} // </editor-fold>

#define PIC16F188XX_IncrementAddress() PIC16F188XX_WriteCommand(INCREMENT_ADDRESS)

private void PIC16F188XX_Load_PCAddress(uint16_t Address) // <editor-fold defaultstate="collapsed" desc="Load PC address">
{
    uint32_t PayloadField=Address;

    PIC16F188XX_WriteCommand(LOAD_PC_ADDRESS);
    PIC16F188XX_Write24Bit(PayloadField);

#ifdef FORCE_ICSP_ENTRY
    debug("\nPC %04X: ", Address);
    fprintf(pDecode, "\nPC %04X: ", Address);
#endif
} // </editor-fold>

private void PIC16F188XX_BeginInternalTimedProgram(void) // <editor-fold defaultstate="collapsed" desc="Begin internally timed program">
{
    PIC16F188XX_WriteCommand(BEGIN_INT_TIMED_PROG);
    delay_TPINT();
} // </editor-fold>

private void PIC16F188XX_EndProgram(void) // <editor-fold defaultstate="collapsed" desc="Begin internally timed program">
{
    PIC16F188XX_WriteCommand(END_EXT_TIMED_PROG);
    delay_TDIS();
} // </editor-fold>

public bool PIC16F188XX_BulkEraseMemory(void) // <editor-fold defaultstate="collapsed" desc="Erase memory of device">
{
    // Erase PFM, UID, CFG 
    PIC16F188XX_WriteCommand(LOAD_PC_ADDRESS);
    PIC16F188XX_Write24Bit(TARGET_CFG_START); // enter config area to erase config words too
    PIC16F188XX_WriteCommand(BULK_ERASE_PROGRAM_MEMORY);
    delay_TERAB();
    // Erase EEPROM
    PIC16F188XX_WriteCommand(LOAD_PC_ADDRESS);
    PIC16F188XX_Write24Bit(TARGET_EEP_START); // enter EEPROM area to erase
    PIC16F188XX_WriteCommand(BULK_ERASE_PROGRAM_MEMORY);
    delay_TERAB();

    return 1; // success
} // </editor-fold>

private void PIC16F188XX_RowEraseMemory(uint16_t Address) // <editor-fold defaultstate="collapsed" desc="Erase 1 page">
{
    PIC16F188XX_Load_PCAddress(GetRowAddress(Address));
    PIC16F188XX_WriteCommand(ROW_ERASE_PROGRAM_MEMORY);
    delay_TERAR();
} // </editor-fold>

public uint32_t PIC16F188XX_GetDeviceID(void) // <editor-fold defaultstate="collapsed" desc="Get device ID">
{
    PIC16F188XX_Load_PCAddress(TARGET_DID_START);

    return (uint32_t) PIC16F188XX_ReadData_NVM_PFM(0);
} // </editor-fold>

public void PIC16F188XX_InitICSP(void) // <editor-fold defaultstate="collapsed" desc="Initializes the GPIOs required for ICSP">
{
    ICSP_PGC_SetDigitalInput();
    ICSP_PGC_SetDigitalInput();
    ICSP_MCLR_SetDigitalInput();
    ICSP_PGC_Pullup_Set();
    ICSP_PGD_Pullup_Set();
} // </editor-fold>

public bool PIC16F188XX_EnterICSP(void) // <editor-fold defaultstate="collapsed" desc="ICSP entry">
{
    static uint8_t __try_again=0;

__LOOP:
    if(icsp_state.busy==0)
    {
        ICSP_PGC_Pullup_Set();
        ICSP_PGD_Pullup_Set();
        ICSP_PGC_SetLow();
        ICSP_PGD_SetLow();
        ICSP_MCLR_SetLow();
        ICSP_PGC_SetDigitalOutput();
        ICSP_PGD_SetDigitalOutput();
        ICSP_MCLR_SetDigitalOutput();
        delay_TENTH();
        PIC16F188XX_WriteCommand('M');
        PIC16F188XX_WriteCommand('C');
        PIC16F188XX_WriteCommand('H');
        PIC16F188XX_WriteCommand('P');

        uint32_t DevID=PIC16F188XX_GetDeviceID();
        // ICSP_Debug("Target ID: %08X\n", DevID);

#ifndef TARGET_MCU_PIC16F188XX
        if(DevID==TARGET_ID)
#else
        if((DevID>=TARGET_ID_MIN)&&(DevID<=TARGET_ID_MAX))
#endif
        {
            PcAddress=GetRowAddress(TARGET_PFM_START);
            // PcAddressBk=TARGET_PFM_START;
            icsp_memset16(RowData, 0x3FFF, TARGET_ROW_WORD_SIZE);
            icsp_memset16(UserIdData, 0x3FFF, TARGET_UID_WORD_LENGTH);
            icsp_memset16(CfgData, 0x3FFF, TARGET_CFG_WORD_LENGTH);
            icsp_memset8(EepromData, 0x00, TARGET_EEP_BYTE_LENGTH);

#ifndef TARGET_MCU_PIC16F188XX
            icsp_log(ICSP_LOG_SUCCESS, NULL, NULL, NULL);
#else
            if(DevID==0x306B)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18854");
            else if(DevID==0x306A)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18854");
            else if(DevID==0x306E)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18855");
            else if(DevID==0x306C)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18855");
            else if(DevID==0x3072)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18856");
            else if(DevID==0x3070)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18856");
            else if(DevID==0x3076)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18857");
            else if(DevID==0x3074)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18857");
            else if(DevID==0x306F)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18875");
            else if(DevID==0x306D)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18875");
            else if(DevID==0x3073)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18876");
            else if(DevID==0x3071)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18876");
            else if(DevID==0x3077)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16LF18877");
            else if(DevID==0x3075)
                icsp_log(ICSP_LOG_SUCCESS, &DevID, NULL, "PIC16F18877");
#endif
            //Icsp_Is_InProgress=1;
            __try_again=0;
            return 1;
        }

        PIC16F188XX_ExitICSP();
        icsp_log(ICSP_LOG_CHIPID_ERROR, &DevID, NULL, "Unsupported chip");

#ifdef FORCE_ICSP_ENTRY
        pDecode=fopen("Decode.txt", "w+");
        PcAddress=TARGET_PFM_START;
        // PcAddressBk=TARGET_PFM_START;
        icsp_memset16(RowData, 0x3FFF, TARGET_ROW_WORD_SIZE);
        icsp_memset16(UserIdData, 0x3FFF, TARGET_UID_WORD_LENGTH);
        icsp_memset16(CfgData, 0x3FFF, TARGET_CFG_WORD_LENGTH);
        icsp_memset8(EepromData, 0x00, TARGET_EEP_BYTE_LENGTH);
        debug("\nEnter ICSP\n");

        return 1;
#else
        if(++__try_again<3)
            goto __LOOP;
        else
            __try_again=0;
        return 0;
#endif
    }

    __try_again=0;

    return 1;
} // </editor-fold>

public void PIC16F188XX_ExitICSP(void) // <editor-fold defaultstate="collapsed" desc="Exit ICSP mode">
{
#ifdef FORCE_ICSP_ENTRY
    fclose(pDecode);
#endif

    PIC16F188XX_InitICSP();
    //ICSP_PGC_Pullup_Release();
    //ICSP_PGD_Pullup_Release();
    //Icsp_Is_InProgress=0;
    // ICSP_Debug("Exited ICSP mode\n");
} // </editor-fold>

private void PIC16F188XX_1WordProgram(uint16_t Address, uint16_t Data) // <editor-fold defaultstate="collapsed" desc="One word program cycle (for program UID and CFG)">
{
    PIC16F188XX_Load_PCAddress(Address); // load PC address
    PIC16F188XX_LoadData_NVM_PFM(0, Data); // load data
    PIC16F188XX_BeginInternalTimedProgram(); // begin program
} // </editor-fold>

/* ************************************************************************** */
private void PIC16F188XX_RowRead_PFM(void) // <editor-fold defaultstate="collapsed" desc="Multi word read cycle for PFM">
{
    uint16_t i;

    PIC16F188XX_Load_PCAddress(PcAddress); // load PC address

    for(i=0; i<TARGET_ROW_WORD_SIZE; i++)
        RowData[i]=PIC16F188XX_ReadData_NVM_PFM(1);
} // </editor-fold>

private void PIC16F188XX_RowProgram_PFM(void) // <editor-fold defaultstate="collapsed" desc="Multi word program cycle for PFM">
{
    uint16_t i;

    PIC16F188XX_Load_PCAddress(PcAddress); // load PC address

    for(i=0; i<(TARGET_ROW_WORD_SIZE-1); i++)
    {
        PIC16F188XX_LoadData_NVM_PFM(1, RowData[i]); // load data 0 to Len-1-1, increase address
        RowData[i]=0x3FFF; // preset value
    }

    PIC16F188XX_LoadData_NVM_PFM(0, RowData[i]); // load data at Len-1, not increase address
    RowData[i]=0x3FFF; // preset value
    PIC16F188XX_BeginInternalTimedProgram(); // begin program
    icsp_state.row_ready=0;
    //PIC16F188XX_IncrementAddress();
} // </editor-fold>

private void PIC16F188XX_EepProgram(void) // <editor-fold defaultstate="collapsed" desc="Multi word program cycle for EEPROM">
{
    uint16_t i;

    for(i=0; i<TARGET_EEP_BYTE_LENGTH; i++)
    {
        PIC16F188XX_1WordProgram(TARGET_EEP_START+i, EepromData[i]);
        EepromData[i]=0x00; // preset value
    }
} // </editor-fold>

private void PIC16F188XX_UserIdProgram(void) // <editor-fold defaultstate="collapsed" desc="Program user ID">
{
    uint16_t i;

    for(i=0; i<TARGET_UID_WORD_LENGTH; i++)
    {
        PIC16F188XX_1WordProgram(TARGET_UID_START+i, UserIdData[i]);
        UserIdData[i]=0x3FFF;
    }
} // </editor-fold>

private void PIC16F188XX_ConfigWordProgram(void) // <editor-fold defaultstate="collapsed" desc="Program configuration word">
{
    static const uint16_t CfgMask[TARGET_CFG_WORD_LENGTH]={
        TARGET_CFG_WORD1_MASK,
        TARGET_CFG_WORD2_MASK,
        TARGET_CFG_WORD3_MASK,
        TARGET_CFG_WORD4_MASK,
        TARGET_CFG_WORD5_MASK
    };

    uint8_t i;

    for(i=0; i<TARGET_CFG_WORD_LENGTH; i++)
    {
        CfgData[i]|=CfgMask[i];
        PIC16F188XX_1WordProgram(TARGET_CFG_START+i, CfgData[i]);
        CfgData[i]=0x3FFF; // preset value
    }
} // </editor-fold>

public int8_t PIC16F188XX_NVM_Write(uint32_t Addr, const uint8_t *pData, int Len) // <editor-fold defaultstate="collapsed" desc="Write hex data to flash">
{
    int i, j, idx;
    int8_t rslt=PROC_DONE;

    if(ICSP_Init(0)==0) // enter ICSP mode and bulk erase chip
    {
        rslt=PROC_ERR;
        write_error_log(__LINE__);
        goto EXIT;
    }

    if(Len==0) // finish programming
    {
        // Write the last row
        if(icsp_state.row_ready)
        {
            debug("\nWrite last row\n");
            PIC16F188XX_RowProgram_PFM();
        }
        // Write User ID
        if(icsp_state.uid_ready)
        {
            debug("\nWrite last user ID\n");
            PIC16F188XX_UserIdProgram();
        }
        // Write EEPROM data
        if(icsp_state.eep_ready) // write EEP before CFG
        {
            debug("\nWrite last eeprom\n");
            PIC16F188XX_EepProgram();
        }
        // Write Configuration Word
        if(icsp_state.cfg_ready)
        {
            debug("\nWrite last cfg\n");
            PIC16F188XX_ConfigWordProgram();
        }
        // all icsp_state flags will be reset after exiting
        goto EXIT;
    }
    else // programming process
    {
        Addr/=2;

        if(!icsp_valid_address_check(Addr, Len))
        {
            rslt=PROC_ERR;
            debug("\n%s, line %d\n", __FILE__, __LINE__);
            debug("\nAddr: %04X, Len: %d\n", Addr, Len);
            goto EXIT;
        }

        if((Addr>=TARGET_PFM_START)&&(Addr<=TARGET_PFM_END)) // PFM zone
        {
ONCE_AGAIN:
            if(PcAddress==GetRowAddress(Addr)) // data in 1 row
            {
                debug("\nThe same row %04X\n", Addr);
                icsp_state.row_ready=1;
                idx=(int) (Addr-PcAddress);

                for(i=0, j=0; i<Len; i+=2, j++)
                {
                    if((idx+j)>=TARGET_ROW_WORD_SIZE)
                    {
                        Len-=i;
                        Addr+=j;
                        pData+=i;
                        goto ONCE_AGAIN;
                    }

                    RowData[idx+j]=icsp_convert2x8to16(&pData[i]);
                }
            }
            else if(PcAddress<GetRowAddress(Addr)) // data of the next row
            {
                debug("\nNext row %04X\n", Addr);

                if(icsp_state.row_ready)
                {
                    debug("\nWrite before next row\n");
                    PIC16F188XX_RowProgram_PFM();
                }

                PcAddress=GetRowAddress(Addr);
                goto ONCE_AGAIN;
            }
            else // data of the previous row
            {
                // PIC16F188XX_RowProgram_PFM(); // write current row data
                // PcAddressBk=PcAddress+TARGET_ROW_WORD_SIZE; // backup the next row address
                // PcAddress=GetRowAddress(Addr); // update previous address
                // PIC16F188XX_RowRead_PFM(); // read previous data
                // PIC16F188XX_RowEraseMemory(PcAddress); // erase previous row
                // goto ONCE_AGAIN;
                rslt=PROC_ERR;
                write_error_log(__LINE__);
                goto EXIT;
            }
        }
        else if((Addr>=TARGET_UID_START)&&(Addr<=TARGET_UID_END)) // User ID zone
        {
            debug("\nUser ID\n");
            icsp_state.uid_ready=1;
            idx=(int) (Addr-TARGET_UID_START);

            for(i=0, j=0; i<Len; i+=2, j++)
                UserIdData[idx+j]=icsp_convert2x8to16(&pData[i]);
        }
        else if((Addr>=TARGET_CFG_START)&&(Addr<=TARGET_CFG_END)) // Configuration zone
        {
            debug("\nConfig\n");
            icsp_state.cfg_ready=1;
            idx=(int) (Addr-TARGET_CFG_START);

            for(i=0, j=0; i<Len; i+=2, j++)
                CfgData[idx+j]=icsp_convert2x8to16(&pData[i]);
        }
        else if((Addr>=TARGET_EEP_START)&&(Addr<=TARGET_EEP_END)) // EEPROM zone
        {
            debug("\nEeprom\n");
            icsp_state.eep_ready=1;
            idx=(int) (Addr-TARGET_EEP_START);

            for(i=0, j=0; i<Len; i+=2, j++)
                EepromData[idx+j]=(uint8_t) icsp_convert2x8to16(&pData[i]);
        }
        else
        {
            rslt=PROC_ERR;
            write_error_log(__LINE__);
            goto EXIT;
        }
    }

    return PROC_DONE;

EXIT:
    ICSP_Deinit();

    return rslt;
} // </editor-fold>

public int8_t PIC16F188XX_NVM_StreamOut(void (*pStreamFnc)(uint8_t c)) // <editor-fold defaultstate="collapsed" desc="Read data from NVM">
{
    static uint16_t Addr;
    uint32_t w;
    uint8_t DoNext=0;
    int8_t rslt=PROC_ERR;

    switch(DoNext)
    {
        case 0:
            if(ICSP_Init(0)==0) // enter ICSP mode and bulk erase chip
            {
                write_error_log(__LINE__);
                goto EXIT;
            }

            DoNext++;
            Addr=TARGET_PFM_START;
            pStreamFnc(':');
            pStreamFnc(':');
            pStreamFnc(':');
            break;

        case 1:
            break;

        default:
            break;
    }

    return PROC_BUSY;

EXIT:
    ICSP_Deinit();

    return rslt;
} // </editor-fold>