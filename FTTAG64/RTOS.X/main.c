#include "libcomp.h"
#include "Application.h"

void vApplicationMallocFailedHook(void)
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
    to query the size of free heap space that remains (although it does not
    provide information on how the remaining heap might be fragmented). */
    taskDISABLE_INTERRUPTS();
    while(1);
}

/*-----------------------------------------------------------*/

void vApplicationIdleHook(void)
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If the application makes use of the
    vTaskDelete() API function (as this demo application does) then it is also
    important that vApplicationIdleHook() is permitted to return to its calling
    function, because it is the responsibility of the idle task to clean up
    memory allocated by the kernel to any task that has since been deleted. */
}

/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void) pcTaskName;
    (void) pxTask;

    /* Run time task stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook	function is 
    called if a task stack overflow is detected.  Note the system/interrupt
    stack is not checked. */
    taskDISABLE_INTERRUPTS();
    while(1);
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */
}

/*-----------------------------------------------------------*/

void vAssertCalled(const char * pcFile, unsigned long ulLine)
{
    volatile unsigned long ul=0;

    (void) pcFile;
    (void) ulLine;

    __asm volatile( "di");
    {
        /* Set ul to a non-zero value using the debugger to step out of this
        function. */
        while(ul==0)
        {
            portNOP();
        }
    }
    __asm volatile( "ei");
}

int main(void) // <editor-fold defaultstate="collapsed" desc="main function">
{
    SYSTEM_Initialize();
    portDISABLE_INTERRUPTS();
    Application_Init();
    xTaskCreate(Bootloader_Tasks, /* The function that implements the task. */
            "Bld", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
            configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
            NULL, /* The parameter passed to the task - just to check the functionality. */
            BOOTLOADER_TASK_PRIORITY, /* The priority assigned to the task. */
            NULL); /* The task handle is not required, so NULL is passed. */
    xTaskCreate(Application_Tasks, /* The function that implements the task. */
            "App", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
            configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
            NULL, /* The parameter passed to the task - just to check the functionality. */
            APPLICATION_TASK_PRIORITY, /* The priority assigned to the task. */
            NULL); /* The task handle is not required, so NULL is passed. */

#if defined(USB_CDC_DEBUG_H)
    xTaskCreate(USB_CDC_Debug_Tasks, /* The function that implements the task. */
            "CdcDb", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
            configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
            NULL, /* The parameter passed to the task - just to check the functionality. */
            USB_CDC_TASK_PRIORITY, /* The priority assigned to the task. */
            NULL); /* The task handle is not required, so NULL is passed. */
#elif defined(USB_CDC_UART_H)
    xTaskCreate(USB_CDC_UART_Tasks, /* The function that implements the task. */
            "CdcUart", /* The text name assigned to the task - for debug only as it is not used by the kernel. */
            configMINIMAL_STACK_SIZE, /* The size of the stack to allocate to the task. */
            NULL, /* The parameter passed to the task - just to check the functionality. */
            USB_CDC_TASK_PRIORITY, /* The priority assigned to the task. */
            NULL); /* The task handle is not required, so NULL is passed. */
#endif

    vTaskStartScheduler();

    return 1;
} // </editor-fold>

