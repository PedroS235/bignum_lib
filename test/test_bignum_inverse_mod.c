#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

void test_inversemod_simple() {
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("18");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);

    bignum_t expected = str2bignum("17");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_noinv() {
    bignum_t a = str2bignum("39");
    bignum_t b = str2bignum("9");
    bignum_t mod_inverse;
    int ret = inversemod(&mod_inverse, &a, &b);

    CU_ASSERT(ret);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
}

void test_inversemod_pos_pos() {
    bignum_t a = str2bignum("314234123421343243242134123");
    bignum_t b = str2bignum("3241234");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);
    bignum_t expected = str2bignum("1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_pos_neg() {
    bignum_t a = str2bignum("314234123421343243242134123");
    bignum_t b = str2bignum("-3241234");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);

    bignum_t expected = str2bignum("1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_neg_pos() {
    bignum_t a = str2bignum("-314234123421343243242134123");
    bignum_t b = str2bignum("3241234");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);

    bignum_t expected = str2bignum("1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_neg_neg() {
    bignum_t a = str2bignum("-314234123421343243242134123");
    bignum_t b = str2bignum("-3241234");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);

    bignum_t expected = str2bignum("1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void bignum_inversemod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_inversemod_simple", test_inversemod_simple);
    CU_add_test(suite, "test_inversemod_noinv", test_inversemod_noinv);
    CU_add_test(suite, "test_inversemod_pos_pos", test_inversemod_pos_pos);
    CU_add_test(suite, "test_inversemod_pos_neg", test_inversemod_pos_neg);
    CU_add_test(suite, "test_inversemod_neg_pos", test_inversemod_neg_pos);
    CU_add_test(suite, "test_inversemod_neg_neg", test_inversemod_neg_neg);
}
