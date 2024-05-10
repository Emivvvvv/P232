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

// Reads array elements from a file into the specified array from the array table.
char* read(int array_table_index) {
    char extended[1024] = {0};

    char filename[3];
    filename[0] = PT.rhs1;
    filename[1] = PT.rhs2;
    filename[2] = '\0';

    if (AT[array_table_index].dim == 1) {
        int array_size = atoi(AT[array_table_index].size1);
        if (array_size <= 0) {
            fprintf(stderr, "Invalid array size.\n");
            return NULL;
        }

        int result = snprintf(extended, sizeof(extended),
                              "FILE* file = fopen(\"%s\", \"r\");\n"
                              "int num, count = 0;\n"
                              "while (count < %d && fscanf(file, \"%%d\", &num) == 1) {\n"
                              "\t%s[count++] = num;\n"
                              "}\n"
                              "fclose(file);\n",
                              filename,
                              array_size,
                              AT[array_table_index].name
        );

        if (result < 0 || result >= sizeof(extended)) {
            return "Error: Something went wrong while creating the extended string.";
        }
    } else {
        int rows = atoi(AT[array_table_index].size1);
        int columns = atoi(AT[array_table_index].size2);
        if (rows <= 0 || columns <= 0) {
            fprintf(stderr, "Invalid array size.\n");
            return NULL;
        }

        int result = snprintf(extended, sizeof(extended),
                              "FILE* file = fopen(\"%s\", \"r\");\n"
                              "int num, count = 0;\n"
                              "for (int i = 0; i < %d && count < %d * %d; i++) {\n"
                              "\tfor (int j = 0; j < %d && fscanf(file, \"%%d\", &num) == 1; j++) {\n"
                              "\t\t%s[i][j] = num;\n"
                              "\t\tcount++;\n"
                              "\t}\n"
                              "}\n"
                              "fclose(file);\n",
                              filename,
                              rows, rows, columns,
                              columns,
                              AT[array_table_index].name
        );

        if (result < 0 || result >= sizeof(extended)) {
            return "Error: Something went wrong while creating the extended string.";
        }
    }

    return extended;
}

// Make necessary changes
char* copy() {
    char* extended = "@copy";
    return extended;
}

// Make necessary changes
char* initialize() {
    char* extended = "@init";
    return extended;
}

// Make necessary changes
char* print() {
    char* extended = "@print";
    return extended;
}

// Make necessary changes
char* matrix_dot_product() {
    char* extended = "@dotp";
    return extended;
}

// Make necessary changes
char* matrix_addition() {
    char* extended = "@add";
    return extended;
}

// Make necessary changes
char* matrix_multiplication() {
    char* extended = "@mmult ";
    return extended;
}

// Make necessary changes
char* reduction_operations_sum() {
    char* extended = "@sum";
    return extended;
}

// Make necessary changes
char* reduction_operations_aver() {
    char* extended = "@aver";
    return extended;
}