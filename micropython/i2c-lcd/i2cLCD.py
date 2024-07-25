import machine
import utime

sda = machine.Pin(0)
scl = machine.Pin(1)
i2c = machine.I2C(0, sda=sda, scl=scl, freq=400000)
I2C_ADDR     = 0x27
#print(i2c.scan())
#i2c.writeto(114, '\x7C')
#i2c.writeto(114, '\x2D')
#i2c.writeto(114, 'hello world')

adc = machine.ADC(4)
conversion_factor = 3.3 / (65535)

while True:
    reading = adc.read_u16() * conversion_factor
    temperature = 25 - (reading - 0.706)/0.001721
    i2c.writeto(I2C_ADDR, '\x7C')
    i2c.writeto(I2C_ADDR, '\x2D')
    out_string = 'temp: ' + str(temperature)
    i2c.writeto(I2C_ADDR, out_string)
    utime.sleep(2)