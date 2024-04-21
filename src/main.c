#include "bignum.h"
#include "tests.h"

int main() {
    test_multmod();
    test_expmod();
    test_extended_gcd();
    // test_inversemod();

    // printf("%d", compare_bignum(&a, &b));

    return 0;
}
