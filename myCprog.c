#include "P_header.h"

int main()
{
    @int B(10)
        @int C(10)
            @int D(10)
                @int E(10)
                    @int F(10)
                @int G(10)
            @int H(5,7)
            @int K(5,7)
        @int Y(7,4)
    @int Z(5,4)
    @read D < f1
        @dotp Z= B . C
            @add E = F + G
                @mmult Z = H * Y
@sum B
    @sum Y
@aver E
    @aver Z
    @copy C = D
@copy H = K
    return 0;
}