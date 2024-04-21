#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "core.h"

void test_sub_basic() {
    bignum_t a = str2bignum("1");
    bignum_t b = str2bignum("0");
    bignum_t c = sub(&a, &b);
    CU_ASSERT(compare_bignum(&a, &c) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_sub_simple() {
    bignum_t a = str2bignum("50");
    bignum_t b = str2bignum("40");
    bignum_t c = sub(&a, &b);
    bignum_t expected = str2bignum("10");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_w_max_uint64() {
    bignum_t a = str2bignum("36893488147419103230");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c = sub(&a, &b);
    bignum_t expected = str2bignum("18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_w_negative_simple() {
    bignum_t a = str2bignum("-10");
    bignum_t b = str2bignum("-5");
    bignum_t c = sub(&a, &b);
    bignum_t expected = str2bignum("-5");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_w_negative_large() {
    bignum_t a = str2bignum("-36893488147419103230");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c = sub(&a, &b);
    bignum_t expected = str2bignum("-55340232221128654845");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_w_negative_large_2() {
    bignum_t a = str2bignum("-36893488147419103230");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c = sub(&a, &b);
    bignum_t expected = str2bignum("-18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_sub_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_sub_basic", test_sub_basic);
    CU_add_test(suite, "test_bignum_sub_simple", test_sub_simple);
    CU_add_test(suite, "test_bignum_sub_w_max_uint64", test_sub_w_max_uint64);
    CU_add_test(suite, "test_bignum_sub_w_negative_large", test_sub_w_negative_large);
    CU_add_test(
        suite, "test_bignum_sub_basic_w_negative_large_2", test_sub_w_negative_large_2);
}
