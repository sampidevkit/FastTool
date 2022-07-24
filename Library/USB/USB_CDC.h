#ifndef USB_CDC_H
#define USB_CDC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void USB_CDC_Tasks(void);
bool USB_CDC_Is_RxReady(void);
bool USB_CDC_Is_TxReady(void);
bool USB_CDC_Is_TxDone(void);
void USB_CDC_Write(uint8_t c);
uint8_t USB_CDC_Read(void);

#define __db(...)       printf(__VA_ARGS__)

#endif