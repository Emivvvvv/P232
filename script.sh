#!/bin/bash
clear
make
if [ $? -eq 0 ]; then
    ./p232.out
else
    echo "Compilation failed."
fi
