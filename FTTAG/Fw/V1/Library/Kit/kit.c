#include "kit.h"
#include "libcomp.h"
#include "AppMain.h"

#ifndef BOOTLOADER_H
private uint8_t DoNext;
private tick_timer_t Tick;
#endif

#if(KIT_STARTUP_DELAY==0)
#error "Minimum value of KIT_STARTUP_DELAY must be 1"
#endif

#ifdef __WIN32
#ifndef KIT_WIN32_DEBUG_TIMEOUT
#define KIT_WIN32_DEBUG_TIMEOUT 20 // second
#endif
private int Win32TimeOut=0;
#endif

#if defined(USE_UART1_DEBUG) || defined(USE_UART2_DEBUG) || defined(USE_UART3_DEBUG) || defined(USE_HID_DEBUG)

private bool KIT_DEBUG_Streaming(const char c)
{
#if defined(USE_UART1_DEBUG)
    while(!UART2_IsTxReady());
    UART2_Write((uint8_t) c);
#endif

#if defined(USE_UART2_DEBUG)
    while(!UART2_IsTxReady());
    UART2_Write((uint8_t) c);
#endif

#if defined(USE_UART3_DEBUG)
    while(!UART3_IsTxReady());
    UART3_Write((uint8_t) c);
#endif

#if defined(USE_HID_DEBUG)
    while(!KIT_USB_Device_HID_Streaming(c));
#endif

    return 1;
}
#endif

public void KIT_Tasks(void) // <editor-fold defaultstate="collapsed" desc="KIT Tasks">
{
#ifndef BOOTLOADER_H
    // <editor-fold defaultstate="collapsed" desc="Application">
    Disable_Peripheral_Interrupt();
    Disable_Global_Interrupt();
    Tick_Timer_Init();
    TaskManager_Init();
    Tick_Timer_Reset(Tick);
    WDT_Enable();
    LibComp_Initialize();
#ifdef INDICATOR_H
    Indicator_Init();
#endif
#ifdef BUTTONAPI_H
    ButtonApi_Init();
#endif
#ifndef UNUSED_STARTUP_DELAY
    DoNext=0;
#else
#if defined(USE_UART1_DEBUG) || defined(USE_UART2_DEBUG) || defined(USE_UART3_DEBUG) || defined(USE_HID_DEBUG)
    Debug_SetStreamFnc(KIT_DEBUG_Streaming);
#endif

#ifdef KIT_USB_DEVICE_H
    KIT_USB_Device_Init();
#endif

#ifdef __WIN32
#ifdef KIT_RS232_WIN32_H
    if(RS232_PROC_SUCCESS!=KIT_RS232_Initialize(&Rs232Cxt))
    {
        KIT_RS232_Deinitialize();
        return;
    }
#endif
#endif
    APP_Main_Initialize();
#endif
    Enable_Peripheral_Interrupt();
    Enable_Global_Interrupt();

    while(1)
    {
#ifndef UNUSED_STARTUP_DELAY
        switch(DoNext)
        {
            case 0:
                if(Tick_Timer_Is_Over_Sec(Tick, 1))
                {
                    DoNext++;
#if defined(USE_UART1_DEBUG) || defined(USE_UART2_DEBUG) || defined(USE_UART3_DEBUG) || defined(USE_HID_DEBUG)
                    Debug_SetStreamFnc(KIT_DEBUG_Streaming);
#endif

#ifdef KIT_USB_DEVICE_H
                    KIT_USB_Device_Init();
#endif

#ifdef __WIN32
#ifdef KIT_RS232_WIN32_H
                    int rslt;

                    do
                        rslt=KIT_RS232_Initialize();
                    while(rslt==RS232_PROC_HANDLE);

                    if(RS232_PROC_ERROR==rslt)
                        goto __EXIT;
#endif
#endif
                }
                break;

            case 1:
                if(Tick_Timer_Is_Over_Sec(Tick, KIT_STARTUP_DELAY-1))
                {
                    DoNext++;
                    APP_Main_Initialize();
                }
                break;

            default:
                APP_Main_Tasks();

#ifdef __WIN32
#ifdef KIT_RS232_WIN32_H
                if(!KIT_RS232_IsDSREnabled(0))
                {
                    printf("\nDTR is not ready\n");
                    goto __EXIT;
                }
#else
                if(Tick_Timer_Is_Over_Ms(Tick, 1000))
                {
                    if(++Win32TimeOut>KIT_WIN32_DEBUG_TIMEOUT)
                        goto __EXIT;
                }
#endif
#endif
                break;
        }
#else
        APP_Main_Tasks();
#endif

        TaskManager();
    }

#ifdef __WIN32
__EXIT:
    TaskManager_End_AllTasks();

#ifdef KIT_RS232_WIN32_H
    KIT_RS232_Deinitialize();
#endif

    printf("\nExit %s\n", __func__);
#endif
    return;
    // </editor-fold>
#else
    // <editor-fold defaultstate="collapsed" desc="Bootloader">
    Disable_Peripheral_Interrupt();
    Disable_Global_Interrupt();
    Tick_Timer_Init();
    TaskManager_Init();
    WDT_Enable();
    LibComp_Initialize();
    APP_Main_Initialize();
    BootLoader_Initialize();
    Enable_Peripheral_Interrupt();
    Enable_Global_Interrupt();

    while(1)
    {
        APP_Main_Tasks();
        BootLoader_Tasks();
        TaskManager();
    }
    // </editor-fold>
#endif
} // </editor-fold>