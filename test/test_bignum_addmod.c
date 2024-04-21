#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_addmod_basic() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("20");
    bignum_t n = str2bignum("4");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("2");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_large() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("508");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_large_negative() {
    bignum_t a = str2bignum("-340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("818");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void bignum_addmod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_addmod_basic", test_addmod_basic);
    CU_add_test(suite, "test_addmod_large", test_addmod_large);
    CU_add_test(suite, "test_addmod_large_negative", test_addmod_large_negative);
}
