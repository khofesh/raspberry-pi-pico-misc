#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define TEMPERATURE_UNITS 'C'
#define ever \
    ;        \
    ;

float read_onboard_temperature(const char unit)
{

    /* 12-bit conversion, assume max value == ADC_VREF == 3.3 V */
    const float conversionFactor = 3.3f / (1 << 12);

    float adc = (float)adc_read() * conversionFactor;
    float tempC = 27.0f - (adc - 0.706f) / 0.001721f;

    if (unit == 'C')
    {
        return tempC;
    }
    else if (unit == 'F')
    {
        return tempC * 9 / 5 + 32;
    }

    return -1.0f;
}

int main()
{
    stdio_init_all();

    // configure adc
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    for (ever)
    {
        float temperature = read_onboard_temperature(TEMPERATURE_UNITS);
        printf("Onboard temperature = %.02f %c\n", temperature, TEMPERATURE_UNITS);

        sleep_ms(990);
    }

    return 0;
}
