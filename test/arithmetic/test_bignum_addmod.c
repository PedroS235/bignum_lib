#include <CUnit/CUnit.h>

#include "common.h"
#include "modular_arithmetic.h"

void test_addmod_basic() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "10");
    str2bignum(&b, "20");
    str2bignum(&n, "4");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "2");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_modzero() {
    bignum_t a, b, n, c;
    str2bignum(&a, "340282366920938463426481119284349108225");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "0");
    int ret = addmod_bignum(&c, &a, &b, &n);
    CU_ASSERT(ret);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
}

void test_addmod_pos_pos_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "340282366920938463426481119284349108225");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "508");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_pos_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-340282366920938463426481119284349108225");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "818");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_neg_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "-340282366920938463426481119284349108225");
    str2bignum(&n, "1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "818");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_neg_pos() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-340282366920938463426481119284349108225");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "534");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_pos_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "34028236692093846342");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "-1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "349");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_neg_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-34028236692093846342");
    str2bignum(&b, "-18446744073709551615");
    str2bignum(&n, "-1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "693");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_pos_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "-34028236692093846342");
    str2bignum(&b, "18446744073709551615");
    str2bignum(&n, "-1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "977");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_neg_neg() {
    bignum_t a, b, n, c, expected;
    str2bignum(&a, "18446744073709551615");
    str2bignum(&b, "-34028236692093846342");
    str2bignum(&n, "-1042");
    addmod_bignum(&c, &a, &b, &n);
    str2bignum(&expected, "977");
    CU_ASSERT(compare_bignum(&c, &expected) == 0);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void bignum_addmod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_addmod_basic", test_addmod_basic);
    CU_add_test(suite, "test_addmod_modzero", test_addmod_modzero);
    CU_add_test(suite, "test_addmod_pos_pos_pos", test_addmod_pos_pos_pos);
    CU_add_test(suite, "test_addmod_neg_pos_pos", test_addmod_neg_pos_pos);
    CU_add_test(suite, "test_addmod_pos_neg_pos", test_addmod_pos_neg_pos);
    CU_add_test(suite, "test_addmod_neg_neg_pos", test_addmod_neg_neg_pos);
    CU_add_test(suite, "test_addmod_pos_pos_neg", test_addmod_pos_pos_neg);
    CU_add_test(suite, "test_addmod_neg_neg_neg", test_addmod_neg_neg_neg);
    CU_add_test(suite, "test_addmod_neg_pos_neg", test_addmod_neg_pos_neg);
    CU_add_test(suite, "test_addmod_pos_neg_neg", test_addmod_pos_neg_neg);
}
