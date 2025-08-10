#include "AppMain.h"

static void SYS_Info(void) // <editor-fold defaultstate="collapsed" desc="System info">
{
    __dbs("\r\nPIC KIT3 AVR MODE");
    __dbss("\r\nFW: ", __DATE__);
    __dbss(" - ", __TIME__);
    __dbsu("\r\nClock: ", _XTAL_FREQ);
    __dbsh("Hz\r\nReset code: ", RCON);

    if(RCONbits.TRAPR)
        __dbs("\r\n-->TRAPR: A Trap Conflict Reset has occurred");

    if(RCONbits.IOPUWR)
        __dbs("\r\n-->IOPUWR: An illegal opcode/address or uninitialized W register used as an Address Pointer");

    if(RCONbits.CM)
        __dbs("\r\n-->CM: A Configuration Word Mismatch Reset has occurred");

    if(RCONbits.PMSLP)
        __dbs("\r\n-->PMSLP: Program memory bias voltage remains powered during Sleep");

    if(RCONbits.EXTR)
        __dbs("\r\n-->EXTR:  Master Clear (pin) Reset has occurred");

    if(RCONbits.SWR)
        __dbs("\r\n-->SWR: Software Reset was executed");

    if(RCONbits.WDTO)
        __dbs("\r\n-->WDTO: Watchdog Timer Time-out Flag bit");

    if(RCONbits.SLEEP)
        __dbs("\r\n-->SLEEP: Device was in Sleep mode");

    if(RCONbits.IDLE)
        __dbs("\r\n-->IDLE: Device was in Idle mode");

    if(RCONbits.BOR)
        __dbs("\r\n-->BOR: Brown-out Reset has occurred");

    if(RCONbits.POR)
        __dbs("\r\n-->POR: Power-on Reset has occurred");

    RCON&=0x0020; // Clear all bits, exclude bit 5: SWDTEN
} // </editor-fold>

void SYS_Wait(void) // <editor-fold defaultstate="collapsed" desc="System waiting task">
{
    ClrWdt();
    TaskManager();
} // </editor-fold>

int main(void) // <editor-fold defaultstate="collapsed" desc="Main">
{
    uint32_t usbID[2];

    SYSTEM_Initialize();
    Enable_Global_Interrupt();

    Tick_Timer_Init();
    TaskManager_Init();
    Tick_Timer_SetFncCallInDelay(SYS_Wait);
    USB_Device_LoadUDID(usbID);
    USBDeviceInit();
    USBDeviceAttach();
    VCP_Init();
    BUTTON_Init(ModeBtCxt, NULL, NULL, NULL);
    Indicator_Init();
    Indicator_Toggle(0, 500, 500);
    __delay_ms(5000);
    SYS_Info();
    __dbs("\r\nUSB ID: ");
    __dbh8(usbID[0]);
    __dbh8(usbID[1]);
    __dbs("\r\nSystem init done\r\n");
    AppMain_Init();

    while(1)
    {
        SYS_Wait();
        AppMain_Tasks();
    }

    return 1;
} // </editor-fold>
