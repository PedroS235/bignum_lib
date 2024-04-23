#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "common.h"

void test_add_simple() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "50");
    str2bignum(&b, "40");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "90");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_pos_pos() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "18446744073709551615");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "36893488147419103230");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_pos_neg() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "-36893488147419103230");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "-18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_neg_pos() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "-18446744073709551615");
    str2bignum(&b, "36893488147419103230");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_neg_pos_2() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "-36893488147419103230");
    str2bignum(&b, "18446744073709551615");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "-18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_add_neg_neg() {
    bignum_t a, b, c, expected;
    str2bignum(&a, "-18446744073709551615");
    str2bignum(&b, "-18446744073709551615");
    add_bignum(&c, &a, &b);
    str2bignum(&expected, "-36893488147419103230");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_add_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_add_simple", test_add_simple);
    CU_add_test(suite, "test_bignum_add_pos_pos", test_add_pos_pos);
    CU_add_test(suite, "test_bignum_add_neg_neg", test_add_neg_neg);
    CU_add_test(suite, "test_bignum_add_pos_neg", test_add_pos_neg);
    CU_add_test(suite, "test_bignum_add_neg_pos", test_add_neg_pos);
    CU_add_test(suite, "test_bignum_add_neg_pos_2", test_add_neg_pos_2);
}
