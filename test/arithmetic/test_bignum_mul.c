#include <CUnit/CUnit.h>

#include "bignum.h"

void test_mul_zero_num() {
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    CU_ASSERT(compare_bignum(&a, &c) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_mul_num_zero() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("0");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    CU_ASSERT(compare_bignum(&b, &c) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_mul_simple() {
    bignum_t a = str2bignum("50");
    bignum_t b = str2bignum("50");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("2500");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_pos_pos() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_neg_pos() {
    bignum_t a = str2bignum("-18446744073709551615");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("-340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_pos_neg() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("-340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void test_mul_neg_neg() {
    bignum_t a = str2bignum("-18446744073709551615");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t c;
    mult_bignum(&c, &a, &b);
    bignum_t expected = str2bignum("340282366920938463426481119284349108225");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);
}

void bignum_mul_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_mul_zero_num", test_mul_zero_num);
    CU_add_test(suite, "test_bignum_mul_num_zero", test_mul_num_zero);
    CU_add_test(suite, "test_bignum_mul_simple", test_mul_simple);
    CU_add_test(suite, "test_bignum_mul_pos_pos", test_mul_pos_pos);
    CU_add_test(suite, "test_bignum_mul_neg_pos", test_mul_neg_pos);
    CU_add_test(suite, "test_bignum_mul_pos_neg", test_mul_pos_neg);
    CU_add_test(suite, "test_bignum_mul_neg_neg", test_mul_neg_neg);
}
