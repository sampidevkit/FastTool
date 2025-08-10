#include "Debug.h"

#ifdef USE_SYSTIME_STAMP
#include "System/TickTimer.h"
#endif

#ifdef TASKMANAGER_H
public sem_declare(debug);
#endif

/* ********************************************************** Local variables */
static int8_t _i;
static int8_t _idx;
static uint8_t _digit[10];

#ifdef USE_SOFTUART_DEBUG
static char cSREG;

#ifdef __AVR__
#define SysInt_Backup()     do{cSREG=SREG; /* store SREG value */ cli();}while(0)
#define SysInt_Restore()    SREG=cSREG; /* restore SREG value (I-bit) */
#elif defined(__PIC__)

#else
#error "Please define SysInt_Backup() and SysInt_Restore() in debug_cfg.h"
#endif

void debug_port_write(uint8_t c) // <editor-fold defaultstate="collapsed" desc="SoftUART put a char">
{
    char i;

    SysInt_Backup();
    // Start bit
    DBG_TX_SetLow();
    //DBG_TX_TRIS=0;
    __debug_bit_delay();
    // Data bits
    for(i=0; i<8; i++)
    {
        if(c&1)
            DBG_TX_SetHigh();
        else
            DBG_TX_SetLow();

        c>>=1;
        __debug_bit_delay();
    }
    // Stop bit
    DBG_TX_SetHigh();
    __debug_bit_delay();
    SysInt_Restore();
} // </editor-fold>
#endif

#if defined(NUM_OF_DEBUG_PORT) && (NUM_OF_DEBUG_PORT>=2)
//dbg_port_cxt_t DebugPort[NUM_OF_DEBUG_PORT]; // External variables
static const dbg_port_cxt_t *ActivePort=NULL;

void debug_port_sel(uint8_t portIdx)
{
    if(portIdx<NUM_OF_DEBUG_PORT)
        ActivePort=&DebugPort[portIdx];
}

void debug_port_write(uint8_t c)
{
    while(!ActivePort->IsTxReady())
    {
        if(ActivePort->Wait)
            ActivePort->Wait();
    }

    ActivePort->Write(c);

    while(!ActivePort->IsTxDone())
    {
        if(ActivePort->Wait)
            ActivePort->Wait();
    }

    ClrWdt();
}
#endif

#ifdef USE_SYSTIME_STAMP

void debug_systime_stamp(void)
{
    debug_port_write('\n');
    debug_port_write('[');
    debug_u32((uint32_t) Tick_Get()/TICK_PER_MS);
    debug_port_write(']');
    debug_port_write(' ');
}
#endif

void debug(const char *str, bool tsEn)
{
#ifdef USE_SYSTIME_STAMP
    if(tsEn==1)
        debug_systime_stamp();
#endif

    while(*str!=0x00)
        debug_port_write(*str++);
}

void debug_hex(uint32_t b, uint8_t dgcount)
{
    for(_i=7; _i>=0; _i--)
    {
        _digit[_i]=(uint8_t) (b&0x0F);

        if(_digit[_i]>9)
        {
            _digit[_i]-=10;
            _digit[_i]+='A';
        }
        else
            _digit[_i]+='0';

        b>>=4;
    }

    if(dgcount&0x80)
    {
        debug_port_write('0');
        debug_port_write('x');
    }

    dgcount&=0x7F;

    for(_i=0, _idx=8; _i<8; _i++)
    {
        if((_digit[_i]=='0')&&(_idx>dgcount))
        {
            _idx--;
            continue;
        }

        _idx=0;
        debug_port_write(_digit[_i]);
    }
}

void debug_hexs(uint8_t *pD, int len)
{
    while(len>1)
    {
        debug_hex(*pD++, 2|HEX_HEADER);
        debug_port_write(' ');
        len--;
    }

    debug_hex(*pD++, 2|HEX_HEADER);
}

void debug_u32(uint32_t b)
{
    for(_i=9; _i>=0; _i--)
    {
        _digit[_i]=((uint8_t) (b%10))+'0';
        b/=10;
    }

    for(_i=0, _idx=1; _i<10; _i++)
    {
        if(_digit[_i]!='0')
            _idx=0;

        if(_idx==0)
            debug_port_write(_digit[_i]);
    }

    if(_idx==1)
        debug_port_write('0');
}

void debug_i32(int32_t b)
{
    if(b<0)
    {
        debug_port_write('-');
        b*=(-1);
    }

    debug_u32((uint32_t) b);
}

void debug_data(uint8_t *pD, int len)
{
    while(len>0)
    {
        if((*pD>=' ')&&(*pD<='~'))
            debug_port_write(*pD);
        else
        {
            debug_port_write('<');
            debug_hex(*pD, 2);
            debug_port_write('>');
        }

        pD++;
        len--;
    }
}

void debug_time(tm_t *time)
{
    debug_u32((uint32_t) time->tm_hour);
    debug_port_write(':');
    debug_u32((uint32_t) time->tm_min);
    debug_port_write(':');
    debug_u32((uint32_t) time->tm_sec);
}

void debug_date(tm_t *time)
{
    debug_u32((uint32_t) time->tm_mday);
    debug_port_write('/');
    debug_u32((uint32_t) time->tm_mon);
    debug_port_write('/');
    debug_u32((uint32_t) time->tm_year);
}

/* ********************************************************************* APIs */
void dbsi(const char *str, int32_t x, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_i32(x);
}

void dbsu(const char *str, uint32_t x, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_u32(x);
}

void dbsh(const char *str, uint32_t x, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_hex(x, 0x88);
}

void dbsc(const char *str, char c, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_port_write(c);
}

void dbss(const char *str1, const char *str2, bool tsEn)
{
    debug((const char *) (str1), tsEn);
    debug((const char *) (str2), 0);
}

void dbstime(const char *str, tm_t tcxt, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_time(&tcxt);
}

void dbsdate(const char *str, tm_t tcxt, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_date(&tcxt);
}

void dbsdata(const char *str, uint8_t *pd, int len, bool tsEn)
{
    debug((const char *) (str), tsEn);
    debug_data(pd, len);
}