#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    NOT_PRESS = 0,
    SINGLE_PRESS,
    NEXT_PRESS,
    DOUBLE_PRESS,
    HOLD_PRESS,
    WAIT_RELEASE
} bt_stt_t;

typedef struct {
    bt_stt_t DoNext;
    uint32_t Begin;
    void (*SinglePressCallback)(void);
    void (*DoublePressCallback)(void);
    void (*HoldPressCallback)(void);
} bt_cxt_t;

extern bt_cxt_t ModeBtCxt;

#define BUTTON_Init(pBtCxt, pCbSF, pCbDF, pCbHF) do{pBtCxt.DoNext=NOT_PRESS; \
        pBtCxt.SinglePressCallback=pCbSF; pBtCxt.DoublePressCallback=pCbDF;  \
        pBtCxt.HoldPressCallback=pCbHF;}while(0)

bt_stt_t BUTTON_GetState(bt_cxt_t *pBtCxt, bool preInput);

#define MOD_Button_GetState()                   BUTTON_GetState(&ModeBtCxt, BT_N_GetValue())
#define MOD_Button_SetSinglePress_Event(pCbSF)  ModeBtCxt.SinglePressCallback=pCbSF
#define MOD_Button_SetDoublePress_Event(pCbDF)  ModeBtCxt.DoublePressCallback=pCbDF
#define MOD_Button_SetHoldPress_Event(pCbHF)    ModeBtCxt.HoldPressCallback=pCbHF

#endif