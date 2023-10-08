#include <stdio.h>
#include "pico/stdlib.h"

#define ever \
    ;        \
    ;

int main()
{
    stdio_init_all();

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    char userInput;

    for (ever)
    {
        printf("command (1 = on or 0 = off):\n");
        userInput = getchar();

        if (userInput == '1')
        {
            gpio_put(25, 1);
            printf("led switched on\n");
        }
        else if (userInput == '0')
        {
            gpio_put(25, 0);
            printf("led switched off\n");
        }
        else
        {
            printf("invalid input\n");
        }
    }

    return 0;
}
