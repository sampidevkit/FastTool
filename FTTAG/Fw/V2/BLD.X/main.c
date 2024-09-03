#include "GPIO/gpio.h"

int main(void)
{
    gpio_set_mode(PIN_A0, 0, 0);
    
    while(1)
    {

    }

    return 1;
}