# MicroPython

## compile the micropython firmware

```shell
cd ~/pico
mkdir pico_w
cd pico_w
git clone https://github.com/micropython/micropython.git --branch master
git clone https://github.com/micropython/micropython-lib.git --branch master
```

build MicroPython

```shell
cd micropython
make -C ports/rp2 BOARD=PICO_W submodules
make -C mpy-cross
cd ports/rp2/
make BOARD=PICO_W -j12
```

upload the program to the pico w

```shell
cd build-PICO_W/

sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program firmware.elf verify reset exit"
```

connect over USB

```shell
[user@ryzen build-PICO_W]$ minicom -o -D /dev/ttyACM1


Welcome to minicom 2.8

OPTIONS: I18n
Compiled on Jul 21 2022, 00:00:00.
Port /dev/ttyACM1, 11:05:32

Press CTRL-A Z for help on special keys


>>>
>>> help()
Welcome to MicroPython!
```

if you press CTRL-D

```shell
>>>
MPY: soft reboot
MicroPython v1.19.1-915-g2bcd88d55 on 2023-03-04; Raspberry Pi Pico W with RP200
Type "help()" for more information.
```

## remote access via serial port

```shell
$ pip install mpremote
$ mpremote connect list
/dev/ttyACM0 XXXXXXXX 2e8a:000c Raspberry Pi Debug Probe (CMSIS-DAP)
/dev/ttyACM1 XXXXXXXX 2e8a:0005 MicroPython Board in FS mode
/dev/ttyS0 None 0000:0000 None None
$ mpremote connect /dev/ttyACM1
```

## toggle LED (mpremote)

```shell
$ mpremote connect /dev/ttyACM1
Connected to MicroPython at /dev/ttyACM1
Use Ctrl-] to exit this shell

>>>
>>> import machine
>>> led = machine.Pin("LED", machine.Pin.OUT)
>>> led.off()
>>> led.on()
>>> led
Pin(EXT_GPIO0, mode=OUT)
```

# configure project

![config](../images/Screenshot%20from%202023-03-04%2011-35-03.png)

## running iperf

the example in "Connecting to the Internet with Raspberry Pi Pico W" is a bit outdated

**Server**

install iperf3

```shell
dnf -y install iperf3
```

open port 5201

```shell
[user@ryzen ~]$ sudo firewall-cmd --add-port=5201/tcp
success
[user@ryzen ~]$ sudo firewall-cmd --list-port
5201/tcp 27017/tcp

```

run iperf3

```shell
[user@ryzen ~]$ sudo iperf3 -s
-----------------------------------------------------------
Server listening on 5201 (test #1)
-----------------------------------------------------------
Accepted connection from 192.168.68.110, port 59054
[  5] local 192.168.68.111 port 5201 connected to 192.168.68.110 port 59055
[ ID] Interval           Transfer     Bitrate
[  5]   0.00-1.00   sec   310 KBytes  2.54 Mbits/sec
[  5]   1.00-2.00   sec   299 KBytes  2.45 Mbits/sec
[  5]   2.00-3.00   sec   666 KBytes  5.46 Mbits/sec
[  5]   3.00-4.00   sec   650 KBytes  5.32 Mbits/sec
[  5]   4.00-5.00   sec   413 KBytes  3.38 Mbits/sec
```

**Client**

```python
>>> import network
>>> wlan = network.WLAN(network.STA_IF)
>>> wlan.active(True)
>>> ssid = ''
>>> password = ''
>>> wlan.connect(ssid, password)
>>> import mip
>>> mip.install('iperf3')
>>> import iperf3
>>> iperf3.client('192.168.68.111')
CLIENT MODE: TCP sending
Connecting to ('192.168.68.111', 5201)
Interval           Transfer     Bitrate
  0.00-1.00   sec   316 KBytes  2.59 Mbits/sec
  1.00-2.00   sec   297 KBytes  2.43 Mbits/sec
  2.00-3.00   sec   669 KBytes  5.48 Mbits/sec
  3.00-4.00   sec   650 KBytes  5.32 Mbits/sec
  4.00-5.00   sec   413 KBytes  3.39 Mbits/sec
```

### remove port after testing

```shell
sudo firewall-cmd --remove-port=5201/tcp
```

## copy libs to pico using mpremote

```shell
mpremote a1 cp lcd1602.py :
```

a1 -> connect to serial port "/dev/ttyACM1"

# References

- https://github.com/micropython/micropython/tree/master/ports/rp2
- appendix A of "Connecting to the internet with raspberry pi pico W"
- https://www.server-world.info/en/note?os=CentOS_8&p=iperf3
- https://www.server-world.info/en/note?os=CentOS_8&p=firewalld&f=1
- [micropython mip](https://docs.micropython.org/en/latest/reference/packages.html)
