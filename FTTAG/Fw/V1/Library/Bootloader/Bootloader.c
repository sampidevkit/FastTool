#include "libcomp.h"
#include "Bootloader.h"
#include "BLD_Target_Device.h"

enum
{
    BLD_TRIGGER=0,
    BLD_COMM_INIT=1,
    BLD_INFO=2,
    BLD_COMM_READ=3,
    BLD_DATA_PROCESS=4,
    BLD_RSLT_SUCCESS=5,
    BLD_RSLT_ERROR=6,
    BLD_COMM_WRITE=7,
    BLD_WAIT,
    BLD_DONE
};

#ifndef __PROJECT_NAME__
#define __PROJECT_NAME__ "SAMPI BOOTLOADER"
#endif

#ifndef __HARDWARE_ID__
#define __HARDWARE_ID__ "SAMM-0000"
#endif

#ifndef __WEBSITE__
#define __WEBSITE__ "https://github.com/sampidevkit/"
#endif

#ifndef BOOTLOADER_DISABLE_INFO
private const uint8_t BldInfo[]={
    "\n" __PROJECT_NAME__ "\n"
    "HwID: " __HARDWARE_ID__ "\n"
    "MCU: " __BLD_NVM_TARGET_DEVICE_NAME__ "\n"
    "Rel: " __DATE__ "-" __TIME__
    "\n" __WEBSITE__ "\n"
};
#endif

private uint8_t DoNext;

#ifndef BLD_FILEIO_H
private uint8_t *pBuffer;
private uint8_t i, BufferLen;
private uint8_t Buffer[BLD_BUFFER_SIZE];
#endif

#if defined(__XC32)
// <editor-fold defaultstate="collapsed" desc="PIC32MM Bootloader">
extern void appFunction(void);

#ifdef USE_BOOTLOADER_BUILTIN_EXCEPTION

void _general_exception_handler(void) // <editor-fold defaultstate="collapsed" desc="Exception handler">
{
    while(1); // Do nothing
} // </editor-fold>
#endif

private void Jump2App(void) // <editor-fold defaultstate="collapsed" desc="Jump to application">
{
    uint32_t *AppPtr;

    AppPtr=(uint32_t *) APP_RESET_ADDRESS;

    if(*AppPtr!=0xFFFFFFFF)
    {
#ifndef BLD_DISABLE_CODE_PROTECT
        if(FSECbits.CP==0) // Code protection bit must be enabled
#endif
            appFunction();
    }
} // </editor-fold>

private bool Check_Exit_Trigger(void) // <editor-fold defaultstate="collapsed" desc="Check exit-trigger state">
{
    private bool prv=1;
    private tick_timer_t tk={1, 0, 0};

    if(prv!=BLD_Trigger_GetState())
    {
        if(prv==1)
        {
            if(Tick_Timer_Is_Over_Ms(tk, 500)) // check in 500ms
            {
                prv=0;
                return 1;
            }
        }
        else
            prv=1;
    }
    else if(tk.Timeout==0)
        tk.Timeout=1;

    return 0;
} // </editor-fold>

#ifndef BLD_FILEIO_H

private new_simple_task_t(BootLoader_DummyTasks)
{
    Task_Done();
}
#endif

