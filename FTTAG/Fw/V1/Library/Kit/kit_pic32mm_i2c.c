#include "libcomp.h"
#include "kit_pic32mm_i2c.h"

typedef struct
{
    tick_timer_t Tick;
    uint8_t SlvAddr;
    uint8_t *pDi;
    uint8_t Li;
    uint8_t *pDo;
    uint8_t Lo;
    uint8_t DoNext;
    int8_t State;
} kit_i2c_cxt_t;

#ifdef USE_KIT_I2C2

#ifdef __db
#undef __db
#endif

#define __db(...)   //task_debug(__VA_ARGS__)

#ifdef __ndb
#undef __ndb
#endif

#define __ndb(...)  //nontask_debug(__VA_ARGS__)

private kit_i2c_cxt_t Kit_I2c2_Cxt={
    .State=KIT_I2C_ERR
};

public new_simple_task_t(KIT_I2C2_Tasks)
{
    static i2c_error_t rslt;

    // Write only: (open + set buffer) - (write) - (close) : 0-1-2
    // Read only : (open + set buffer) - (read) - (close) :  0-3-2
    // Write & read: (open + set buffer) - (write) - (close) - (open + set buffer) - (read) - (close):  0-1-2-0-3-2

    switch(Kit_I2c2_Cxt.DoNext)
    {
        case 0: // open bus and set buffer
            rslt=KIT_I2C2_MasterOpen(Kit_I2c2_Cxt.SlvAddr);

            if(rslt==I2C_NOERR)
            {
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);

                if(Kit_I2c2_Cxt.Li>0) // write only
                {
                    Kit_I2c2_Cxt.DoNext=1;
                    __db("\nOpen write");
                    KIT_I2C2_MasterSetBuffer(Kit_I2c2_Cxt.pDi, Kit_I2c2_Cxt.Li);
                    Kit_I2c2_Cxt.Li=0;
                }
                else // read only
                {
                    Kit_I2c2_Cxt.DoNext=3;
                    __db("\nOpen read");
                    KIT_I2C2_MasterSetBuffer(Kit_I2c2_Cxt.pDo, Kit_I2c2_Cxt.Lo);
                    Kit_I2c2_Cxt.Lo=0;
                }
            }
            else if(rslt==I2C_FAIL)
            {
                Kit_I2c2_Cxt.DoNext=2;
                Kit_I2c2_Cxt.Li=0;
                Kit_I2c2_Cxt.Lo=0;
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
                __db("\nOpen bus error");
            }
            break;

        case 1: // write operation
            rslt=KIT_I2C2_MasterOperation(0);

            if(rslt==I2C_NOERR)
            {
                __db("\nWrite I2C");
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
                Kit_I2c2_Cxt.DoNext=2;
            }
            else if(rslt==I2C_FAIL)
            {
                Kit_I2c2_Cxt.DoNext=2;
                Kit_I2c2_Cxt.Li=0;
                Kit_I2c2_Cxt.Lo=0;
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
                __db("\nWrite bus error");
            }
            break;

        case 2: // close bus
            rslt=KIT_I2C2_MasterClose();

            if(rslt==I2C_NOERR)
            {
                __db("\nClose I2C");
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);

                if(Kit_I2c2_Cxt.Lo==0)
                {
                    Kit_I2c2_Cxt.DoNext=254;
                    __db("\nLine %d", __LINE__);
                }
                else
                {
                    Kit_I2c2_Cxt.DoNext=0;
                    __db("\nLine %d", __LINE__);
                }
            }
            else if(rslt==I2C_FAIL)
            {
                Kit_I2c2_Cxt.DoNext=255;
                __db("\nClose bus error");
            }
            break;

        case 3: // read operation
            rslt=KIT_I2C2_MasterOperation(1);

            if(rslt==I2C_NOERR)
            {
                __db("\nRead I2C");
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
                Kit_I2c2_Cxt.DoNext=2;
            }
            else if(rslt==I2C_FAIL)
            {
                Kit_I2c2_Cxt.DoNext=2;
                Kit_I2c2_Cxt.Li=0;
                Kit_I2c2_Cxt.Lo=0;
                Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
                __db("\nRead bus error");
            }
            break;

        case 254:
            Kit_I2c2_Cxt.State=KIT_I2C_OK;
            __db("\nEnd task 254");
            TaskManager_End_Task(KIT_I2C2_Tasks);
            break;

        case 255:
        default:
            KIT_I2C2_HardwareDisale();
            Kit_I2c2_Cxt.State=KIT_I2C_ERR;
            __db("\nEnd task 255");
            TaskManager_End_Task(KIT_I2C2_Tasks);
            break;
    }

    if(Tick_Timer_Is_Over_Ms(Kit_I2c2_Cxt.Tick, 100))
    {
        if(Kit_I2c2_Cxt.DoNext==2)
        {
            Kit_I2c2_Cxt.DoNext=255;
            __db("\nLine %d", __LINE__);
        }
        else
        {
            Kit_I2c2_Cxt.DoNext=2;
            Kit_I2c2_Cxt.Li=0;
            Kit_I2c2_Cxt.Lo=0;
            __db("\nLine %d", __LINE__);
        }
    }

    Task_Done();
}

public int8_t KIT_I2C2_GetState(void)
{
    return Kit_I2c2_Cxt.State;
}

public void KIT_I2C2_Enable(void)
{
    Kit_I2c2_Cxt.DoNext=0;
    Kit_I2c2_Cxt.State=KIT_I2C_BUSY;
    Tick_Timer_Reset(Kit_I2c2_Cxt.Tick);
    TaskManager_Create_NewSimpleTask(KIT_I2C2_Tasks);
    __ndb("\nEnable I2C");
}

public void KIT_I2C2_Xfer(uint8_t SlvAddr, uint8_t *pDi, uint8_t Li, uint8_t *pDo, uint8_t Lo)
{
    Kit_I2c2_Cxt.SlvAddr=SlvAddr;
    Kit_I2c2_Cxt.pDi=pDi;
    Kit_I2c2_Cxt.pDo=pDo;
    Kit_I2c2_Cxt.Li=Li;
    Kit_I2c2_Cxt.Lo=Lo;
    __ndb("\nSet buffer");
}

public void KIT_I2C2_Wait(void)
{
    TaskManager();
}

#undef __db
#undef __ndb
#endif
