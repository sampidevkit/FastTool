#include "Button.h"
#include "libcomp.h"

bt_cxt_t ModeBtCxt={NOT_PRESS, 0, NULL, NULL, NULL};

bt_stt_t BUTTON_GetState(bt_cxt_t *pBtCxt, bool preInput) // <editor-fold defaultstate="collapsed" desc="Button UP">
{
    switch(pBtCxt->DoNext)
    {
        case NOT_PRESS:
            if(preInput==0)
            {
                pBtCxt->DoNext=SINGLE_PRESS;
                pBtCxt->Begin=Tick_Get();
            }
            break;

        case SINGLE_PRESS:
            if(preInput==1)
            {
                if(Tick_Dif(Tick_Get(), pBtCxt->Begin)>=(TICK_PER_MS*50))
                {
                    pBtCxt->DoNext=NEXT_PRESS;
                    pBtCxt->Begin=Tick_Get();
                }
                else
                {
                    pBtCxt->DoNext=NOT_PRESS;
                    break;
                }
            }
            else if(Tick_Dif(Tick_Get(), pBtCxt->Begin)>=(TICK_PER_MS*2000))
            {
                pBtCxt->DoNext=WAIT_RELEASE;

                if(pBtCxt->HoldPressCallback)
                    pBtCxt->HoldPressCallback();

                return HOLD_PRESS;
            }
            break;

        case NEXT_PRESS:
            if(preInput==0)
            {
                pBtCxt->Begin=Tick_Get();
                pBtCxt->DoNext=DOUBLE_PRESS;
            }
            else if(Tick_Dif(Tick_Get(), pBtCxt->Begin)>=(TICK_PER_MS*150))
            {
                pBtCxt->DoNext=NOT_PRESS;

                if(pBtCxt->SinglePressCallback)
                    pBtCxt->SinglePressCallback();

                return SINGLE_PRESS;
            }
            break;

        case DOUBLE_PRESS:
            if(preInput==1)
            {
                pBtCxt->DoNext=WAIT_RELEASE;

                if(pBtCxt->DoublePressCallback)
                    pBtCxt->DoublePressCallback();

                return DOUBLE_PRESS;
            }
            else if(Tick_Dif(Tick_Get(), pBtCxt->Begin)>=(TICK_PER_MS*2000))
            {
                pBtCxt->DoNext=WAIT_RELEASE;

                if(pBtCxt->HoldPressCallback)
                    pBtCxt->HoldPressCallback();

                return HOLD_PRESS;
            }
            break;

        case WAIT_RELEASE:
        default:
            if(preInput==1)
                pBtCxt->DoNext=NOT_PRESS;
            break;
    }

    return NOT_PRESS;
} // </editor-fold>