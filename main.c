/*
 * main.c, P232 main function.
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

#include "P_header.h"


// Function declarations
void parse_line(char* line);
void enter_array_table();
void process_and_expand_directive();
void print_with_spaces(const char* expanded_line);
int find_array_index(const char* array_name);
char* ltrim(char* s, int* left_trim_space_count);
char *rtrim(char* s);
char* trim(char* s, int* left_trim_space_count);

int array_table_index = 0;
int line_left_space_count = 0;

FILE* source_file = NULL;
FILE* expanded_file = NULL;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>.c\n", argv[0]);
        return 1;
    }

    char* filename = argv[1];

    source_file = fopen(filename, "r");
    expanded_file = fopen("expanded.c", "w");

    if (!source_file) {
        printf("Couldn't open source file \"%s\"\n", filename);
        return 1;
    } else if (!expanded_file) {
        printf("Error at opening expanded file!\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), source_file)) {
        char trimmed_line[1024];
        strcpy(trimmed_line, trim(line, &line_left_space_count));

        if (trimmed_line[0] == '@') {
            parse_line(line);
            if (strcmp(PT.oper, "@int") == 0)
                enter_array_table();
            process_and_expand_directive();
        } else {
            fprintf(expanded_file, "%s\n", line);
        }
    }

    fclose(source_file);
    fclose(expanded_file);

    return 0;
}

// Parse the line and fill the Parse Table
void parse_line(char* line) {
    char* saveptr;  // Pointer for internal strtok_r state

    char* oper = strtok_r(line, " (,)<=.+*;", &saveptr);
    if (oper != NULL) {
        strcpy(PT.oper, oper);
    } else {
        PT.oper[0] = '\0';
    }

    char* lhs = strtok_r(NULL, " (,)<=.+*;", &saveptr);
    if (lhs != NULL) {
        strcpy(PT.lhs, lhs);
    } else {
        PT.lhs[0] = '\0';
    }

    char* rhs1 = strtok_r(NULL, " (,)<=.+*;", &saveptr);
    if (rhs1 != NULL) {
        strcpy(PT.rhs1, rhs1);
    } else {
        PT.rhs1[0] = '\0';
    }

    char* rhs2 = strtok_r(NULL, " (,)<=.+*;", &saveptr);
    if (rhs2 != NULL) {
        strcpy(PT.rhs2, rhs2);
    } else {
        PT.rhs2[0] = '\0';
    }
}

void enter_array_table() {
    strcpy(AT[array_table_index].name, PT.lhs);
    strcpy(AT[array_table_index].size1, PT.rhs1);
    strcpy(AT[array_table_index].size2, PT.rhs2);

    if (PT.rhs2[0] == '\0')
        AT[array_table_index].dim = 1;
    else
        AT[array_table_index].dim = 2;

    array_table_index++;
}

// Process directive based on parsed information
void process_and_expand_directive() {
    char* expanded_line = NULL;
    char undefined_string[50] = "Undefined directive";

    if (strcmp(PT.oper, "@int") == 0)
        expanded_line = declaration(array_table_index - 1);
    else if (strcmp(PT.oper, "@read") == 0)
        expanded_line = read(find_array_index(PT.lhs));
    else if (strcmp(PT.oper, "@copy") == 0)
        expanded_line = copy(find_array_index(PT.rhs1),find_array_index(PT.lhs));
    else if (strcmp(PT.oper, "@init") == 0)
        expanded_line = initialize(find_array_index(PT.lhs));
    else if (strcmp(PT.oper, "@print") == 0)
        expanded_line = print(find_array_index(PT.lhs));
    else if (strcmp(PT.oper, "@dotp") == 0)
        expanded_line = matrix_dot_product(find_array_index(PT.rhs1),find_array_index(PT.rhs2));
    else if (strcmp(PT.oper, "@add") == 0)
        expanded_line = matrix_addition(find_array_index(PT.lhs),find_array_index(PT.rhs1),find_array_index(PT.rhs2));
    else if (strcmp(PT.oper, "@mmult") == 0)
        expanded_line = matrix_multiplication(find_array_index(PT.lhs),find_array_index(PT.rhs1),find_array_index(PT.rhs2));
    else if (strcmp(PT.oper, "@sum") == 0)
        expanded_line = reduction_operations_sum(find_array_index(PT.lhs));
    else if (strcmp(PT.oper, "@aver") == 0)
        expanded_line = reduction_operations_aver(find_array_index(PT.lhs));

    if (expanded_line != NULL) {
        print_with_spaces(expanded_line);
    } else {
        print_with_spaces(undefined_string);
    }
}

void print_with_spaces(const char* expanded_line) {
    char spaces[line_left_space_count + 1];  // +1 for the null terminator
    memset(spaces, ' ', line_left_space_count);
    spaces[line_left_space_count] = '\0';

    const char *temp = expanded_line;
    while (*temp) {
        fprintf(expanded_file, "%s", spaces); // Print spaces at the beginning of each line

        // Print characters until a newline or end of string
        while (*temp && *temp != '\n') {
            fputc(*temp, expanded_file);
            temp++;
        }

        // Handle newline at the end of line
        if (*temp == '\n') {
            fputc(*temp, expanded_file);
            temp++;
        } else {
            // If we reach the end of the string without a newline, add one
            fputc('\n', expanded_file);
        }
    }
}

int find_array_index(const char* array_name) {
    for (int i = 0; i < 20 && AT[i].name[0] != '\0'; i++) {
        if (strcmp(AT[i].name, array_name) == 0) {
            return i;
        }
    }
    printf("ERR: Undefined Array: %s\n", array_name);
    return -1;
}


char* ltrim(char* s, int* left_trim_space_count)
{
    *left_trim_space_count = 0;
    while(isspace(*s)) {
        (*left_trim_space_count)++;
        s++;
    }
    return s;
}

char *rtrim(char* s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char* trim(char* s, int* left_trim_space_count)
{
    return rtrim(ltrim(s, left_trim_space_count));
}
