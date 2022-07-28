#ifndef BUTTON_H
#define BUTTON_H

typedef enum {
    NOT_PRESS = 0,
    SINGLE_PRESS,
    DOUBLE_PRESS,
    HOLD_PRESS
} bt_stt_t;

bt_stt_t BUTTON_GetState(void);

#endif