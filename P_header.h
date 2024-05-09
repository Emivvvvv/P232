#ifndef P232_P_HEADER_H
#define P232_P_HEADER_H
/*
 * P_header.h, header file
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

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

// Make necessary changes
char* declaration();

// Make necessary changes
char* read();

// Make necessary changes
extern char*
copy();

// Make necessary changes
extern char*
initialize();

// Make necessary changes
extern char*
print();

// Make necessary changes
extern char*
matrix_dot_product();

// Make necessary changes
extern char*
matrix_addition();

// Make necessary changes
extern char*
matrix_multiplication();

// Make necessary changes
extern char*
reduction_operations_sum();

// Make necessary changes
extern char*
reduction_operations_aver();

#endif
