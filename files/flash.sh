#!/bin/sh

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <elf_filename>"
  exit 1
fi

ELF_FILENAME="$1"

rm -rf build/
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
sudo openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program $ELF_FILENAME verify reset exit"
