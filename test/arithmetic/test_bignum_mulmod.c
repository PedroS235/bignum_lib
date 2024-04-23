#include <CUnit/CUnit.h>

#include "common.h"
#include "modular_arithmetic.h"

void test_multmod_basic() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "10");
    str2bignum(&b, "20");
    str2bignum(&n, "55");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "35");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}
void test_multmod_modzero() {
    bignum_t a, b, n, c;
    str2bignum(&a, "34028236692093846342");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "0");
    int ret = multmod_bignum(&c, &a, &b, &n);
    CU_ASSERT(ret);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
}

void test_multmod_pos_pos_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "34028236692093846342");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_pos_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-3402823669209384634");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "736");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_neg_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "3402823669209384634");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "1042");
    multmod_bignum(&c, &a, &b, &n);
    print_bignum(&c);
    str2bignum(&expected, "736");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_neg_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-34028236692093846342");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_pos_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "34028236692093846342");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "-1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_pos_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-3402823669209384634");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "-1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "736");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_neg_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "3402823669209384634");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "-1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "736");
    CU_ASSERT(compare_bignum(&c, &expected) == 0);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_neg_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-34028236692093846342");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "-1042");
    multmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void bignum_multmod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_multmod_basic", test_multmod_basic);
    CU_add_test(suite, "test_multmod_modzero", test_multmod_modzero);
    CU_add_test(suite, "test_multmod_pos_pos_pos", test_multmod_pos_pos_pos);
    CU_add_test(suite, "test_multmod_neg_pos_pos", test_multmod_neg_pos_pos);
    CU_add_test(suite, "test_multmod_pos_neg_pos", test_multmod_pos_neg_pos);
    CU_add_test(suite, "test_multmod_neg_neg_pos", test_multmod_neg_neg_pos);
    CU_add_test(suite, "test_multmod_pos_pos_neg", test_multmod_pos_pos_neg);
    CU_add_test(suite, "test_multmod_neg_pos_neg", test_multmod_neg_pos_neg);
    CU_add_test(suite, "test_multmod_pos_neg_neg", test_multmod_pos_neg_neg);
    CU_add_test(suite, "test_multmod_neg_neg_neg", test_multmod_neg_neg_neg);
}
