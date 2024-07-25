# Raspberry Pi Pico Misc

- Raspberry Pi Pico
- Raspberry Pi Debug Probe

## Setup

lsusb

```shell
[user@ryzen ~]$  lsusb
...
Bus 005 Device 005: ID 2e8a:0003 Raspberry Pi RP2 Boot
...
```

## pico-sdk

```shell
mkdir pico
cd pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
cd ..
git clone -b master https://github.com/raspberrypi/pico-examples.git

```

if you list the pico folder now looks like this

```shell
[user@ryzen pico]$  ls
pico-examples  pico-sdk
```

## install packages

```shell
sudo dnf install gcc-arm-linux-gnu arm-none-eabi-newlib arm-none-eabi-gcc-cs arm-none-eabi-gcc-cs-c++
```

## blink onboard LED

```shell
cd ~/pico/pico-examples/
mkdir build
cd build
export PICO_SDK_PATH=../../pico-sdk
```

now, since I have pico w board, I need to specify the board

```shell
cmake -DPICO_BOARD=pico_w ..
```

go to the blink folder for `pico_w`

```shell
cd pico-examples/build/pico_w/blink
make -j4
```

## upload the `.uf2`

hold down the `BOOTSEL` on the pico w as you plug it in. mount the pico to `/mnt`

```shell
sudo mkdir -p /mnt/pico
sudo mount /dev/sdd1 /mnt/pico
```

if you list the `/mnt/pico/` folder, you'll see two files already there

```shell
[user@ryzen blink]$  ls /mnt/pico
INDEX.HTM  INFO_UF2.TXT
```

copy the `.uf2` file to `/mnt/pico/`, then unmount the pico w.

```shell
[user@ryzen blink]$ pwd
/home/user/pico/pico-examples/build/pico_w/blink
[user@ryzen blink]$  ls
CMakeFiles           picow_blink.bin  picow_blink.elf.map
cmake_install.cmake  picow_blink.dis  picow_blink.hex
Makefile             picow_blink.elf  picow_blink.uf2
[user@ryzen blink]$  sudo cp picow_blink.uf2 /mnt/pico/
[user@ryzen blink]$  sudo umount /mnt/pico
```

![pico w blink](./images/pico-w-blink.gif)

## ESP01

- [Can't communicate Pi Pico with ESP01(AT commands) using C](https://forums.raspberrypi.com/viewtopic.php?t=339415)
- [No webserver with DIP-PI PIOT](https://forums.raspberrypi.com/viewtopic.php?t=335483)
- https://github.com/vshymanskyy/BlynkESP8266
- https://www.youtube.com/watch?v=v_Tm_IgbRDc
- https://github.com/CytronTechnologies/MAKER-PI-PICO/issues/1

# References

- https://youtube.com/playlist?list=PLEB5F4gTNK68IlRIJtcJ_2cW4dSdmreTw&si=h6JpgvXs4Dq5eYoq
- https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html#blink-an-led
- https://forums.raspberrypi.com/viewtopic.php?t=336836
- https://www.electromaker.io/blog/article/getting-started-with-the-raspberry-pi-pico-w-cc-sdk
- https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html
- https://raspberrypi.github.io/pico-sdk-doxygen/index.html
- https://developer.arm.com/documentation/dui0662/latest/
- [lwIP - A Lightweight TCP/IP stack](https://github.com/lwip-tcpip/lwip)
