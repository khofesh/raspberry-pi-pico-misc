#!/bin/sh

rm -rf build/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program blink.elf verify reset exit"
