#include "P_header.h"

int main()
{
    int A[10];
        int B[7][5];
    int D[3][5];
    FILE* file = fopen("f1", "r");
    int num, count = 0;
    for (int i = 0; i < 7 && count < 7 * 5; i++) {
    	for (int j = 0; j < 5 && fscanf(file, "%d", &num) == 1; j++) {
    	B[i][j] = num;
    	count++;
    	}
    }
    fclose(file);
    @copy
        @init
            @print
                @dotp
            @add
        @mmult 
        @sum
    @aver
    return 0;
}
