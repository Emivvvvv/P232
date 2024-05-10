#include "P_header.h"

int main()
{
    int B[10];
        int C[10];
            int D[10];
                int E[10];
                    int F[10];
                int G[10];
            int H[5][7];
        int Y[7][4];
    int Z[5][4];
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
                for (int i = 0; i < 5; i++){
                	for (int j = 0; j < 4; j++){
                		Z[i][j] = 0;
                		for (int k = 0; k < 7; k++){
                			Z[i][j] += H[i][k] * Y[k][j];
                		}
                	}
                }
    return 0;
}
