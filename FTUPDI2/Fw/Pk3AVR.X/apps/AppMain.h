#ifndef APPMAIN_H
#define	APPMAIN_H

#include <stdio.h>

#include "VCP.h"
#include "system.h"
#include "buttons/Buttons.h"
#include "common/Debug.h"
#include "system/TickTimer.h"
#include "system/TaskManager.h"
#include "indicator/Indicator.h"

void AppMain_Init(void);
void AppMain_Tasks(void);

#endif
