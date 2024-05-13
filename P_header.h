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

extern int P_dot;
extern int P_sum;
extern int P_aver;

struct ArrayTable {
    char name[10];
    int dim; // 1: 1-dimensional, 2: 2-dimensional
    char size1[10]; // size of dimension 1
    char size2[10]; // size of dimension 2
};
extern struct ArrayTable AT[20]; // max. 20 arrays

struct ParseTable {
    char oper[10]; // @read, @copy, etc.
    char lhs[10];
    char rhs1[10];
    char rhs2[10];
};
extern struct ParseTable PT;

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

// Assigns one array's information to another array.
//Their sizes and dimensions must be equal. If arrays have different dimensions or sizes, return an error string.
// The function handles both one-dimensional and two-dimensional arrays, depending on the array's dimension in the array table.
// @param Array_S: The index of source array in the array table which contains the array's name, dimensions, and size specifications.
// @param Array_D: The index of destination array in the array table which contains the array's name, dimensions, and size specifications.
// @return char*: A string containing the C code necessary to perform copying source array to destination array.
extern char* copy(int Array_S , int Array_D);

// This code represents a C function that initializes a table array with right-hand side value of ParseTable. The function is called with the index of the array table.
// The function handles both one-dimensional and two-dimensional arrays, depending on the array's dimension in the array table.
// @param array_table_index : The index of array in the array table which contains the array's name, dimensions, and size specifications.
// @return char*: A string containing the C code necessary to perform initializing value to array.
extern char* initialize(int array_table_index);

// This code represents a C function that prints an array with a specific size and value. The function is called with the index of the array table.
// The function handles both one-dimensional and two-dimensional arrays, depending on the array's dimension in the array table.
// @param array_table_index : The index of array in the array table which contains the array's name, dimensions, and size specifications.
// @return char*: A string containing the C code necessary to perform initializing value to array.
extern char* print(int array_table_index);

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
extern char* reduction_operations_sum(int A_index);

// Takes an array or a matrix, sums all its elements and divides its number of elements and assign the result to a variable called P_aver.
// The function checks if the array is 1D or 2D array.
// @param A_index: The index in the ArrayTable for the array whose average is to be calculated.
// @return char*: A string containing C code that calculates the average of the array's elements.
extern char* reduction_operations_aver(int A_index);

#endif
