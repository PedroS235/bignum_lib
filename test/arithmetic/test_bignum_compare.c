#include <CUnit/CUnit.h>

#include "bignum.h"
#include "common.h"

void test_compare_zero() {
    bignum_t a;
    str2bignum(&a, "000000000000");
    bignum_t b = ZERO();
    print_bignum(&a);
    print_bignum(&b);
    CU_ASSERT(compare_bignum(&a, &b) == 0)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_equal_positive() {
    bignum_t a, b;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "18446744073709551615");
    CU_ASSERT(compare_bignum(&a, &b) == 0)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_equal_negative() {
    bignum_t a, b;
    str2bignum(&a, "-18446744073709551615");
    str2bignum(&b, "-18446744073709551615");
    CU_ASSERT(compare_bignum(&a, &b) == 0)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_greater_pos_pos() {
    bignum_t a, b;
    str2bignum(&a, "36893488147419103230");
    str2bignum(&b, "18446744073709551615");
    CU_ASSERT(compare_bignum(&a, &b) == 1)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_greater_pos_neg() {
    bignum_t a, b;
    str2bignum(&a, "36893488147419103230");
    str2bignum(&b, "-36893488147419103230");
    CU_ASSERT(compare_bignum(&a, &b) == 1)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_greater_neg_neg() {
    bignum_t a, b;
    str2bignum(&a, "-18446744073709551615");
    str2bignum(&b, "-36893488147419103230");
    CU_ASSERT(compare_bignum(&a, &b) == 1)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_smaller_pos_pos() {
    bignum_t a, b;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "36893488147419103230");
    CU_ASSERT(compare_bignum(&a, &b) == -1)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_smaller_neg_pos() {
    bignum_t a, b;
    str2bignum(&a, "-36893488147419103230");
    str2bignum(&b, "36893488147419103230");
    CU_ASSERT(compare_bignum(&a, &b) == -1)
    free_bignum(&a);
    free_bignum(&b);
}

void test_compare_smaller_neg_neg() {
    bignum_t a, b;
    str2bignum(&a, "-36893488147419103230");
    str2bignum(&b, "-18446744073709551615");
    CU_ASSERT(compare_bignum(&a, &b) == -1)
    free_bignum(&a);
    free_bignum(&b);
}

void bignum_compare_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_compare_zero", test_compare_zero);
    CU_add_test(suite, "test_compare_equal_positive", test_compare_equal_positive);
    CU_add_test(suite, "test_compare_equal_negative", test_compare_equal_negative);
    CU_add_test(suite, "test_compare_greater_pos_pos", test_compare_greater_pos_pos);
    CU_add_test(suite, "test_compare_greater_pos_neg", test_compare_greater_pos_neg);
    CU_add_test(suite, "test_compare_greater_neg_neg", test_compare_greater_neg_neg);
    CU_add_test(suite, "test_compare_smaller_pos_pos", test_compare_smaller_pos_pos);
    CU_add_test(suite, "test_compare_smaller_neg_pos", test_compare_smaller_neg_pos);
    CU_add_test(suite, "test_compare_smaller_neg_neg", test_compare_smaller_neg_neg);
}