public void BootLoader_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Boot loader task">
{
    switch(DoNext)
    {
        case BLD_TRIGGER: // Check boot load trigger and App-zone
            if(BLD_Trigger_GetState())
                Jump2App(); // Jump out this function if no application

            DoNext=BLD_COMM_INIT;
            break;

        case BLD_COMM_INIT: // Communication initialize
            BLD_Comm_Init();

#ifndef BLD_FILEIO_H
            DoNext=BLD_INFO;
            pBuffer=(uint8_t *) BldInfo;

        case BLD_INFO:
            while(*pBuffer!=0x00)
            {
                if(BLD_IsTxReady())
                    BLD_Write(*pBuffer++);
                else
                    return;
            }

            BufferLen=0;
            DoNext=BLD_WAIT;
            break;

        default:
        case BLD_COMM_READ:
            if(BLD_Trigger_GetState()==0)
                BLD_SystemReboot();

            while(BLD_IsRxReady())
            {
                Buffer[BufferLen]=BLD_Read();

                if(Buffer[BufferLen]=='\n')
                {
                    if(BufferLen<BLD_BUFFER_SIZE)
                        DoNext=BLD_DATA_PROCESS;
                    else
                        DoNext=BLD_RSLT_ERROR;
                }
                else if(BufferLen<BLD_BUFFER_SIZE)
                    BufferLen++;
            }
            break;

        case BLD_DATA_PROCESS: // Process data
            for(i=0; i<BufferLen; i++)
            {
                int8_t rslt;

                rslt=HEXPARSE_Tasks(Buffer[i]);

                if(rslt==PROC_DONE)
                {
                    DoNext=BLD_RSLT_SUCCESS;
                    break;
                }
                else if(rslt==PROC_ERR)
                {
                    DoNext=BLD_RSLT_ERROR;
                    break;
                }
            }

            DoNext=BLD_RSLT_SUCCESS;
            break;

        case BLD_RSLT_SUCCESS: // Success
            Buffer[0]='A';
            Buffer[1]=0;
            BufferLen=0;
            DoNext=BLD_COMM_WRITE;
            break;

        case BLD_RSLT_ERROR: // Error
            Buffer[0]='N';
            Buffer[1]=0;
            BufferLen=0;
            DoNext=BLD_COMM_WRITE;
            break;

        case BLD_COMM_WRITE: // Send response
            while(Buffer[BufferLen]!=0x00)
            {
                if(BLD_IsTxReady())
                    BLD_Write(Buffer[BufferLen++]);
                else
                    return;
            }

            BufferLen=0;
            DoNext=BLD_COMM_READ;
#else
            DoNext=BLD_WAIT;
#endif
            break;

        case BLD_WAIT:
            if(BLD_Trigger_GetState())
#ifndef BLD_FILEIO_H
                DoNext=BLD_COMM_READ;
            break;
#else
                DoNext=BLD_DONE;
            break;
            
        default: // BLD_DONE
            if(Check_Exit_Trigger())
                BLD_SystemReboot();
            break;
#endif
    }
} // </editor-fold>

public void BootLoader_Initialize(void) // <editor-fold defaultstate="collapsed" desc="Boot loader initialize">
{
    DoNext=BLD_TRIGGER;
    BLD_Trigger_Init();

#ifndef BLD_FILEIO_H
    TaskManager_Create_NewSimpleTask(BootLoader_DummyTasks);
#endif

    Enable_Peripheral_Interrupt();
    Enable_Global_Interrupt();
} // </editor-fold>

public void BootLoader_Deinitialize(void) // <editor-fold defaultstate="collapsed" desc="Bootloader deinitialize">
{
    ClrWdt();
    WDT_Disable();
} // </editor-fold>
// </editor-fold>
#else
// <editor-fold defaultstate="collapsed" desc="PIC18F Bootloader">
// To be device independent, these are set by mcc in memory.h
#define LAST_WORD_MASK  (WRITE_FLASH_BLOCKSIZE - 1)
#define _str(x)         #x
#define str(x)          _str(x)

private uint8_t ToDo;

/* ****************************************************************************
 The bootloader code does not use any interrupts. 
 However, the application code may use interrupts.
 The interrupt vector on a PIC18F is located at address 0x0008 (High) 
 and 0x0018 (Low). 
 The following function will be located  at the interrupt vector and will 
 contain a jump to the new application interrupt vectors.
 ***************************************************************************** */
asm("psect  intcode,global,reloc=2,class=CODE,delta=1");
asm("GOTO " str(APP_INT_VECTOR_HIGH_ADDRESS));
asm("psect  intcodelo,global,reloc=2,class=CODE,delta=1");
asm("GOTO " str(APP_INT_VECTOR_LOW_ADDRESS));

