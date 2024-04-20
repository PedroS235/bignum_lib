#include "big_num.h"
#include "tests.h"

int main() {
    test_compare();
    test_add();
    test_sub();
    test_mul();

    // printf("%d", compare_bignum(&a, &b));

    return 0;
}
