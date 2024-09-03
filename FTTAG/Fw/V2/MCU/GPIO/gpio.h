#ifndef GPIO_H
#define GPIO_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/* ******************************************************************* PORT A */
#define PIN_A0          0x00
#define PIN_OC1         PIN_A0
#define PIN_AI1         PIN_A0

#define PIN_A1          0x01
#define PIN_OC0         PIN_A1
#define PIN_AI0         PIN_A1

#define PIN_A2          0x02
#define PIN_FLASH_CS_N  PIN_A2

#define PIN_A3          0x03
#define PIN_OC2         PIN_A3
#define PIN_AI2         PIN_A3

#define PIN_A4          0x04
#define PIN_SDO         PIN_A4

#define PIN_A9          0x09
#define PIN_SCK         PIN_A9

/* ******************************************************************* PORT B */
#define PIN_B0          0x10
#define PIN_PGD         PIN_B0

#define PIN_B1          0x11
#define PIN_PGC         PIN_B1

#define PIN_B2          0x12
#define PIN_SDA         PIN_B2

#define PIN_B3          0x13
#define PIN_SCL         PIN_B3

#define PIN_B4          0x14
#define PIN_SDI         PIN_B4

#define PIN_B5          0x15
#define PIN_RLED        PIN_B5

#define PIN_B6          0x16
#define PIN_VBUS        PIN_B6

#define PIN_B7          0x17
#define PIN_GLED        PIN_B7

#define PIN_B8          0x18
#define PIN_QWIIC_SCL   PIN_B8

#define PIN_B9          0x19
#define PIN_QWIIC_SDA   PIN_B9

#define PIN_B10         0x1A
#define PIN_USB_DM      PIN_B10

#define PIN_B11         0x1B
#define PIN_USB_DP      PIN_B11

#define PIN_B13         0x1D
#define PIN_TX          PIN_B13
#define PIN_AI3         PIN_B13

#define PIN_B14         0x1E
#define PIN_VOADJ       PIN_B14

#define PIN_B15         0x1F
#define PIN_RX          PIN_B15
#define PIN_AI4         PIN_B15

/* ******************************************************************* PORT C */
#define PIN_C0          0x20
#define PIN_BT_CLR      PIN_C0

#define PIN_C1          0x21
#define PIN_INT_N       PIN_C1

#define PIN_C2          0x22
#define PIN_DBG_TX      PIN_C2

#define PIN_C3          0x23
#define PIN_BT_MOD      PIN_C3

#define PIN_C8          0x28
#define PIN_PD_INT_N    PIN_C8

#define PIN_C9          0x29
#define PIN_BLED        PIN_C9

/* **************************************************************** GPIO MODE */
#define DIGITAL_OUTPUT  0b00000000
#define DIGITAL_INPUT   0b00000001
#define ANALOG_OUTPUT   0b00000010
#define ANALOG_INPUT    0b00000011
// Alternative mode (via |)
#define OPEN_DRAIN      0b00000100
#define PULL_UP         0b00001000
#define PULL_DOWN       0b00010000

/* *************************************************************** GPIO STATE */
#define OUTPUT_LOW      0b0
#define OUTPUT_HIGH     0b1

extern volatile uint32_t *gpio_sfr;

#define gpio_get_sfr(base_reg, pin) do{gpio_sfr=&base_reg; gpio_sfr+=((pin&0xF0)<<2);}while(0)
#define gpio_clr_reg(base_reg, pin) do{gpio_sfr=&base_reg; gpio_sfr+=(((pin&0xF0)<<2)+4); *gpio_sfr=(1<<(pin&0x0F));}while(0)
#define gpio_set_reg(base_reg, pin) do{gpio_sfr=&base_reg; gpio_sfr+=(((pin&0xF0)<<2)+8); *gpio_sfr=(1<<(pin&0x0F));}while(0)
#define gpio_inv_reg(base_reg, pin) do{gpio_sfr=&base_reg; gpio_sfr+=(((pin&0xF0)<<2)+12); *gpio_sfr=(1<<(pin&0x0F));}while(0)

#define get_tris(pin)               gpio_get_sfr(TRISA, pin)
#define get_port(pin)               gpio_get_sfr(PORTA, pin)
#define get_lat(pin)                gpio_get_sfr(LATA, pin)
#define get_ansel(pin)              gpio_get_sfr(ANSELA, pin)
#define get_cnpu(pin)               gpio_get_sfr(CNPUA, pin)
#define get_cnpd(pin)               gpio_get_sfr(CNPDA, pin)
#define get_odc(pin)                gpio_get_sfr(ODCA, pin)

#define clr_tris(pin)               gpio_clr_reg(TRISA, pin)
#define clr_port(pin)               gpio_clr_reg(PORTA, pin)
#define clr_lat(pin)                gpio_clr_reg(LATA, pin)
#define clr_ansel(pin)              gpio_clr_reg(ANSELA, pin)
#define clr_cnpu(pin)               gpio_clr_reg(CNPUA, pin)
#define clr_cnpd(pin)               gpio_clr_reg(CNPDA, pin)
#define clr_odc(pin)                gpio_clr_reg(ODCA, pin)

#define set_tris(pin)               gpio_set_reg(TRISA, pin)
#define set_port(pin)               gpio_set_reg(PORTA, pin)
#define set_lat(pin)                gpio_set_reg(LATA, pin)
#define set_ansel(pin)              gpio_set_reg(ANSELA, pin)
#define set_cnpu(pin)               gpio_set_reg(CNPUA, pin)
#define set_cnpd(pin)               gpio_set_reg(CNPDA, pin)
#define set_odc(pin)                gpio_set_reg(ODCA, pin)

#define inv_tris(pin)               gpio_inv_reg(TRISA, pin)
#define inv_port(pin)               gpio_inv_reg(PORTA, pin)
#define inv_lat(pin)                gpio_inv_reg(LATA, pin)
#define inv_ansel(pin)              gpio_inv_reg(ANSELA, pin)
#define inv_cnpu(pin)               gpio_inv_reg(CNPUA, pin)
#define inv_cnpd(pin)               gpio_inv_reg(CNPDA, pin)
#define inv_odc(pin)                gpio_inv_reg(ODCA, pin)

/* gpio_set_mode(pin, mode, state)
 * pin: PIN_x
 * mode: DIGITAL_OUTPUT, DIGITAL_INPUT, ANALOG_OUTPUT, ANALOG_INPUT
 * alternative mode (via |): OPEN_DRAIN, PULL_UP, PULL_DOWN
 * state: OUTPUT_LOW, OUTPUT_HIGH
 */
void gpio_set_mode(uint8_t pin, uint8_t mode, bool prestate);


uint8_t gpio_get_mode(uint8_t pin);
void gpio_set_state(uint8_t pin, bool state);
bool gpio_get_state(uint8_t pin);

#define gpio_output_high(pin)       gpio_set_state(pin, true)
#define gpio_output_low(pin)        gpio_set_state(pin, false)

#endif