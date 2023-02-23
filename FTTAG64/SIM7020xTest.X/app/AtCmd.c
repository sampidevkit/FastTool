#include "libcomp.h"
#include "AtCmd.h"

#undef __db
#define __db(...)

static uint8_t DoNext=0;
static size_t RxCount=0;
static tick_timer_t TickRaw={1, 0, 0};
buff_t AtCmdRxBkBuff;

void ATCMD_Init(void)
{
    DoNext=0;
    RxCount=0;
    AtCmdRxBkBuff.Len=0;
    AtCmdRxBkBuff.pData=NULL;
    Tick_Timer_Reset(TickRaw);
}

void ATCMD_SendRaw(const uint8_t *pD, size_t sz)
{
    // Get all response data in Rx buffer before send new data
    while(ATCMD_Port_IsRxReady())
        ATCMD_Port_Read();

    while(sz>0)
    {
        if(ATCMD_Port_IsTxReady())
        {
            ATCMD_Port_Write(*pD++);
            sz--;
        }
    }

    while(ATCMD_Port_IsTxDone());
    Tick_Timer_Reset(TickRaw);
    RxCount=0;
}

int8_t ATCMD_GetRaw(uint8_t *pD, size_t *pSz, uint16_t firstWait, uint16_t lastWait)
{
    while(ATCMD_Port_IsRxReady())
    {
        uint8_t c=ATCMD_Port_Read();

        Tick_Timer_Reset(TickRaw);
        __db("%c", c);
        pD[RxCount++]=c;
    }

    if(RxCount==0)
    {
        if(Tick_Timer_Is_Over_Ms(TickRaw, firstWait))
        {
            if(pSz!=NULL)
                *pSz=RxCount;

            pD[RxCount]=0x00;
            RxCount=0;

            return PROC_ERR;
        }
    }
    else if(Tick_Timer_Is_Over_Ms(TickRaw, lastWait))
    {
        if(pSz!=NULL)
            *pSz=RxCount;

        pD[RxCount]=0x00;
        RxCount=0;

        return PROC_DONE;
    }

    return PROC_BUSY;
}

int8_t ATCMD_SendGetDat(const char *pTx, char *pRx, uint16_t firstWait, uint16_t lastWait)
{
    int8_t rslt=PROC_BUSY;

    switch(DoNext)
    {
        case 0:
            DoNext++;
            __db("\nTX: %s\nRX: ", pTx);
            ATCMD_SendRaw((uint8_t*) pTx, strlen(pTx));
            break;

        case 1:
        default:
            rslt=ATCMD_GetRaw((uint8_t*) pRx, NULL, firstWait, lastWait);

            if(rslt!=PROC_BUSY)
                DoNext=0;
            break;
    }

    return rslt;
}

int8_t ATCMD_SendGetAck(const char *pTx, const char *pAck, uint16_t firstWait, uint16_t lastWait)
{
    switch(DoNext)
    {
        case 0:
            DoNext++;
            AtCmdRxBkBuff.Len=0;
            __db("\nTX: %s\nRX: ", pTx);
            ATCMD_SendRaw((uint8_t*) pTx, strlen(pTx));
            break;

        case 1:
        default:
            while(ATCMD_Port_IsRxReady())
            {
                uint8_t c=ATCMD_Port_Read();

                Tick_Timer_Reset(TickRaw);
                __db("%c", c);

                if(AtCmdRxBkBuff.pData!=NULL)
                {
                    AtCmdRxBkBuff.pData[AtCmdRxBkBuff.Len++]=c;
                    AtCmdRxBkBuff.pData[AtCmdRxBkBuff.Len]=0;
                }
                
                if(FindString(c, &RxCount, (uint8_t *) pAck))
                {
                    DoNext=0;
                    return PROC_DONE;
                }
            }

            if(RxCount==0)
            {
                if(Tick_Timer_Is_Over_Ms(TickRaw, firstWait))
                {
                    DoNext=0;
                    __db("RX timeout");
                    return PROC_ERR;
                }
            }
            else if(Tick_Timer_Is_Over_Ms(TickRaw, lastWait))
            {
                DoNext=0;
                __db("Not found");
                return PROC_ERR;
            }
            break;
    }

    return PROC_BUSY;
}