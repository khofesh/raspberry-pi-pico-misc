# Pico Tutorials

## multicore

it doesn't print to serial

![debug](./img/Screenshot%20from%202023-10-08%2015-29-41.png)

## freertos_blink

```shell
cd freertos_blink
mkdir lib
cd lib
git submodule add https://github.com/FreeRTOS/FreeRTOS-Kernel.git
git submodule update --init
```

in `FreeRTOSConfig.h`

```c
#define configUSE_CORE_AFFINITY                 0
```

compile

```shell
./flash.sh src/freertos_blink.elf
```

## freertos part 2

```shell
git clone --recurse-submodules https://github.com/khofesh/rp2040-freertos-template.git
```

# References

- youtube playlist: https://youtube.com/playlist?list=PLEB5F4gTNK68IlRIJtcJ_2cW4dSdmreTw&si=iJeGFPTNpFun2908
- freertos tutorial: https://www.youtube.com/playlist?list=PLEB5F4gTNK68zDlrXbcCgJ6NejaP0PvHX
