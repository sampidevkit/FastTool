#include "Button.h"
#include "libcomp.h"

bt_stt_t BUTTON_GetState(void) // <editor-fold defaultstate="collapsed" desc="Button UP">
{
    static bool prv=1;
    static tick_t tk={1, 0, 0};

    if(prv!=BT_N_GetValue())
    {
        if(prv==1)
        {
            if(Tick_Is_Over_Ms(&tk, 3000)) // check in 3s
            {
                prv=0;
                return 1;
            }
        }
        else
            prv=1;
    }
    else if(tk.Over==0)
        tk.Over=1;

    return 0;
} // </editor-fold>