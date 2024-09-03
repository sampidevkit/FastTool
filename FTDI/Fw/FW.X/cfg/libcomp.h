#ifndef LIBCOMP_H
#define LIBCOMP_H

#include "system/system.h"
#include "Common/Button.h"
#include "Common/debug.h"
#include "Common/Util.h"
#include "Drivers/AP33772.h"
#include "Tasks/TaskManager.h"
#include "Timer/SystemTick.h"
#include "Timer/Wdt.h"

#include <util/delay.h>

#define INTERRUPT_GlobalEnable()    ENABLE_INTERRUPTS()
#define INTERRUPT_GlobalDisable()   DISABLE_INTERRUPTS()
#define Reset_AVR()                 do{wdt_enable(WDTO_30MS); while(1);}while(0)

#define ADC_VREF                    5000 // mV
#define ADC_RES                     4096 // 12-bit

#define DAC_VREF                    5000 // mV
#define DAC_RES                     1024 // 10-bit

typedef enum {
    CH_VIO_SEN = ADC_MUXPOS_AIN22_gc,
    CH_VDD = ADC_MUXPOS_VDDDIV10_gc,
    CH_VDDIO = ADC_MUXPOS_VDDIO2DIV10_gc,
    CH_VIO_OUT = ADC_MUXPOS_DAC0_gc
} adc_channel_t;

typedef enum {
    LED_OFF = 0,
    RED_ON,
    RED_BLINK,
    BLUE_ON,
    BLUE_BLINK,
    MAGENTA_ON,
    MAGENTA_BLINK
} led_state_t;

typedef enum {
    VLOGIC_1800 = 0,
    VLOGIC_3300,
    VLOGIC_5000,
    VLOGIC_VIO_SEN,
    VLOGIC_OFF
} vlogic_t;

typedef enum {
    VBUS_5000 = 0,
    VBUS_9000,
    VBUS_12000,
    VBUS_OFF
} vbus_t;

typedef union {
    uint8_t val;

    struct {
        unsigned red : 2;
        unsigned blue : 2;
        unsigned rfu : 4;
    };
} led_t;

typedef struct {
    led_state_t state;
    tick_timer_t tk;
} led_cxt_t;

typedef struct {
    int tr25;
    int tr50;
    int tr75;
    int tr100;
    uint8_t templim;
    vbus_t vbus;
    vlogic_t vlogic;
    uint8_t cks;
} cfg_cxt_t;

void LED_Tasks(void *);
void GetVolTask(void *);

#endif