#include <CUnit/CUnit.h>

#include "bignum/arithmetic.h"
#include "bignum/common.h"

void test_sub_simple() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "50");
    str2bignum(&b, "40");
    sub_bignum(&c, &a, &b);
    str2bignum(&expected, "10");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_pos_pos() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "36893488147419103230");
    str2bignum(&b, "18446744073709551615");
    sub_bignum(&c, &a, &b);
    str2bignum(&expected, "18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_neg_neg() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "-36893488147419103230");
    str2bignum(&b, "-18446744073709551615");
    sub_bignum(&c, &a, &b);
    str2bignum(&expected, "-18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_neg_pos() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "-36893488147419103230");
    str2bignum(&b, "18446744073709551615");
    sub_bignum(&c, &a, &b);
    str2bignum(&expected, "-55340232221128654845");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_pos_neg() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "36893488147419103230");
    str2bignum(&b, "-18446744073709551615");
    sub_bignum(&c, &a, &b);
    str2bignum(&expected, "55340232221128654845");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_sub_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_sub_simple", test_sub_simple);
    CU_add_test(suite, "test_bignum_sub_pos_pos", test_sub_pos_pos);
    CU_add_test(suite, "test_bignum_sub_neg_neg", test_sub_neg_neg);
    CU_add_test(suite, "test_bignum_sub_neg_pos", test_sub_neg_pos);
    CU_add_test(suite, "test_bignum_sub_pos_neg", test_sub_pos_neg);
}
