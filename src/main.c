#include "big_num.h"
#include "tests.h"

int main() {
    test_compare();
    test_add();
    test_sub();
    test_mul();
    test_div();
    test_remainder();
    test_addmod();
    test_multmod();
    test_expmod();
    test_extended_gcd();
    // test_inversemod();

    // printf("%d", compare_bignum(&a, &b));

    return 0;
}
