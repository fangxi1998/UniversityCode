#include "OSAL_MyfirstAppCoord.h"
// The order in this table must be identical to the task initialization calls below in osalInitTask.
const pTaskEventHandlerFn tasksArr[] = {
  macEventLoop,
  nwk_event_loop,
  Hal_ProcessEvent,//Ó²¼þ³éÏó²ã

  APS_event_loop,

  ZDApp_event_loop,

  My_Task_Process_Event 
}; 
//***sizeof(tasksArr[0]) = sizeof(pTaskEventHandlerFn)***********
const uint8 tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );
uint16 *tasksEvents = NULL;

/*********************************************************************
 * @fn      osalInitTasks
 *
 * @brief   This function invokes the initialization function for each task.
 *
 * @param   void
 *
 * @return  none
 ****************************************************************/

void osalInitTasks( void )
{
  uint8 taskID = 0;

  tasksEvents = (uint16 *)osal_mem_alloc( sizeof( uint16 ) * tasksCnt);
  osal_memset( tasksEvents, 0, (sizeof( uint16 ) * tasksCnt));

  macTaskInit( taskID++ );
  nwk_init( taskID++ );
  Hal_Init( taskID++ );

  APS_Init( taskID++ );

  ZDApp_Init( taskID++ );

  My_Task_Init( taskID );
}

/*********************************************************************
*********************************************************************/
