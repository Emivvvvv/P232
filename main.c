/*
 * main.c, P232 main function.
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "P_header.h"
#include "utils.h"

// Function declarations
void assign_token(const char *token, char *target);
void parse_line(char* line);
void enter_array_table();
void process_and_expand_directive();
void print_spaces();

int array_table_index = 0;
int line_left_space_count = 0;

FILE* sourceFile = NULL;
FILE* expandedFile = NULL;

int main() {
    sourceFile = fopen("../myCprog.c", "r");
    expandedFile = fopen("../expanded.c", "w");

    if (!sourceFile || !expandedFile) {
        printf("Error opening files!\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), sourceFile)) {
        char trimmed_line[1024];
        strcpy(trimmed_line, trim(line, &line_left_space_count));

        if (trimmed_line[0] == '@') {
            parse_line(line);
            if (strcmp(PT.oper, "@int") == 0 || strcmp(PT.oper, "@int1") == 0) {
                enter_array_table();
            }
            process_and_expand_directive();
        } else {
            fprintf(expandedFile, "%s\n", line);
        }
    }

    fclose(sourceFile);
    fclose(expandedFile);

    return 0;
}

// Parse the line and fill the Parse Table
void parse_line(char* line) {
    strcpy(PT.oper, strtok(line, " (,)<=.+*"));

    // We assume there is no syntax error.
    // if there is no token, we assing it to 0.
    char* lhs =strtok(NULL, " (,)<=.+*");
    assign_token(lhs, &PT.lhs);

    char* rhs1 =strtok(NULL, " (,)<=.+*");
    assign_token(rhs1, &PT.rhs1);

    char* rhs2 =strtok(NULL, " (,)<=.+*");
    assign_token(rhs2, &PT.rhs2);

    if (strcmp(PT.oper, "@read") == 0 || ((strcmp(PT.oper, "@int") == 0 && rhs2 == NULL))) {
        if (strcmp(PT.oper, "@int") == 0) {
            strcat(PT.oper, "1");
        }
        PT.rhs1 = rhs1[0];
        PT.rhs2 = rhs1[1];
    }
}

void assign_token(const char *token, char *target) {
    if (token == NULL) {
        *target = '\0'; // Assign null character if token is NULL
    } else {
        *target = *token; // Assign first character of the token
    }
}

void enter_array_table() {
    strcpy(AT[array_table_index].name, &PT.lhs);

    if (strcmp(PT.oper, "@int1") == 0) {
        AT[array_table_index].dim = 1;

        AT[array_table_index].size1[0] = PT.rhs1;
        AT[array_table_index].size1[1] = PT.rhs2;
        AT[array_table_index].size1[2] = '\0';

        AT[array_table_index].size2[0] = '0';
        AT[array_table_index].size2[1] = '\0';
    } else {
        AT[array_table_index].dim = 2;

        AT[array_table_index].size1[0] = PT.rhs1;
        AT[array_table_index].size1[1] = '\0';

        AT[array_table_index].size2[0] = PT.rhs2;
        AT[array_table_index].size2[1] = '\0';
    }

    array_table_index++;
}

// Process directive based on parsed information
void process_and_expand_directive() {
    char expanded_line[1024];

    if (strcmp(PT.oper, "@int") == 0 || strcmp(PT.oper, "@int1") == 0) {
        strcpy(expanded_line, declaration());
    } else if (strcmp(PT.oper, "@read") == 0) {
        strcpy(expanded_line, read());
    } else if (strcmp(PT.oper, "@copy") == 0) {
        strcpy(expanded_line, copy());
    } else if (strcmp(PT.oper, "@init") == 0) {
        strcpy(expanded_line, initialize());
    } else if (strcmp(PT.oper, "@print") == 0) {
        strcpy(expanded_line, print());
    } else if (strcmp(PT.oper, "@dotp") == 0) {
        strcpy(expanded_line, matrix_dot_product());
    } else if (strcmp(PT.oper, "@add") == 0) {
        strcpy(expanded_line, matrix_addition());
    } else if (strcmp(PT.oper, "@mmult") == 0) {
        strcpy(expanded_line, matrix_multiplication());
    } else if (strcmp(PT.oper, "@sum") == 0) {
        strcpy(expanded_line, reduction_operations_sum());
    } else if (strcmp(PT.oper, "@aver") == 0) {
        strcpy(expanded_line, reduction_operations_aver());
    } else {
        printf("Undefined directive: %s", PT.oper);
    }
    
    print_spaces();
    fprintf(expandedFile, "%s\n", expanded_line);
}

void print_spaces() {
    for (int i = 0; i < line_left_space_count; i++) fprintf(expandedFile, " ");
}
