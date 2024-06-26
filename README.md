# P232
A C programming language preprocessor to perform arithmetic operations on matrices. Yeditepe University CSE232 course group term project.


|     **Group Members**     |                  Tasks                  |
|:-------------------------:|:---------------------------------------:|
| **Leader** - Emirhan Tala |           main.c, @int, @read           |
|      Nika Golestani       | makefile, sh, @copy, find_array_index() |
|        Eylül Akar         |           @dotp, @add, @mmult           |
|    Samet Alper Özdemir    |               @sum, @aver               |
|   Dilara Zeynep Kesgün    |              @init, @read               |


## How to Use P232 Preprocessor

P232 is a preprocessor designed to expand C programs containing special operation directives. This document outlines how to use the `p232.sh` script and the Makefile to process C programs with your custom preprocessor directives.

### Requirements

- Linux environment with a Bash shell
- GCC compiler

### Usage

To use the preprocessor, you need to pass a single C source file with a `.c` extension as an argument to the `p232.sh` script. Here is how you can run it:

```bash
./p232 myCprog.c
```

The script performs the following operations:
1. Checks if exactly one argument is provided.
2. Verifies that the file has a `.c` extension.
3. Compiles the program if it's not already compiled.
4. Executes the preprocessor on the provided file, generating an expanded C program saved as `expanded.c`.

### Cleaning Up

To clean up object files and the executable, run:

```bash
make clean
```

If you also want to remove the `expanded.c` file generated by the preprocessor, run:

```bash
make clean-all
```

### Available directives

- `@int B(10)` declares 1D integer array B with 10 elements
- `@int A(3,5)` declares 2D integer array A with 3x5 elements
- `@read B < f1` Reads all elements of an array from a file.
- `@copy C = A` Copies all elements of an array to another array.
- `@init A = 2` Initializes all elements of an array to a value.
- `@print A` Prints the array elements on the screen.
- `@dotp C = A . B` Calculates the dot product of two 1D arrays and assigns the result to the preprocessor variable P_dot
- `@add C = A + B` Adds two arrays and assigns the result to an array
- `@mmult C = A * B` Multiplies two 2D arrays and assigns the result to a 2D array
- `@sum A` Sums all elements of an array and assigns the result to the preprocessor variable P_sum
- `@aver A` Calculates the average of all elements in an array and assigns the result to the preprocessor variable P_aver.

### Example

Here's a simple example of a C program using preprocessor directives:

```
#include "P_header.h"

int main() {
    @int X(10)
    @init X = 0
    @print X
    return 0;
}
```

Running `./p232.sh` on this file would generate an `expanded.c` file with the expanded C code.

```
#include “P_header.h”

int main() {
    int X[10];
    for (int i=0; i<10; ++i)
        X[i]=0;
    for (int i=0; i<10; ++i)
        printf(“%d “, X[i]);
    printf(“\n”);
    return 0;
}
```
