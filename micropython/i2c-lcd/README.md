# Get started with micropython on raspberry pi pico

## LCD with hd44780 controller

### scan for any I2C devices

```python
import machine

sdaPIN=machine.Pin(0)
sclPIN=machine.Pin(1)
i2c=machine.I2C(0,sda=sdaPIN, scl=sclPIN, freq=400000)

devices = i2c.scan()
if len(devices) == 0:
    print("No i2c device !")
else:
    print('i2c devices found:',len(devices))
for device in devices:
    print("At address: ",hex(device))
```

### I2C LCD micropython libs

copy the content of `lcd_api.py` to thonny and save it to raspberry pi pico.

do the same thing with `pico_i2c_lcd.py` content.

it looks something like this:

![i2c lcd](../../images/Screenshot%20from%202023-02-15%2022-48-03.png)

### references

- https://microcontrollerslab.com/i2c-lcd-raspberry-pi-pico-micropython-tutorial/
- https://github.com/T-622/RPI-PICO-I2C-LCD
- https://www.youtube.com/watch?v=B8Kr_3xHjqE
- https://peppe8o.com/using-i2c-lcd-display-with-raspberry-pi-pico-and-micropython/
