#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_multmod_basic() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("20");
    bignum_t n = str2bignum("55");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("35");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}
void test_multmod_modzero() {
    bignum_t a = str2bignum("34028236692093846342");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("0");
    bignum_t c;
    int ret = multmod_bignum(&c, &a, &b, &n);
    CU_ASSERT(ret);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
}

void test_multmod_pos_pos_pos() {
    bignum_t a = str2bignum("34028236692093846342");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_pos_pos() {
    bignum_t a = str2bignum("-3402823669209384634");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("824");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_neg_pos() {
    bignum_t a = str2bignum("3402823669209384634");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("824");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_neg_pos() {
    bignum_t a = str2bignum("-34028236692093846342");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_pos_neg() {
    bignum_t a = str2bignum("34028236692093846342");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("-824");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_pos_neg() {
    bignum_t a = str2bignum("-3402823669209384634");
    bignum_t b = str2bignum("18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("-218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_pos_neg_neg() {
    bignum_t a = str2bignum("3402823669209384634");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("-218");
    CU_ASSERT(compare_bignum(&c, &expected) == 0);
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);
}

void test_multmod_neg_neg_neg() {
    bignum_t a = str2bignum("-34028236692093846342");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("-1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    bignum_t expected = str2bignum("-824");
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
