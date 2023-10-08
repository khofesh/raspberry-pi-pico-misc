#include <stdio.h>
#include "pico/stdlib.h"

#define ever \
    ;        \
    ;

int main()
{
    // initialize I/O
    stdio_init_all();

    // initialize GPIO - gree LED is connected to pin 25
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for (ever)
    {
        gpio_put(25, 1);
        printf("led ON \n");
        sleep_ms(1000);

        gpio_put(25, 0);
        printf("led OFF \n");
        sleep_ms(1000);
    }

    return 0;
}
