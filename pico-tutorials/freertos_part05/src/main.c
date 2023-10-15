#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "semphr.h"

SemaphoreHandle_t count;

void led_task()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true)
    {
        if (xSemaphoreTake(count, (TickType_t)10) == pdTRUE)
        {
            gpio_put(LED_PIN, 1);
            vTaskDelay(100);
        }
        else
        {
            gpio_put(LED_PIN, 0);
            vTaskDelay(1);
        }
    }
}

void button_task()
{
    gpio_init(27);
    gpio_set_dir(27, GPIO_IN);

    while (true)
    {
        if (gpio_get(27) != 0)
        {
            xSemaphoreGive(count);
            vTaskDelay(20);
        }
        else
        {
            vTaskDelay(1);
        }
    }
}

int main()
{
    stdio_init_all();

    count = xSemaphoreCreateCounting(5, 0);

    xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    xTaskCreate(button_task, "Button_Task", 256, NULL, 1, NULL);
    vTaskStartScheduler();

    while (1)
    {
        /* code */
    }
}