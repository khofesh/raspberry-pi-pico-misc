from machine import I2C
from lcd_api import LcdApi
from i2c_lcd import I2cLcd
import utime

I2C_ADDR     = 0x27
I2C_NUM_ROWS = 2
I2C_NUM_COLS = 16

sda = machine.Pin(0)
scl = machine.Pin(1)
i2c = I2C(0, sda=sda, scl=scl, freq=400000)
lcd = I2cLcd(i2c, I2C_ADDR, I2C_NUM_ROWS, I2C_NUM_COLS)

adc = machine.ADC(4)
conversion_factor = 3.3 / (65535)

while True:
    reading = adc.read_u16() * conversion_factor
    temperature = 25 - (reading - 0.706)/0.001721
    lcd.clear()
    out_string = 'temp: ' + str(temperature)
    lcd.putstr(out_string)
    utime.sleep(2)