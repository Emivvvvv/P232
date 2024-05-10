#ifndef P232_P_HEADER_H
#define P232_P_HEADER_H
/*
 * P_header.h, header file
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int P_dot;
int P_sum;
int P_aver;

struct ArrayTable {
    char name[10];
    int dim; // 1: 1-dimensional, 2: 2-dimensional
    char size1[10]; // size of dimension 1
    char size2[10]; // size of dimension 2
};
struct ArrayTable AT[20]; // max. 20 arrays

struct ParseTable {
    char oper[10]; // @read, @copy, etc.
    char lhs; // array on the left hand side
    char rhs1; // first array on the right hand side
    char rhs2; // second array on the right hand side
};
struct ParseTable PT;

// Generates a C language declaration for an integer array based on the specification provided in the array table.
// Both 1D and 2D array generation is possible.
// @param array_table_index: The index in the array table which contains the array's name, dimensions, and sizes.
// @return char*: A string containing the C language declaration for the array.
extern char* declaration(int array_table_index);

// Reads integers seperated by spaces from a file and stores them into the array defined in the array table.
// The function handles both one-dimensional and two-dimensional arrays, depending on the array's dimension in the array table.
// @param array_table_index: The index in the array table which contains the array's name, dimensions, and size specifications.
// @return char*: A string containing the C code necessary to perform the file reading and array population.
extern char* read(int array_table_index);

// Make necessary changes
extern char* copy();

// Make necessary changes
extern char* initialize();

// Make necessary changes
extern char* print();

// Calculates the dot product of two one-dimensional arrays, given their indices in the array table,
// and assigns the result to the environmental variable `P_dot`.
// The function checks that both arrays are 1D and have the same length before generating code to calculate the dot product.
// @param A_index: The index in the array table for the first 1D array.
// @param B_index: The index in the array table for the second 1D array.
// @return char*: A string containing C code that calculates the dot product of two 1D arrays.
extern char* matrix_dot_product(int A_index , int B_index);

// Takes two matrices (1D or 2D), adds them element-wise, and assigns the result to another matrix.
// The function checks if all matrices have the same dimensions and lengths before generating C code for the addition.
// @param C_index: The index in the array table for the result matrix where the addition result is stored.
// @param A_index: The index in the array table for the first matrix to be added.
// @param B_index: The index in the array table for the second matrix to be added.
// @return char*: A string containing C code to add two matrices and store the result in another matrix.
extern char* matrix_addition(int C_index, int A_index , int B_index);


// Takes two two-dimensional matrices, multiplies them using the standard matrix multiplication rule, and assigns the result to another matrix.
// The function checks if the matrices have the correct dimensions for multiplication before generating the C code.
// @param C_index: The index in the array table for the result matrix where the multiplication result is stored.
// @param A_index: The index in the array table for the first matrix to be multiplied.
// @param B_index: The index in the array table for the second matrix to be multiplied.
// @return char*: A string containing C code to multiply two matrices and store the result in another matrix.
extern char* matrix_multiplication(int C_index, int A_index , int B_index);


// Takes an array or a matrix, sums all its elements and assign the result to a variable called P_sum.
// The function checks if the array is 1D or 2D array.
// @param A_index: The index in the ArrayTable for the array whose average is to be calculated.
// @return char*: A string containing C code that calculates the sum of the array's elements.
extern char* reduction_operations_sum();

// Takes an array or a matrix, sums all its elements and divides its number of elements and assign the result to a variable called P_aver.
// The function checks if the array is 1D or 2D array.
// @param A_index: The index in the ArrayTable for the array whose average is to be calculated.
// @return char*: A string containing C code that calculates the average of the array's elements.
extern char* reduction_operations_aver();

#endif
