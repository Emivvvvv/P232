#include "P_header.h"

int main()
{
    int A[10];
    int B[10];
    int C[10];
    int D[10];
    int E[10];
    int F[10];
    int G[10];
    FILE* file = fopen("f1", "r");
    int num, count = 0;
    while (count < 10 && fscanf(file, "%d", &num) == 1) {
    	D[count++] = num;
    }
    fclose(file);
    P_dot = 0;
    for (int i = 0; i < 10; i++) {
    	P_dot += B[i] + C[i];
    }
    for (int i = 0; i < 10; i++) {
    	E[i] = F[i] + G[i];
    }
    return 0;
}
