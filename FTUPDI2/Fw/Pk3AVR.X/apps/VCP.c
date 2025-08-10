#include "VCP.h"
#include "VCP_Debug.h"

#ifdef USE_VCP_ATC
#include "VCP_ATC.h"
#endif

void VCP_Init(void) // <editor-fold defaultstate="collapsed" desc="USB CDC initialize">
{
    uint8_t i=0;

    if((USBGetDeviceState()>=CONFIGURED_STATE)&&(USBIsDeviceSuspended()==false))
    {
        __delay_ms(3000);
    }

    VCP_Debug_Init(i++);

#ifdef USE_VCP_ATC
    VCP_ATC_Init(i++);
#endif

} // </editor-fold>
