#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/adc.h"

#define ever \
    ;        \
    ;

// core 1 interrupt handler
void core1_interrupt_handler()
{
    // receive raw value, convert and print temperature over USB serial
    while (multicore_fifo_rvalid())
    {
        uint16_t raw = multicore_fifo_pop_blocking();
        const float conversion_factor = 3.3f / (1 << 12);
        float result = raw * conversion_factor;
        float temp = 27 - (result - 0.706) / 0.001721;
        printf("temp = %f C\n", temp);
    }

    // clear interrupt
    multicore_fifo_clear_irq();
}

// core 1 main code
void core1_entry()
{
    // configure core 1 interrupt
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
    irq_set_enabled(SIO_IRQ_PROC1, true);

    // infinite loop which wait for interrupt
    for (ever)
    {
        tight_loop_contents();
    }
}

// core 0 main code
int main()
{
    stdio_init_all();

    multicore_launch_core1(core1_entry); // start core 1

    // configure ADC
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    // primary core 0 loop

    for (ever)
    {
        uint16_t raw = adc_read();
        multicore_fifo_push_blocking(raw);
        sleep_ms(1000);
    }

    return 0;
}
