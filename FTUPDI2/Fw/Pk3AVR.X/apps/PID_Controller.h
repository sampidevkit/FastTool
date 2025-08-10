#ifndef PID_CONTROLLER_H
#define	PID_CONTROLLER_H

#include "common/LibDef.h"

void PID_Init(uint16_t setPoint);
uint16_t PID_GetSetpoint(void);
uint16_t PID_Task(int32_t Realpoint);

#endif
