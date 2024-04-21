#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "core.h"

void test_add_basic() {
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("1");
    bignum_t c = add(&a, &b);
    CU_ASSERT(compare_bignum(&b, &c) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_add_simple() {
    bignum_t a = str2bignum("50");
    bignum_t b = str2bignum("40");
    bignum_t c = add(&a, &b);
    bignum_t expected = str2bignum("90");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_max_uint64() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c = add(&a, &b);
    bignum_t expected = str2bignum("36893488147419103230");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_w_negative_simple() {
    bignum_t a = str2bignum("-10");
    bignum_t b = str2bignum("-5");
    bignum_t c = add(&a, &b);
    bignum_t expected = str2bignum("-15");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_w_negative_large() {
    bignum_t a = str2bignum("-18446744073709551615");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c = add(&a, &b);
    bignum_t expected = str2bignum("-36893488147419103230");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_add_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_add_basic", test_add_basic);
    CU_add_test(suite, "test_bignum_add_simple", test_add_simple);
    CU_add_test(suite, "test_bignum_add_max_uint64", test_add_max_uint64);
    CU_add_test(suite, "test_bignum_add_w_negative_large", test_add_w_negative_large);
}
