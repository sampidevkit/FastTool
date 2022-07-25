#ifndef USB_CDC_DEBUG_H
#define USB_CDC_DEBUG_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void USB_CDC_Debug_Tasks(void);
bool USB_CDC_Debug_Is_RxReady(void);
bool USB_CDC_Debug_Is_TxReady(void);
bool USB_CDC_Debug_Is_TxDone(void);
void USB_CDC_Debug_Write(uint8_t c);
uint8_t USB_CDC_Debug_Read(void);

#define __db(...) printf(__VA_ARGS__)

#endif