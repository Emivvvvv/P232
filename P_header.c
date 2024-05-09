#include "P_header.h"

/*
 * P_header.c, implementation file
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

// Creates a C declaration for an integer array from array table data.
char* declaration(int array_table_index) {
    char extended[1024];

    if (AT[array_table_index].dim == 1) {
        sprintf(extended, "int %s[%s];", AT[array_table_index].name, AT[array_table_index].size1);
    } else {
        sprintf(extended, "int %s[%s][%s];", AT[array_table_index].name, AT[array_table_index].size1, AT[array_table_index].size2);
    }

    return extended;
}

// Make necessary changes
char* read() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* copy() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* initialize() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* print() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* matrix_dot_product() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* matrix_addition() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* matrix_multiplication() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* reduction_operations_sum() {
    char* extended = "test";
    return extended;
}

// Make necessary changes
char* reduction_operations_aver() {
    char* extended = "test";
    return extended;
}