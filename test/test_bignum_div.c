#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "core.h"

void test_div_basic() {
    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("5");
    div_result_t c = div_bignum(&a, &b);

    bignum_t q_c = str2bignum("2");
    bignum_t r_c = str2bignum("0");

    CU_ASSERT(compare_bignum(&q_c, &c.quotient) == 0)
    CU_ASSERT(compare_bignum(&r_c, &c.remainder) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_simple() {
    bignum_t a = str2bignum("25");
    bignum_t b = str2bignum("3");
    div_result_t c = div_bignum(&a, &b);

    bignum_t q_c = str2bignum("8");
    bignum_t r_c = str2bignum("1");

    CU_ASSERT(compare_bignum(&q_c, &c.quotient) == 0)
    CU_ASSERT(compare_bignum(&r_c, &c.remainder) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_max_uint64() {
    bignum_t a = str2bignum("32423423523423423433423");
    bignum_t b = str2bignum("2342342346767456");
    div_result_t c = div_bignum(&a, &b);

    bignum_t q_c = str2bignum("13842307");
    bignum_t r_c = str2bignum("1660367839872431");

    CU_ASSERT(compare_bignum(&q_c, &c.quotient) == 0)
    CU_ASSERT(compare_bignum(&r_c, &c.remainder) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_large() {
    bignum_t a = str2bignum("82374982374892374982739847293472983479283478237498");
    bignum_t b = str2bignum("9283748237458329758324792834729384");
    div_result_t c = div_bignum(&a, &b);

    bignum_t q_c = str2bignum("8873030619521053");
    bignum_t r_c = str2bignum("7430152715228522944387360532516146");

    CU_ASSERT(compare_bignum(&q_c, &c.quotient) == 0)
    CU_ASSERT(compare_bignum(&r_c, &c.remainder) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void bignum_div_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_div_basic", test_div_basic);
    CU_add_test(suite, "test_bignum_div_simple", test_div_simple);
    CU_add_test(suite, "test_bignum_div_max_uint64", test_div_max_uint64);
    CU_add_test(suite, "test_bignum_div_w_negative_large", test_div_large);
}
