#include "gpio.h"

volatile uint32_t *gpio_sfr;

void gpio_set_mode(uint8_t pin, uint8_t mode, bool prestate) // <editor-fold defaultstate="collapsed" desc="Set GPIO mode">
{
    // pre-state
    if(prestate==true)
        set_lat(pin);
    else
        clr_lat(pin);
    // direction
    if((mode&0b00001)==0b00001)
        set_tris(pin);
    else
        clr_tris(pin);
    // analog
    if((mode&0b00010)==0b00010)
        set_ansel(pin);
    else
        clr_ansel(pin);
    // open-drain
    if((mode&0b00100)==0b00100)
        set_odc(pin);
    else
        clr_odc(pin);
    // pull-up
    if((mode&0b01000)==0b01000)
        set_cnpu(pin);
    else
        clr_cnpu(pin);
    // pull-down
    if((mode&0b10000)==0b10000)
        set_cnpd(pin);
    else
        clr_cnpd(pin);
} // </editor-fold>

uint8_t gpio_get_mode(uint8_t pin) // <editor-fold defaultstate="collapsed" desc="Get GPIO mode">
{
    uint8_t mode=0b00000;
    // get direction
    get_tris(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        mode=0b00001;
    // get analog
    get_ansel(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        mode|=0b00010;
    // get open-drain
    get_odc(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        mode|=0b00100;
    // get pull-up
    get_cnpu(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        mode|=0b01000;
    // get pull-down
    get_cnpd(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        mode|=0b10000;

    return mode;
} // </editor-fold>

void gpio_set_state(uint8_t pin, bool state) // <editor-fold defaultstate="collapsed" desc="Set GPIO state">
{
    if(state==true)
        set_lat(pin);
    else
        clr_lat(pin);
} // </editor-fold>

bool gpio_get_state(uint8_t pin) // <editor-fold defaultstate="collapsed" desc="Get GPIO state">
{
    get_port(pin);

    if((*gpio_sfr)&(1<<(pin&0x0F)))
        return true;

    return false;
} // </editor-fold>