/*
 * main.c, P232 main function.
 *
 * P232, a C programming language preprocessor to perform arithmetic operations on matrices.
 * Yeditepe University CSE232 course group term project.
 */

#include "P_header.h"


// Function declarations
void assign_token(const char *token, char *target);
void parse_line(char* line);
void enter_array_table();
void process_and_expand_directive();
void print_with_spaces(const char* expanded_line);
int find_array_index(char array_name);
char* ltrim(char* s, int* left_trim_space_count);
char *rtrim(char* s);
char* trim(char* s, int* left_trim_space_count);

int array_table_index = 0;
int line_left_space_count = 0;

FILE* source_file = NULL;
FILE* expanded_file = NULL;

int main() {
    source_file = fopen("../myCprog.c", "r");
    expanded_file = fopen("../expanded.c", "w");

    if (!source_file || !expanded_file) {
        printf("Error opening files!\n");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), source_file)) {
        char trimmed_line[1024];
        strcpy(trimmed_line, trim(line, &line_left_space_count));

        if (trimmed_line[0] == '@') {
            parse_line(line);
            if (strcmp(PT.oper, "@int") == 0 || strcmp(PT.oper, "@int1") == 0) {
                enter_array_table();
            }
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
    AT[array_table_index].name[0] = PT.lhs;
    AT[array_table_index].name[1] = '\0';

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
    char expanded_line[2048] = {0};

    if (strcmp(PT.oper, "@int") == 0 || strcmp(PT.oper, "@int1") == 0) {
        strcpy(expanded_line, declaration(array_table_index - 1));
    } else if (strcmp(PT.oper, "@read") == 0) {
        strcpy(expanded_line, read(find_array_index(PT.lhs)));
    } else if (strcmp(PT.oper, "@copy") == 0) {
        strcpy(expanded_line, copy(find_array_index(PT.rhs1),find_array_index(PT.lhs)));
    } else if (strcmp(PT.oper, "@init") == 0) {
        strcpy(expanded_line, initialize());
    } else if (strcmp(PT.oper, "@print") == 0) {
        strcpy(expanded_line, print(find_array_index(PT.lhs)));
    } else if (strcmp(PT.oper, "@dotp") == 0) {
        strcpy(expanded_line, matrix_dot_product(find_array_index(PT.rhs1),find_array_index(PT.rhs2)));
    } else if (strcmp(PT.oper, "@add") == 0) {
        strcpy(expanded_line, matrix_addition(find_array_index(PT.lhs),find_array_index(PT.rhs1),find_array_index(PT.rhs2)));
    } else if (strcmp(PT.oper, "@mmult") == 0) {
        strcpy(expanded_line, matrix_multiplication(find_array_index(PT.lhs),find_array_index(PT.rhs1),find_array_index(PT.rhs2)));
    } else if (strcmp(PT.oper, "@sum") == 0) {
        strcpy(expanded_line, reduction_operations_sum(find_array_index(PT.lhs)));
    } else if (strcmp(PT.oper, "@aver") == 0) {
        strcpy(expanded_line, reduction_operations_aver(find_array_index(PT.lhs)));
    } else {
        printf("Undefined directive: %s", PT.oper);
    }
    
    print_with_spaces(expanded_line);
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
//Find the AT index that has given array name
int find_array_index(const char array_name) {
    for (int i = 0; i < 20 && AT[i].name[0] != '\0'; i++) {
        if (AT[i].name[0] == array_name) {
            return i; 
        }
    }
    printf("Undefined Array: %c", array_name);
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
