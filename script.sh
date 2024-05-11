#!/bin/bash

clear

# Check for exactly one command-line argument
if [ $# -ne 1 ]; then
    echo "Error: Please provide exactly one C source file."
    exit 1
fi

# Check if the argument has a .c extension
if [[ $1 != *.c ]]; then
    echo "Error: The file must have a .c extension."
    exit 1
fi

# Compile the program
make

if [ $? -eq 0 ]; then
    # Run the program with the provided .c file
    ./p232.out "$1"
else
    echo "Compilation failed."
    exit 1
fi

