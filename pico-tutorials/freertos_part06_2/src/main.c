#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// https://embeddedcomputing.com/technology/open-source/linux-freertos-related/using-freertos-with-the-raspberry-pi-pico-part-4

const int task_delay = 500;
const int task_size = 128;

SemaphoreHandle_t mutex;

void vGuardedPrint(char *out)
{
    xSemaphoreTake(mutex, portMAX_DELAY);
    puts(out);
    xSemaphoreGive(mutex);
}

void vTaskSMP_print_core(void *pvParameters)
{
    char *task_name = pcTaskGetName(NULL);
    char out[12];

    for (;;)
    {
        sprintf(out, "%s %d", task_name, get_core_num());
        vGuardedPrint(out);
        vTaskDelay(task_delay);
    }
}

int main()
{
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, 1);

    mutex = xSemaphoreCreateMutex();

    // define the task handlers
    TaskHandle_t handleA;
    TaskHandle_t handleB;

    // create 4x tasks with different names and 2 with handlers

    xTaskCreate(vTaskSMP_print_core, "A", task_size, NULL, 1, &handleA);
    xTaskCreate(vTaskSMP_print_core, "B", task_size, NULL, 1, &handleB);
    xTaskCreate(vTaskSMP_print_core, "C", task_size, NULL, 1, NULL);
    xTaskCreate(vTaskSMP_print_core, "D", task_size, NULL, 1, NULL);

    // pin tasks
    traceENTER_vTaskCoreAffinitySet(handleA, (1 << 0)); // core 0
    traceENTER_vTaskCoreAffinitySet(handleB, (1 << 1)); // core 1

    vTaskStartScheduler();
}