private void Jump2App(void) // <editor-fold defaultstate="collapsed" desc="Jump to application">
{
    // Check the reset vector for code to initiate bootloader. This section reads
    // the application start vector to see if the location is blank (0xFF) or not.
    // If blank, it runs the bootloader. Otherwise, it assumes the application 
    // is loaded and instead runs the application.

    if(0xFF!=BLD_Nvm_ReadByte(APP_RESET_ADDRESS))
    {
        STKPTR=0x00;
        BSR=0x00;
        asm("goto  " str(APP_RESET_ADDRESS));
    }
} // </editor-fold>

public void BootLoader_Tasks(void) // <editor-fold defaultstate="collapsed" desc="Boot loader task">
{
    switch(DoNext)
    {
        case BLD_TRIGGER: // Check boot load trigger and Appzone
            if((BLD_Trigger_GetState()==0))
                DoNext=BLD_COMM_INIT;
            else
            {
                Jump2App(); // Jump out this function if no application
                DoNext=BLD_COMM_INIT;
            }
            break;

        case BLD_COMM_INIT: // Communication initialize
            BLD_Comm_Init();

#ifndef BOOTLOADER_DISABLE_INFO
            DoNext=BLD_INFO;

            pBuffer=(uint8_t *) BldInfo;
        case BLD_INFO: // Put device info
            while(*pBuffer!=0x00)
            {
                if(BLD_IsTxReady())
                    BLD_Write(*pBuffer++);
                else
                    return;

                while(!BLD_IsTxDone());
            }
#endif

            BufferLen=0;
            DoNext=BLD_COMM_READ;

        case BLD_COMM_READ: // Read data from UART buffer
            while(BLD_IsRxReady())
            {
                Buffer[BufferLen]=BLD_Read();

                if(Buffer[BufferLen]=='\n')
                {
                    if(BufferLen<BLD_BUFFER_SIZE) // process data
                        DoNext=BLD_DATA_PROCESS;
                    else // response error
                        DoNext=BLD_RSLT_ERROR;
                }
                else if(BufferLen<BLD_BUFFER_SIZE)
                    BufferLen++;
            }
            break;

        case BLD_DATA_PROCESS: // Process data
            for(i=0; i<BufferLen; i++)
            {
                int8_t rslt;

                rslt=HEXPARSE_Tasks((int8_t) Buffer[i]);

                if(rslt==PROC_DONE)
                {
                    DoNext=BLD_RSLT_SUCCESS;
                    break;
                }
                else if(rslt==PROC_ERR)
                {
                    DoNext=BLD_RSLT_ERROR;
                    break;
                }
            }

            DoNext=BLD_RSLT_SUCCESS;
            break;

        case BLD_RSLT_SUCCESS: // Success
            Buffer[0]='A';
            Buffer[1]=0;
            BufferLen=0;
            DoNext=BLD_COMM_WRITE;
            break;

        case BLD_RSLT_ERROR: // Error
            Buffer[0]='K';
            Buffer[1]=0;
            BufferLen=0;
            DoNext=BLD_COMM_WRITE;
            break;

        case BLD_COMM_WRITE:
            while(Buffer[BufferLen]!=0x00)
            {
                if(BLD_IsTxReady())
                    BLD_Write(Buffer[BufferLen++]);
                else
                    return;

                while(!BLD_IsTxDone());
            }

            BufferLen=0;
            DoNext=ToDo;
            break;

        case BLD_DONE:
        default:
            Reset();
            break;
    }
} // </editor-fold>

public void BootLoader_Initialize(void) // <editor-fold defaultstate="collapsed" desc="Boot loader initialize">
{
    ToDo=BLD_COMM_READ;
    DoNext=BLD_TRIGGER;
    BLD_Trigger_Init();
} // </editor-fold>

public void BootLoader_Deinitialize(void) // <editor-fold defaultstate="collapsed" desc="Bootloader deinitialize">
{
    ToDo=BLD_DONE;
} // </editor-fold>
// </editor-fold>
#endif