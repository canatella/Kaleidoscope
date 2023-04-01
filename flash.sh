#!/bin/sh
set -e

make -C examples/Devices/DM/Quetch/ -j
while ! dfu-programmer atmega32u4 erase; do
    echo "reset keyboard, retrying in 5s"
    sleep 5
done
dfu-programmer atmega32u4 flash /tmp/kaleidoscope-dam/output/231332904-Quetch.ino/Quetch-latest.hex
dfu-programmer atmega32u4 start
