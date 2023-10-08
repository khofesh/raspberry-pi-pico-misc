#include <stdio.h>
#include "pico/stdlib.h"

#define ever \
    ;        \
    ;

int main()
{
    // initialize GPIO - gree LED is connected to pin 25
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    for (ever)
    {
        gpio_put(25, 1);
        sleep_ms(500);
        gpio_put(25, 0);
        sleep_ms(500);
    }

    return 0;
}
