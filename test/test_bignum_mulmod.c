#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_multmod_basic() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("20");
    bignum_t n = str2bignum("55");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("35");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_large() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("393");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_large_negative() {
    bignum_t a = str2bignum("-340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("649");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void bignum_multmod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_multmod_basic", test_multmod_basic);
    CU_add_test(suite, "test_multmod_large", test_multmod_large);
    CU_add_test(suite, "test_multmod_large_negative", test_multmod_large_negative);
}
