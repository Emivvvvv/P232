#include "P_header.h"

int main()
{
    @int X(10)
        @int A(5)
            @int B(3,5)
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