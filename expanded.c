#include "P_header.h"

int main()
{
    // test @int
    int A[10];
    int A_2[10];
    int A_3[10];
    int B[5];
    int C_test[100];
    int D_array[8];
    int E[5][5];
    int F[20][20];
    int G_test[30][30];
    int G_test2[30][30];
    int G_test3[30][30];
    int H_array[15][125];

    // test @read
    FILE* file = fopen("f1_nums", "r");
    int num, count = 0;
    while (count < 10 && fscanf(file, "%d", &num) == 1) {
    	A[count++] = num;
    }
    fclose(file);

    // test @copy
    for (int i = 0; i < 10; i++) {
    	A[i] = A_2[i];
    }
    for (int i = 0; i < 30; i++) {
    	for (int j = 0; j < 30; j++) {
    		G_test[i][j] = G_test2[i][j];
    	}
    }

    // test @init
    for (int i = 0; i < 10; i++) {
    	A[i] = 2;
    }
    if (1 == 1) {
        for (int i = 0; i < 5; i++) {
        	for (int j = 0; j < 5; j++) {
        		E[i][j] = 5;
        	}
        }
    } else {
        if (1 != 2) {
            for (int i = 0; i < 100; i++) {
            	C_test[i] = 10;
            }
        }
    }
    for (int i = 0; i < 15; i++) {
    	for (int j = 0; j < 125; j++) {
    		H_array[i][j] = 1000;
    	}
    }

    // test @print
    printf("[");
    for (int i = 0; i < 10-1; i++) {
    	printf("%d, ", A[i]);
    }
    printf("%d]", A[10-1]);
    printf("[");
    for (int i = 0; i < 5; i++) {
    	printf("[");
    	for (int j = 0; j < 5-1; j++) {
    		printf("%d, ", E[i][j]);
    	}
    	printf("%d]", E[i][5-1]);
    }
    printf("]");
    printf("[");
    for (int i = 0; i < 100-1; i++) {
    	printf("%d, ", C_test[i]);
    }
    printf("%d]", C_test[100-1]);
    printf("[");
    for (int i = 0; i < 15; i++) {
    	printf("[");
    	for (int j = 0; j < 125-1; j++) {
    		printf("%d, ", H_array[i][j]);
    	}
    	printf("%d]", H_array[i][125-1]);
    }
    printf("]");

    // test @dotp
    P_dot = 0;
    for (int i = 0; i < 10; i++) {
    	P_dot += A_2[i] + A_3[i];
    }

    // test @add
    for (int i = 0; i < 30; i++) {
    	for(int j = 0; j < 30; j++){
    		G_test[i][j] = G_test2[i][j] + G_test3[i][j];
    	}
    }

    // test @mmult
    for (int i = 0; i < 30; i++){
    	for (int j = 0; j < 30; j++){
    		G_test[i][j] = 0;
    		for (int k = 0; k < 30; k++){
    			G_test[i][j] += G_test2[i][k] * G_test3[k][j];
    		}
    	}
    }

    // test @sum
    P_sum = 0;
    for(int i = 0; i < 10; i++){
    	P_sum += A[i];
    }
    P_sum = 0;
    for(int i = 0; i < 5; i++){
    	for(int j = 0; j < 5; j++){
    		P_sum += E[i][j];
    	}
    }
    P_sum = 0;
    for(int i = 0; i < 100; i++){
    	P_sum += C_test[i];
    }
    P_sum = 0;
    for(int i = 0; i < 15; i++){
    	for(int j = 0; j < 125; j++){
    		P_sum += H_array[i][j];
    	}
    }

    // test @aver
    P_aver = 0;
    for(int i = 0; i < 10; i++){
    	P_aver += A[i];
    }
    P_aver /= 10;
    P_aver = 0;
    for(int i = 0; i < 5; i++){
    	for(int j = 0; j < 5; j++){
    		P_aver += E[i][j];
    	}
    }
    P_aver /= (5 * 5);
    P_aver = 0;
    for(int i = 0; i < 100; i++){
    	P_aver += C_test[i];
    }
    P_aver /= 100;
    P_aver = 0;
    for(int i = 0; i < 15; i++){
    	for(int j = 0; j < 125; j++){
    		P_aver += H_array[i][j];
    	}
    }
    P_aver /= (15 * 125);

    // test undefined oper
    Undefined directive: @undef
    Undefined directive: @what
    return 0;
}
