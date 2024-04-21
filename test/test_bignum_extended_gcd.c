#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_extended_gcd_simple() {
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("15");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("5");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
}

void bignum_extended_gcd_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "Extended GCD Simple", test_extended_gcd_simple);
}
