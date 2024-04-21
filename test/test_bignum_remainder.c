#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "core.h"

void test_remainder_simple() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("4");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("2");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_remainder_negative() {
    bignum_t a = str2bignum("-10");
    bignum_t b = str2bignum("4");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("2");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_remainder_zero() {
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("4");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("0");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_remainder_zero_divisor() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("0");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("0");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_remainder_large() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("1042");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("887");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void bignum_remainder_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_remainder", test_remainder_simple);
    CU_add_test(suite, "test_bignum_remainder_negative", test_remainder_negative);
    CU_add_test(suite, "test_bignum_remainder_zero", test_remainder_zero);
    // TODO: When the correct behavior is ready, uncomment the test below
    // CU_add_test(
    //     suite, "test_bignum_remainder_zero_divisor", test_remainder_zero_divisor);
    CU_add_test(suite, "test_bignum_remainder_large", test_remainder_large);
}
