#include "Button.h"
#include "libcomp.h"

bool BUTTON_Is_Pressed(void) // <editor-fold defaultstate="collapsed" desc="Button UP">
{
    static bool prv=1;
    static tick_t tk={1, 0, 0};

    if(prv!=BT_N_GetValue())
    {
        if(prv==1)
        {
            if(Tick_Is_Over(&tk, 100)) // check in 100ms
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