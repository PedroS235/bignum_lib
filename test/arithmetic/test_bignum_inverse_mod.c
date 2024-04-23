#include <CUnit/CUnit.h>

#include "common.h"
#include "modular_arithmetic.h"

void test_inversemod_simple() {
    bignum_t a, b, mod_inverse;
    str2bignum(&a, "35");
    str2bignum(&b, "18");
    inversemod(&mod_inverse, &a, &b);

    bignum_t expected;
    str2bignum(&expected, "17");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_noinv() {
    bignum_t a, b, mod_inverse;
    str2bignum(&a, "39");
    str2bignum(&b, "9");
    int ret = inversemod(&mod_inverse, &a, &b);

    CU_ASSERT(ret);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
}

void test_inversemod_pos_pos() {
    bignum_t a, b, mod_inverse, expected;
    str2bignum(&a, "314234123421343243242134123");
    str2bignum(&b, "3241234");
    inversemod(&mod_inverse, &a, &b);
    str2bignum(&expected, "1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_pos_neg() {
    bignum_t a, b, mod_inverse, expected;
    str2bignum(&a, "314234123421343243242134123");
    str2bignum(&b, "-3241234");
    inversemod(&mod_inverse, &a, &b);
    str2bignum(&expected, "1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_neg_pos() {
    bignum_t a, b, mod_inverse, expected;
    str2bignum(&a, "-314234123421343243242134123");
    str2bignum(&b, "3241234");
    inversemod(&mod_inverse, &a, &b);

    str2bignum(&expected, "1498259");

    CU_ASSERT(compare_bignum(&mod_inverse, &expected) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&expected);
}

void test_inversemod_neg_neg() {
    bignum_t a, b, mod_inverse, expected;
    str2bignum(&a, "-314234123421343243242134123");
    str2bignum(&b, "-3241234");
    inversemod(&mod_inverse, &a, &b);

    str2bignum(&expected, "1498259");

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
