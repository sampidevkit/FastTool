#include "libcomp.h"
#include "BLD_Nvm_PIC18.h"
#include "BLD_Target_Device.h"

private bool bld_nvm_initialized=0;

private struct
{
    uint32_t addr;
    uint8_t idx;
    uint8_t data[BLD_NVM_TARGET_DEVICE_PAGE_SIZE];
} BldNvmPack;

private bool BLD_Nvm_IsWritable(uint32_t Addr) // <editor-fold defaultstate="collapsed" desc="Check writable address">
{
    if((Addr>=APP_BEGIN_ADDRESS)&&(Addr<=APP_END_ADDRESS))
        return 1;

    return 0;
} // </editor-fold>

private void BLD_Nvm_FullErase(void) // <editor-fold defaultstate="collapsed" desc="Full media memory erasing">
{
    uint32_t Addr=APP_BEGIN_ADDRESS;
    uint32_t NumOfPage=APP_SIZE_IN_PAGE;

    while(NumOfPage>0)
    {
        ClrWdt();
        NumOfPage--;
        BLD_Nvm_EraseBlock(Addr);
        Addr+=BLD_NVM_TARGET_DEVICE_PAGE_SIZE;
    }
} // </editor-fold>

private bool BLD_Nvm_Init(void) // <editor-fold defaultstate="collapsed" desc="Init memory">
{
    if(bld_nvm_initialized==0)
    {
        BLD_Nvm_UnLock();
        BLD_Nvm_FullErase();
        BldNvmPack.addr=(APP_BEGIN_ADDRESS);
        memset((uint8_t*) BldNvmPack.data, 0xFF, BLD_NVM_TARGET_DEVICE_PAGE_SIZE);
        bld_nvm_initialized=1;
    }

    return bld_nvm_initialized;
} // </editor-fold>

private void BLD_Nvm_Deinit(void) // <editor-fold defaultstate="collapsed" desc="Deinit memory">
{
    BLD_Nvm_Lock();
    bld_nvm_initialized=0;
    BLD_Nvm_SystemReboot();
} // </editor-fold>

private int8_t BLD_Nvm_Pack(uint32_t Addr, const uint8_t *pData) // <editor-fold defaultstate="collapsed" desc="Add 2 bytes to buffer">
{
    uint16_t prvPackIdx=(uint16_t) (BldNvmPack.addr>>7);
    uint16_t prePackIdx=(uint16_t) (Addr>>7);

    if(prvPackIdx!=prePackIdx)
    {
        BldNvmPack.addr&=TARGET_PACK_BYTE_MASK;

        if(BLD_Nvm_WriteBlock(BldNvmPack.addr, BldNvmPack.data))
            return PROC_ERR;

        if(prvPackIdx<prePackIdx) // new pack
            memset((uint8_t*) BldNvmPack.data, 0xFF, BLD_NVM_TARGET_DEVICE_PAGE_SIZE);
        else // old pack
            return PROC_ERR;
    }

    BldNvmPack.idx=(uint8_t) (Addr&TARGET_PACK_IDX_MASK);
    BldNvmPack.data[BldNvmPack.idx]=pData[0];
    BldNvmPack.data[BldNvmPack.idx+1]=pData[1];
    BldNvmPack.addr=Addr;

    return PROC_DONE;
} // </editor-fold>

public int8_t BLD_Nvm_Write(uint32_t Addr, const uint8_t *pData, int Len) // <editor-fold defaultstate="collapsed" desc="Write hex data to flash">
{
    int i;
    int8_t rslt=PROC_DONE;

    if(BLD_Nvm_Init()==0)
        goto EXIT;

    if(Len==0) // finish
    {
        uint8_t dummy[2]={0xFF, 0xFF};

        rslt=BLD_Nvm_Pack((APP_END_ADDRESS+1), dummy);
        goto EXIT;
    }

    for(i=0; i<Len; i+=2)
    {
        if(BLD_Nvm_IsWritable(Addr))
        {
            rslt=BLD_Nvm_Pack(Addr, &pData[i]);

            if(rslt==PROC_ERR)
                goto EXIT;
        }

        Addr+=2;
    }

    return PROC_DONE;

EXIT:
    BLD_Nvm_Deinit();

    return rslt;
} // </editor-fold>