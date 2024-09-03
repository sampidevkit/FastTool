#include "libcomp.h"
#include "HexParsing.h"

public int8_t HEXPARSE_Hex2Integer(int8_t c, uint8_t NumOfDigit, uint32_t *pVal, uint8_t *pCks) // <editor-fold defaultstate="collapsed" desc="Check hex">
{
    static uint8_t i=0, j=0, val=0;

    if(i==0)
        val=0;

    if(j==0)
        *pVal=0;

    val<<=4;

    if((c>='0')&&(c<='9'))
        val|=(uint8_t) (c-'0');
    else if((c>='A')&&(c<='F'))
        val|=(uint8_t) (c-'A'+10);
    else if((c>='a')&&(c<='f'))
        val|=(uint8_t) (c-'a'+10);
    else
    {
        i=0;
        j=0;
        *pCks=0;
        return PROC_ERR;
    }

    i++;

    if(i>=2)
    {
        i=0;
        j+=2;
        *pCks=*pCks+val;
        *pVal=*pVal<<8;
        *pVal|=val;
        val=0;

        if(j>=NumOfDigit)
        {
            j=0;
            return PROC_DONE;
        }
    }

    return PROC_BUSY;
} // </editor-fold>

public int8_t HEXPARSE_Tasks(int8_t c) // <editor-fold defaultstate="collapsed" desc="Intel hex parsing">
{
#define debug(...) //printf(__VA_ARGS__)

    uint32_t tmp;
    int8_t this_task_rslt;
    static hex_t Hex={0, 0, 0};
    static uint32_t addr, val=0, line=0;
    static uint8_t i, cks=0, phase=0, numofdigit=2;

    this_task_rslt=HEXPARSE_Hex2Integer(c, numofdigit, &val, &cks);

    if(this_task_rslt==PROC_ERR)
    {
        if(phase!=0)
        {
            write_error_log(__LINE__);
            goto EXIT;
        }
    }
    else if(this_task_rslt==PROC_BUSY)
        return PROC_BUSY;

    this_task_rslt=PROC_ERR;

    switch(phase)
    {
        case 0: // <editor-fold defaultstate="collapsed" desc="Get start code">
            if(c==':')
            {
                numofdigit=2;
                Hex.ByteCount=0;
                phase=1;
                debug("\nLine %05d: ", line++);
            } // </editor-fold>
            break;

        case 1: // <editor-fold defaultstate="collapsed" desc="Get byte count">
            Hex.ByteCount=(uint8_t) val;
            numofdigit=4;
            phase=2;
            debug("Len=%02d, ", Hex.ByteCount); // </editor-fold>
            break;

        case 2: // <editor-fold defaultstate="collapsed" desc="Get address">
            addr=val;
            numofdigit=2;
            phase=3;
            Hex.RecordType=0; // </editor-fold>
            break;

        case 3: // <editor-fold defaultstate="collapsed" desc="Get record type">
            Hex.RecordType=(uint8_t) val;

            switch(Hex.RecordType)
            {
                case HEX_RECTYPE_DAT:
                    i=0;
                    phase=4;
                    numofdigit=2;
                    Hex.Address.Value=addr;
                    debug("Addr=%08X, DAT, ", Hex.Address.Value+Hex.Address.ExtLin+Hex.Address.ExtSeg);
                    break;

                case HEX_RECTYPE_EOF:
                    phase=7;
                    numofdigit=0;
                    debug("Addr=%08X, EOF, ", addr);
                    break;

                case HEX_RECTYPE_ESA:
                    debug("Addr=%08X, ESA, ", addr);
                    addr=0;
                    phase=5;
                    numofdigit=4;
                    break;

                case HEX_RECTYPE_ELA:
                    debug("Addr=%08X, ELA, ", addr);
                    addr=0;
                    phase=6;
                    numofdigit=4;
                    break;

                case HEX_RECTYPE_SSA:
                case HEX_RECTYPE_SLA:
                default:
                    debug("UNKNOWN");
                    write_error_log(__LINE__);
                    goto EXIT;
            } // </editor-fold>
            break;

        case 4: // <editor-fold defaultstate="collapsed" desc="Get data">
            Hex.Data[i]=(uint8_t) val;
            debug("%02X", Hex.Data[i]);

            if(++i==Hex.ByteCount)
            {
                phase=7;
                Hex.Checksum=0;
                debug(", ");
            }
            else
                debug(" "); // </editor-fold>
            break;

        case 5: // <editor-fold defaultstate="collapsed" desc="Get extended segment address">
            addr=val;
            phase=7;
            numofdigit=2;
            debug("%04X, ", addr);
            Hex.Address.ExtSeg=(addr<<8);
            Hex.Address.ExtLin=0; // </editor-fold>
            break;

        case 6: // <editor-fold defaultstate="collapsed" desc="Get extended linear address">
            addr=val;
            phase=7;
            numofdigit=2;
            debug("%04X, ", addr);
            Hex.Address.ExtLin=(addr<<16);
            Hex.Address.ExtSeg=0; // </editor-fold>
            break;

        case 7: // <editor-fold defaultstate="collapsed" desc="Get checksum">
            Hex.Checksum=(uint8_t) val;
            phase=0;
            numofdigit=2;
            debug("CRC %02X", Hex.Checksum);

            if((cks&0xFF)==0x00)// checksum matched
            {
                if(Hex.RecordType==HEX_RECTYPE_DAT)
                {
                    tmp=Hex.Address.Value+Hex.Address.ExtLin+Hex.Address.ExtSeg;

                    if(HEXPARSE_NVM_Write(tmp, Hex.Data, Hex.ByteCount)==PROC_ERR)
                    {
                        debug("\nWrite data error\n");
                        //write_error_log(__LINE__);
                        goto EXIT;
                    }
                }
                else if(Hex.RecordType==HEX_RECTYPE_EOF)
                {
                    this_task_rslt=PROC_DONE;
                    goto EXIT;
                }
            }
            else
            {
                debug(" - Error: %02X\n", cks&0xFF);
                write_error_log(__LINE__);
                goto EXIT;
            } // </editor-fold>
            break;

        default:
            debug("\nError, unknown state %d", phase);
            write_error_log(__LINE__);
            goto EXIT;
    }

    return PROC_BUSY;

EXIT:
    val=0;
    line=0;
    phase=0;
    cks=0;
    numofdigit=2;
    Hex.Address.ExtLin=0;
    Hex.Address.ExtSeg=0;

    if(this_task_rslt==PROC_DONE)
    {
        if(HEXPARSE_NVM_Write(0, NULL, 0)==PROC_ERR) // Write the last data and/or reset all states in HEXPARSE_NVM_Write
        {
            debug("\nWrite the last DWord error\n");
            write_error_log(__LINE__);
            this_task_rslt=PROC_ERR;
        }
    }

    return this_task_rslt;
#undef debug
} // </editor-fold>

public void HEXPARSE_PutLine(uint8_t *pData, uint8_t Len) // <editor-fold defaultstate="collapsed" desc="Put hex line">
{
    uint8_t c;
    
    HEXPARSE_StreamOut(':');
    HEXPARSE_StreamOut(Bcd2Hex(Len>>4));
} // </editor-fold>