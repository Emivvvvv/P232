#include "P_header.h"

int main()
{
    @int A(10)
        @int B(7,5)
    @int D(3,5)
    @read B < f1
    @copy C = A
        @init X = 0
            @print X
                @dotp C = A . B
            @add C = A + B
        @mmult C = A * B
        @sum A
    @aver A
    return 0;
}