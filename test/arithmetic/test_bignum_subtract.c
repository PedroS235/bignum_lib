#include <CUnit/CUnit.h>

#include "bignum.h"

void test_sub_simple() {
    bignum_t a = str2bignum("50");
    bignum_t b = str2bignum("40");
    bignum_t c;
    sub_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("10");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_pos_pos() {
    bignum_t a = str2bignum("36893488147419103230");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c;
    sub_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_neg_neg() {
    bignum_t a = str2bignum("-36893488147419103230");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c;
    sub_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("-18446744073709551615");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_neg_pos() {
    bignum_t a = str2bignum("-36893488147419103230");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c;
    sub_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("-55340232221128654845");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_sub_pos_neg() {
    bignum_t a = str2bignum("36893488147419103230");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c;
    sub_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("55340232221128654845");
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
