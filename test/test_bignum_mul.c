#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_mul_basic() {
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("1");
    bignum_t c = mul_bignum(&a, &b);
    CU_ASSERT(compare_bignum(&a, &c) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_mul_simple() {
    bignum_t a = str2bignum("50");
    bignum_t b = str2bignum("50");
    bignum_t c = mul_bignum(&a, &b);
    bignum_t expected = str2bignum("2500");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_max_uint64() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c = mul_bignum(&a, &b);
    bignum_t expected = str2bignum("340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_w_negative_large() {
    bignum_t a = str2bignum("-18446744073709551615");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c = mul_bignum(&a, &b);
    bignum_t expected = str2bignum("-340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_w_2_negative_large() {
    bignum_t a = str2bignum("-18446744073709551615");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c = mul_bignum(&a, &b);
    bignum_t expected = str2bignum("340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_mul_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_mul_basic", test_mul_basic);
    CU_add_test(suite, "test_bignum_mul_simple", test_mul_simple);
    CU_add_test(suite, "test_bignum_mul_max_uint64", test_mul_max_uint64);
    CU_add_test(suite, "test_bignum_mul_w_negative_large", test_mul_w_negative_large);
    CU_add_test(
        suite, "test_bignum_mul_w_2_negative_large", test_mul_w_2_negative_large);
}
