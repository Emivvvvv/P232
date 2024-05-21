#include "P_header.h"

int main()
{
    // test @int
    @int A (10)
    @int A_2 (10)
    @int A_3 (10)
    @int B (5)
    @int C_test (100)
    @int D_array (8)
    @int E (5,5)
    @int F (20, 20)
    @int G_test (30, 30)
    @int G_test2 (30, 30)
    @int G_test3 (30, 30)
    @int H_array (15, 125)

    // test @read
    @read A < f1_nums

    // test @copy
    @copy A = A_2
    @copy G_test = G_test2

    // test @init
    @print A = 2
    if (1 == 1) {
        @print E = 5
    } else {
        if (1 != 2) {
            @print C_test = 10
        }
    }
    @print H_array = 1000

    // test @print
    @print A
    @print E
    @print C_test
    @print H_array

    // test @dotp
    @dotp A = A_2 . A_3

    // test @add
    @add G_test = G_test2 * G_test3

    // test @mmult
    @mmult G_test = G_test2 * G_test3

    // test @sum
    @sum A
    @sum E
    @sum C_test
    @sum H_array

    // test @aver
    @aver A
    @aver E
    @aver C_test
    @aver H_array

    return 0;
}