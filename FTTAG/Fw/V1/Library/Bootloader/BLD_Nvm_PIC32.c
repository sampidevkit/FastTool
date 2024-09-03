#include "libcomp.h"
#include "BLD_Nvm_PIC32.h"
#include "BLD_Target_Device.h"

typedef struct
{
    uint32_t Address;
    uint32_t Word0;
    uint32_t Word1;
} bld_nvm_t;

private bool bld_nvm_initialized=0;

private uint32_t BLD_Nvm_Convert4x8to32(const uint8_t *pArr) // <editor-fold defaultstate="collapsed" desc="Convert 32bit to 4x8bit">
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

private bool BLD_Nvm_IsWritable(uint32_t Addr) // <editor-fold defaultstate="collapsed" desc="Check writable address">
{
    if((Addr>=APP_BEGIN_ADDRESS)&&(Addr<=APP_END_ADDRESS))
        return 1;

    return 0;
} // </editor-fold>

private bool BLD_Nvm_FullErase(void) // <editor-fold defaultstate="collapsed" desc="Full media memory erasing">
{
    uint32_t Addr=APP_BEGIN_ADDRESS;
    uint32_t NumOfPage=APP_SIZE_IN_PAGE;

    while(NumOfPage>0)
    {
        NumOfPage--;

        if(!FLASH_ErasePage(Addr))
            return 0; // error

        Addr+=BLD_NVM_TARGET_DEVICE_PAGE_SIZE;
    }

    return 1;
} // </editor-fold>

private bool BLD_Nvm_Init(void) // <editor-fold defaultstate="collapsed" desc="Init memory">
{
    if(bld_nvm_initialized==0)
    {
        BLD_Nvm_UnLock();
        bld_nvm_initialized=BLD_Nvm_FullErase();
    }

    return bld_nvm_initialized;
} // </editor-fold>

private void BLD_Nvm_Denit(void) // <editor-fold defaultstate="collapsed" desc="Deinit memory">
{
    BLD_Nvm_Lock();
    bld_nvm_initialized=0;
    BLD_Nvm_SystemReboot();
} // </editor-fold>

private bool BLD_Nvm_DWordPack(bld_nvm_t *pBldNvm) // <editor-fold defaultstate="collapsed" desc="Write double word then checksum">
{
    bool rslt=0;

    if(BLD_Nvm_Init())
    {
        if((pBldNvm->Word0!=0xFFFFFFFF)||(pBldNvm->Word1!=0xFFFFFFFF))
        {
            if(BLD_Nvm_IsWritable(pBldNvm->Address))
            {
                if(FLASH_WriteDoubleWord(pBldNvm->Address, pBldNvm->Word0, pBldNvm->Word1))
                    rslt=1;
            }
            else
                rslt=1;

            pBldNvm->Word0=0xFFFFFFFF; // add blanked data
            pBldNvm->Word1=0xFFFFFFFF; // add blanked data
        }
        else
            rslt=1;
    }

    return rslt;
} // </editor-fold>

public int8_t BLD_Nvm_Write(uint32_t Addr, const uint8_t *pData, int Len) // <editor-fold defaultstate="collapsed" desc="Write hex data to flash">
{
    // copy only the bytes from the current data packet up to the boundary of a row
    int8_t rslt=PROC_DONE;
    private bld_nvm_t bld_nvm={0, 0xFFFFFFFF, 0xFFFFFFFF};

    // Check the last data
    if(Len==0)
    {
        if(!BLD_Nvm_DWordPack(&bld_nvm))
            rslt=PROC_ERR;

        goto EXIT;
    }

    while(Len>0)
    {
        // Check boundary of DWord
        if((Addr&0xFFFFFFF8)!=bld_nvm.Address)
        {
            if(bld_nvm.Address!=0) // Skip in the first time
            {
                if(!BLD_Nvm_DWordPack(&bld_nvm))
                {
                    rslt=PROC_ERR;
                    goto EXIT;
                }
            }

            bld_nvm.Address=(Addr&0xFFFFFFF8); // update new row address
        }
        // Check current address is of Word0 or Word1
        if((Addr&7)==0) // Word 0 address
            bld_nvm.Word0=BLD_Nvm_Convert4x8to32(pData);
        else // if((Addr&4)==4) // Word 1 address
            bld_nvm.Word1=BLD_Nvm_Convert4x8to32(pData);

        pData+=4;
        Addr+=4;
        Len-=4;
    }

    return PROC_DONE;

EXIT:
    bld_nvm.Address=0; // Reset the 1st start address
    BLD_Nvm_Denit();

    return rslt;
} // </editor-fold>