#include "P_header.h"

/*
 * P_header.c, implementation file
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

// Define global variables
int P_dot;
int P_sum;
int P_aver;

struct ArrayTable AT[20]; // max. 20 arrays
struct ParseTable PT; // Creates a C declaration for an integer array from array table data.

char* declaration(int array_table_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[array_table_index];

    if (A->dim == 1 && A->size1[0] == '\0' || A->dim == 2 && (A->size1[0] == '\0' || A->size2[0] == '\0'))
        return "Error: Arrays size values must be filled.";
    else if (A->dim == 1)
        sprintf(extended, "int %s[%s];", A->name, A->size1);
    else
        sprintf(extended, "int %s[%s][%s];", A->name, A->size1, A->size2);

    return extended;
}

// Reads array elements from a file into the specified array from the array table.
char* read(int array_table_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[array_table_index];

    if (A->dim == 1)
        sprintf(extended,
            "FILE* file = fopen(\"%s\", \"r\");\n"
            "int num, count = 0;\n"
            "while (count < %s && fscanf(file, \"%%d\", &num) == 1) {\n"
            "\t%s[count++] = num;\n"
            "}\n"
            "fclose(file);\n",
            PT.rhs1,
            A->size1,
            A->name
        );
    else
        sprintf(extended,
            "FILE* file = fopen(\"%s\", \"r\");\n"
            "int num, count = 0;\n"
            "for (int i = 0; i < %s && count < %s * %s; i++) {\n"
            "\tfor (int j = 0; j < %s && fscanf(file, \"%%d\", &num) == 1; j++) {\n"
            "\t\t%s[i][j] = num;\n"
            "\t\tcount++;\n"
            "\t}\n"
            "}\n"
            "fclose(file);\n",
            PT.rhs1,
            AT[array_table_index].size1,
            AT[array_table_index].size1,
            AT[array_table_index].size2,
            AT[array_table_index].size2,
            AT[array_table_index].name
        );

    return extended;
}

// Takes two arrays source and destination,then copies source to destination.
char* copy(int Array_S , int Array_D) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[Array_S];
    struct ArrayTable* B = &AT[Array_D];

    if (A->dim != B->dim)
        return "Error: Arrays should have same dimension value.";
    if (strcmp(A->size1, B->size1) != 0)
        return "Error: Arrays must have the same length.";

    if(A->dim == 1)
        sprintf(extended,
                "for (int i = 0; i < %s; i++) {\n"
                "\t%s[i] = %s[i];\n"
                "}\n",
                A->size1,
                B->name, 
                A->name);
 
    else if (A->dim == 2) {
        if (strcmp(A->size2, B->size2) != 0)
            return "Error: Arrays must have the same length.";

        sprintf(extended,
            "for (int i = 0; i < %s; i++) {\n"
            "\tfor (int j = 0; j < %s; j++) {\n"
            "\t\t%s[i][j] = %s[i][j];\n"
            "\t}\n"
            "}\n",
            A->size1,
            A->size2,
            B->name, 
            A->name);
    }

    return extended;
}


//This code represents a C function that initializes a table array with a specific size and value. The function is called with the index of the array table and the initialization value.
char* initialize(int array_table_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[array_table_index];

    if (A->dim == 1)
        sprintf(extended,
                "for (int i = 0; i < %s; i++) {\n"
                "\t%s[i] = %s;\n"
                "}\n",
                A->size1,
                A->name,
                PT.rhs1);
    else
        sprintf(extended,
                "for (int i = 0; i < %s; i++) {\n"
                "\tfor (int j = 0; j < %s; j++) {\n"
                "\t\t%s[i][j] = %s;\n"
                "\t}\n"
                "}\n",
                A->size1,
                A->size2,
                A->name,
                PT.rhs1);

    return extended;
}

// This code represents a C function that prints an array with a specific size and value. The function is called with the index of the array table. 
char* print(int array_table_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[array_table_index];
    
    if(A->dim == 1)
        sprintf(extended,
            "printf(\"[\");\n"
            "for (int i = 0; i < %s-1; i++) {\n"
            "\tprintf(\"%%d, \", %s[i]);\n"
            "}\n"
            "printf(\"%%d]\", %s[%s-1]);\n" ,
            A->size1,
            A->name,
            A->name,
            A->size1);

    else if (A->dim == 2)
        sprintf(extended,
            "printf(\"[\");\n"
            "for (int i = 0; i < %s; i++) {\n"
            "\tprintf(\"[\");\n"
            "\tfor (int j = 0; j < %s-1; j++) {\n"
            "\t\tprintf(\"%%d, \", %s[i][j]);\n" //ASSUME ARRAY IS INT ARRAY
            "\t}\n"
            "\tprintf(\"%%d]\", %s[i][%s-1]);\n"
            "}\n"
            "printf(\"]\");\n",
            A->size1,
            A->size2,
            A->name,
            A->name,
            A->size2);

    return extended;
}

// Takes two 1D matrices, calculates their dot product and assigns it to the environmental variable P_dot
char* matrix_dot_product(int A_index , int B_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[A_index];
    struct ArrayTable* B = &AT[B_index];

    if (A->dim != 1 || B->dim != 1)
        return "Error: All arrays must be 1D for array  for dot product.";

    if (strcmp(A->size1, B->size1) != 0)
        return "Error: Arrays A and B must have the same length for  for dot product.";

    sprintf(extended,
            "P_dot = 0;\n"
            "for (int i = 0; i < %s; i++) {\n"
            "\tP_dot += %s[i] + %s[i];\n"
            "}\n",
            A->size1,
            A->name, B->name);

    return extended;
}

// Takes two matrices, adds them accordingly and assigns the result to another matrix
char* matrix_addition(int C_index, int A_index , int B_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[A_index];
    struct ArrayTable* B = &AT[B_index];
    struct ArrayTable* C = &AT[C_index];

    if (A->dim == 1 && B->dim == 1 && C->dim == 1) {
        if ((strcmp(A->size1, B->size1) != 0)||
        (strcmp(A->size1, B->size1) != 0) || (strcmp(A->size1, C->size1) != 0)) {
            return "Error: Arrays A , B and C must have the same length for array addition.";
        }
    }
    else if (A->dim == 2 && B->dim == 2 && C->dim == 2){
        sprintf(extended,
                "for (int i = 0; i < %s; i++) {\n"
                "\t%s[i] = %s[i] + %s[i];\n"
                "}\n",
                A->size1,
                C->name, A->name, B->name);

        if ((strcmp(A->size1, B->size1) != 0) ||
            (strcmp(A->size1, C->size1) != 0) ||
            (strcmp(A->size2, B->size2) != 0) ||
            (strcmp(A->size2, C->size2) != 0)) {
            return "Error: Arrays A , B and C must have the same length for array addition.";
        }
        sprintf(extended,
                "for (int i = 0; i < %s; i++) {\n"
                "\tfor(int j = 0; j < %s; j++){\n"
                "\t\t%s[i][j] = %s[i][j] + %s[i][j];\n"
                "\t}\n"
                "}\n",
                A->size1,
                A->size2,
                C->name, A->name, B->name);
    } else {
        return "Error: All arrays must have the same dimensions for array addition.";
    }

    return extended;
}

// Takes two matrices, multiplies them accordingly and assigns the result to another matrix
char* matrix_multiplication(int C_index, int A_index , int B_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[A_index];
    struct ArrayTable* B = &AT[B_index];
    struct ArrayTable* C = &AT[C_index];

    if (A->dim == 2 && B->dim == 2 && C->dim == 2){
        if ((strcmp(A->size1, C->size1) != 0) ||
            (strcmp(A->size2, B->size1) != 0) ||
            (strcmp(B->size2, C->size2) != 0)) {
            return "Error: Arrays A , B and C must have axb bxc axc respectively sizes for array multiplication.";
        } else {
            sprintf(extended,
                    "for (int i = 0; i < %s; i++){\n"
                    "\tfor (int j = 0; j < %s; j++){\n"
                    "\t\t%s[i][j] = 0;\n"
                    "\t\tfor (int k = 0; k < %s; k++){\n"
                    "\t\t\t%s[i][j] += %s[i][k] * %s[k][j];\n"
                    "\t\t}\n"
                    "\t}\n"
                    "}\n",
                    C->size1,
                    C->size2,
                    C->name,
                    A->size2,
                    C->name, A->name, B->name);
        }
    } else {
        return "Error: Arrays A , B and C must have the 2D for array multiplication.";
    }

    return extended;
}

// Takes an array or a matrix, sums all its elements and assign the result to a variable called P_sum.
char* reduction_operations_sum(int A_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[A_index];

    if(A->dim == 1)
        sprintf(extended,
                "P_sum = 0;\n"
                "for(int i = 0; i < %s; i++){\n"
                "\tP_sum += %s[i];\n"
                "}\n",
                A->size1,
                A->name);

    else if(A->dim == 2)
        sprintf(extended,
                "P_sum = 0;\n"
                "for(int i = 0; i < %s; i++){\n"
                "\tfor(int j = 0; j < %s; j++){\n"
                "\t\tP_sum += %s[i][j];\n"
                "\t}\n"
                "}\n",
                A->size1,
                A->size2,
                A->name);
    else
        return "Error: Unsupported dimension for sum operation.";

    return extended;
}

// Takes an array or a matrix, sums all its elements and divides its number of elements and assign the result to a variable called P_aver.
char* reduction_operations_aver(int A_index) {
    char* extended = malloc(1024);

    struct ArrayTable* A = &AT[A_index];

    if(A->dim == 1)
        sprintf(extended,
        "P_aver = 0;\n"
        "for(int i = 0; i < %s; i++){\n"
        "\tP_aver += %s[i];\n"
        "}\n"
        "P_aver /= %s;\n",
        A->size1,
        A->name,
        A->size1);

    else if(A->dim == 2)
        sprintf(extended,
        "P_aver = 0;\n"
        "for(int i = 0; i < %s; i++){\n"
        "\tfor(int j = 0; j < %s; j++){\n"
        "\t\tP_aver += %s[i][j];\n"
        "\t}\n"
        "}\n"
        "P_aver /= (%s * %s);\n",
        A->size1,
        A->size2,
        A->name,
        A->size1,
        A->size2);
    else
        return "Error: Unsupported dimension for average operation.";

    return extended;
}
