
#ifndef _OSAL_MYFIRSTAPPCOORD_H_
#define _OSAL_MYFIRSTAPPCOORD_H_

#include "ZComDef.h"
#include "OSAL_Tasks.h"
#include "mac_api.h"
#include "nwk.h"
#include "hal_drivers.h"
#include "aps.h"
#include "ZDApp.h"

void     My_Task_Init(byte task_id );
UINT16   My_Task_Process_Event( byte task_id, UINT16 events );

#endif
