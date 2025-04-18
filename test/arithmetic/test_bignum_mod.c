#include <CUnit/CUnit.h>

#include "bignum/bignum.h"
#include "bignum/common.h"
#include "bignum/modular_arithmetic.h"

void test_mod_simple() {
    bignum_t a = ZERO();
    bignum_t b = bignum_new();
    bignum_t c = bignum_new();
    bignum_t r_c = bignum_new();
    str2bignum(&b, "99999999999999");
    bignum_mod(&c, &a, &b);
    str2bignum(&r_c, "0");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_zero_divisor() {
    bignum_t a = bignum_new();
    bignum_t c = bignum_new();
    str2bignum(&a, "99999999999");
    bignum_t b = ZERO();
    int ret = bignum_mod(&c, &a, &b);

    CU_ASSERT(ret);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_mod_pos_pos() {
    bignum_t a = bignum_new();
    bignum_t b = bignum_new();
    bignum_t c = bignum_new();
    bignum_t r_c = bignum_new();
    str2bignum(&a, "55931291235123512515151");
    str2bignum(&b, "12316543");
    bignum_mod(&c, &a, &b);
    str2bignum(&r_c, "4620713");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_neg_pos() {
    bignum_t a = bignum_new();
    bignum_t b = bignum_new();
    bignum_t c = bignum_new();
    bignum_t r_c = bignum_new();
    str2bignum(&a, "-55931291235123512515151");
    str2bignum(&b, "12316543");
    bignum_mod(&c, &a, &b);
    str2bignum(&r_c, "7695830");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_pos_neg() {
    bignum_t a = bignum_new();
    bignum_t b = bignum_new();
    bignum_t c = bignum_new();
    bignum_t r_c = bignum_new();
    str2bignum(&a, "55931291235123512515151");
    str2bignum(&b, "-12316543");
    bignum_mod(&c, &a, &b);

    str2bignum(&r_c, "4620713");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_neg_neg() {
    bignum_t a = bignum_new();
    bignum_t b = bignum_new();
    bignum_t c = bignum_new();
    bignum_t r_c = bignum_new();
    str2bignum(&a, "-55931291235123512515151");
    str2bignum(&b, "-12316543");
    bignum_mod(&c, &a, &b);
    str2bignum(&r_c, "7695830");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void bignum_mod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_mod", test_mod_simple);
    CU_add_test(suite, "test_bignum_mod_zero_divisor", test_mod_zero_divisor);
    CU_add_test(suite, "test_bignum_mod_pos_pos", test_mod_pos_pos);
    CU_add_test(suite, "test_bignum_mod_neg_pos", test_mod_neg_pos);
    CU_add_test(suite, "test_bignum_mod_pos_neg", test_mod_pos_neg);
    CU_add_test(suite, "test_bignum_mod_neg_neg", test_mod_neg_neg);
}
