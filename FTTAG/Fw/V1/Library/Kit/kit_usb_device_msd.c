#include "libcomp.h"
#include "kit_usb_device_msd.h"

//The LUN variable definition is critical to the MSD function driver.  This
//  array is a structure of function pointers that are the functions that
//  will take care of each of the physical media.  For each additional LUN
//  that is added to the system, an entry into this array needs to be added
//  so that the stack can know where to find the physical layer functions.
//  In this example the media initialization function is named
//  "MediaInitialize", the read capacity function is named "ReadCapacity",
//  etc.
LUN_FUNCTIONS LUN[MAX_LUN+1]={
    {
        (FILEIO_MEDIA_INFORMATION*(*)(void *))&MEDIA_Initialize,
        (uint32_t(*)(void *))&MEDIA_ReadCapacity,
        (uint16_t(*)(void *))&MEDIA_ReadSectorSize,
        (bool(*)(void *))&MEDIA_Detect,
        (uint8_t(*)(void *, uint32_t, uint8_t*, uint8_t))&MEDIA_SectorRead,
        (uint8_t(*)(void *))&MEDIA_WriteProtectState,
        (uint8_t(*)(void *, uint32_t, uint8_t*, uint8_t))&MEDIA_SectorWrite,
        (void *) MEDIA_Parameters
    }
};

/* Standard Response to INQUIRY command stored in ROM 	*/
const InquiryResponse inq_resp={
    0x00, // peripheral device is connected, direct access block device
    0x80, // removable
    0x04, // version = 00=> does not conform to any standard, 4=> SPC-2
    0x02, // response is in format specified by SPC-2
    0x20, // n-4 = 36-4=32= 0x20
    0x00, // sccs etc.
    0x00, // bque=1 and cmdque=0,indicates simple queueing 00 is obsolete,
    // but as in case of other device, we are just using 00
    0x00, // 00 obsolete, 0x80 for basic task queueing
    T10_ASSIGNED_VENDOR_ID, // this is the T10 assigned Vendor ID
    'M', 'a', 's', 's', ' ', 'S', 't', 'o', 'r', 'a', 'g', 'e', ' ', ' ', ' ', ' ',
    '0', '0', '0', '1'
};

private bool Init=0;

public new_simple_task_t(KIT_USB_Device_MSD_Tasks) // <editor-fold defaultstate="collapsed" desc="App USB device MSD tasks">
{
    MSDTasks();
    Task_Done();
} // </editor-fold>

public void KIT_USB_Device_MSD_EventInit(void) // <editor-fold defaultstate="collapsed" desc="USB device MSD event initialize">
{
#if (MSD_DATA_IN_EP == MSD_DATA_OUT_EP)
    USBEnableEndpoint(MSD_DATA_IN_EP, USB_IN_ENABLED|USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
#else
    USBEnableEndpoint(MSD_DATA_IN_EP, USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    USBEnableEndpoint(MSD_DATA_OUT_EP, USB_OUT_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
#endif

    USBMSDInit();
} // </editor-fold>

public void KIT_USB_Device_MSD_Init(void) // <editor-fold defaultstate="collapsed" desc="App USB device MSD initialize">
{
    if(Init==0)
    {
        Init=1;
        TaskManager_Create_NewSimpleTask(KIT_USB_Device_MSD_Tasks);
    }
} // </editor-fold>

public void KIT_USB_Device_MSD_Deinit(void) // <editor-fold defaultstate="collapsed" desc="App USB device MSD deinitialize">
{
    if(Init==1)
    {
        Init=0;
        TaskManager_End_Task(KIT_USB_Device_MSD_Tasks);
    }
} // </editor-fold>
