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
    char edited_text[1024] = {0};

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

        int result = snprintf(edited_text, sizeof(edited_text), "FILE* file = fopen(\"%s\", \"r\");\n", filename);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        strncat(extended, "int num, count = 0;\n", sizeof(extended) - strlen(extended) - 1);

        result = snprintf(edited_text, sizeof(edited_text), "while (count < %d && fscanf(file, \"%%d\", &num) == 1) {\n", array_size);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        result = snprintf(edited_text, sizeof(edited_text), "\t%s[count++] = num;\n", AT[array_table_index].name);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        strncat(extended, "}\nfclose(file);\n", sizeof(extended) - strlen(extended) - 1);
    } else {
        int rows = atoi(AT[array_table_index].size1);
        int columns = atoi(AT[array_table_index].size2);
        if (rows <= 0 || columns <= 0) {
            fprintf(stderr, "Invalid array size.\n");
            return NULL;
        }

        int result = snprintf(edited_text, sizeof(edited_text), "FILE* file = fopen(\"%s\", \"r\");\n", filename);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        strncat(extended, "int num, count = 0;\n", sizeof(extended) - strlen(extended) - 1);

        result = snprintf(edited_text, sizeof(edited_text), "for (int i = 0; i < %d && count < %d * %d; i++) {\n", rows, rows, columns);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        result = snprintf(edited_text, sizeof(edited_text), "\tfor (int j = 0; j < %d && fscanf(file, \"%%d\", &num) == 1; j++) {\n", columns);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        result = snprintf(edited_text, sizeof(edited_text), "\t%s[i][j] = num;\n\tcount++;\n", AT[array_table_index].name);
        if (result >= 0 && result < sizeof(edited_text)) {
            strncat(extended, edited_text, sizeof(extended) - strlen(extended) - 1);
        }

        strncat(extended, "\t}\n}\nfclose(file);\n", sizeof(extended) - strlen(extended) - 1);
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

// Takes two 1D matrices , takes their dot product and assigns it to a integer and environmental variable P_dot
char* matrix_dot_product(int A_index , int B_index) {
    char* extended[1024] = {0};

    struct ArrayTable* A = &AT[A_index];
    struct ArrayTable* B = &AT[B_index];

    if (A->dim != 1 || B->dim != 1) {
        return "Error: All arrays must be 1D for array  for dot product.";
    }
    if (strcmp(A->size1, B->size1) != 0) {
        return "Error: Arrays A and B must have the same length for  for dot product.";
    }
    sprintf(extended,
            "P_dot = 0;\n"
            "for (int i = 0; i < %s; i++) {\n"
            "\tP_dot += %s[i] + %s[i];\n"
            "}\n",
            A->size1,
            A->name, B->name
    );

    return extended;
}

// Make necessary changes
char* matrix_addition(int C_index, int A_index , int B_index) {
    char* extended[1024] = {0};

    struct ArrayTable* A = &AT[A_index];
    struct ArrayTable* B = &AT[B_index];
    struct ArrayTable* C = &AT[C_index];

    if (A->dim == 1 && B->dim == 1 && C->dim == 1) {
       if ((strcmp(A->size1, B->size1) != 0) ||
            (strcmp(A->size1, B->size1) != 0) ||
            (strcmp(A->size1, C->size1) != 0)) {
        return "Error: Arrays A , B and C must have the same length for array addition.";
        }
       sprintf(extended,
        "for (int i = 0; i < %s; i++) {\n"
        "\t%c[i] = %c[i] + %c[i];\n"
        "}\n",
        A->size1,
        C->name[0], A->name[0], B->name[0]
        ); 
    }
    else if (A->dim == 2 && B->dim == 2 && C->dim == 2){
        if ((strcmp(A->size1, B->size1) != 0) ||
            (strcmp(A->size1, C->size1) != 0) ||
            (strcmp(A->size2, B->size2) != 0) ||
            (strcmp(A->size2, C->size2) != 0)) {
        return "Error: Arrays A , B and C must have the same length for array addition.";
        }
        sprintf(extended,
        "for (int i = 0; i < %s; i++) {\n"
        "\tfor(int j = 0; j < %s; j++){\n"
        "\t\t%c[i][j] = %c[i][j] + %c[i][j];\n"
        "\t}\n"
        "}\n",
        A->size1,
        A->size2,
        C->name[0], A->name[0], B->name[0]
        ); 
    } else {
        return "Error: All arrays must have the same dimensions for array addition.";
    }
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