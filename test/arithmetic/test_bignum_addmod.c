#include <CUnit/CUnit.h>

#include "bignum.h"

void test_addmod_basic() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("20");
    bignum_t n = str2bignum("4");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("2");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_modzero() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("0");
    bignum_t c;
    int ret = addmod_bignum(&c, &a, &b, &n);
    CU_ASSERT(ret);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
}

void test_addmod_pos_pos_pos() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("508");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_pos_pos() {
    bignum_t a = str2bignum("-340282366920938463426481119284349108225");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("818");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_neg_pos() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("-340282366920938463426481119284349108225");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("818");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_neg_pos() {
    bignum_t a = str2bignum("-340282366920938463426481119284349108225");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("534");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_pos_neg() {
    bignum_t a = str2bignum("34028236692093846342");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("349");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_neg_neg() {
    bignum_t a = str2bignum("-34028236692093846342");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("693");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_neg_pos_neg() {
    bignum_t a = str2bignum("-34028236692093846342");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("977");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_addmod_pos_neg_neg() {
    bignum_t a = str2bignum("18446744073709551615");
    bignum_t b = str2bignum("-34028236692093846342");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    addmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("977");
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
