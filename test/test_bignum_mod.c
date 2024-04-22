#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_mod_simple() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("4");
    bignum_t c;
    bignum_mod(&c, &a, &b);
    bignum_t r_c = str2bignum("2");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_negative() {
    bignum_t a = str2bignum("-10");
    bignum_t b = str2bignum("4");
    bignum_t c;
    bignum_mod(&c, &a, &b);
    bignum_t r_c = str2bignum("2");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_zero() {
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("4");
    bignum_t c;
    bignum_mod(&c, &a, &b);
    bignum_t r_c = str2bignum("0");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void test_mod_zero_divisor() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("0");
    bignum_t c;
    int ret = bignum_mod(&c, &a, &b);

    CU_ASSERT(ret);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
}

void test_mod_large() {
    bignum_t a = str2bignum("340282366920938463426481119284349108225");
    bignum_t b = str2bignum("1042");
    bignum_t c;
    bignum_mod(&c, &a, &b);
    bignum_t r_c = str2bignum("887");

    CU_ASSERT(compare_bignum(&c, &r_c) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
}

void bignum_mod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_mod", test_mod_simple);
    CU_add_test(suite, "test_bignum_mod_negative", test_mod_negative);
    CU_add_test(suite, "test_bignum_mod_zero", test_mod_zero);
    CU_add_test(suite, "test_bignum_mod_zero_divisor", test_mod_zero_divisor);
    CU_add_test(suite, "test_bignum_mod_large", test_mod_large);
}
