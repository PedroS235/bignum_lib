#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

void test_div_by_zero() {
    bignum_t a = str2bignum("999999999999999999999");
    bignum_t b = str2bignum("0");
    bignum_t q, r;
    int ret = div_bignum(&q, &r, &a, &b, false);

    CU_ASSERT(ret);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
}

void test_div_simple() {
    bignum_t a = str2bignum("25");
    bignum_t b = str2bignum("3");
    bignum_t q;
    bignum_t r;
    div_bignum(&q, &r, &a, &b, false);

    bignum_t q_c = str2bignum("8");
    bignum_t r_c = str2bignum("1");

    CU_ASSERT(compare_bignum(&q_c, &q) == 0)
    CU_ASSERT(compare_bignum(&r_c, &r) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_pos_pos() {
    bignum_t a = str2bignum("32423423523423423433423");
    bignum_t b = str2bignum("2342342346767456");
    bignum_t q;
    bignum_t r;
    div_bignum(&q, &r, &a, &b, false);

    bignum_t q_c = str2bignum("13842307");
    bignum_t r_c = str2bignum("1660367839872431");

    CU_ASSERT(compare_bignum(&q_c, &q) == 0)
    CU_ASSERT(compare_bignum(&r_c, &r) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_neg_pos() {
    bignum_t a = str2bignum("-32423423523423423433423");
    bignum_t b = str2bignum("2342342346767456");
    bignum_t q;
    bignum_t r;
    div_bignum(&q, &r, &a, &b, false);

    bignum_t q_c = str2bignum("-13842307");
    bignum_t r_c = str2bignum("-1660367839872431");

    CU_ASSERT(compare_bignum(&q_c, &q) == 0)
    CU_ASSERT(compare_bignum(&r_c, &r) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_pos_neg() {
    bignum_t a = str2bignum("32423423523423423433423");
    bignum_t b = str2bignum("-2342342346767456");
    bignum_t q;
    bignum_t r;
    div_bignum(&q, &r, &a, &b, false);

    bignum_t q_c = str2bignum("-13842307");
    bignum_t r_c = str2bignum("1660367839872431");

    CU_ASSERT(compare_bignum(&q_c, &q) == 0)
    CU_ASSERT(compare_bignum(&r_c, &r) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void test_div_neg_neg() {
    bignum_t a = str2bignum("-32423423523423423433423");
    bignum_t b = str2bignum("-2342342346767456");
    bignum_t q;
    bignum_t r;
    div_bignum(&q, &r, &a, &b, false);

    bignum_t q_c = str2bignum("13842307");
    bignum_t r_c = str2bignum("-1660367839872431");

    CU_ASSERT(compare_bignum(&q_c, &q) == 0)
    CU_ASSERT(compare_bignum(&r_c, &r) == 0)

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&q_c);
    free_bignum(&r_c);
}

void bignum_div_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_div_by_zero", test_div_by_zero);
    CU_add_test(suite, "test_bignum_div_simple", test_div_simple);
    CU_add_test(suite, "test_bignum_div_pos_pos", test_div_pos_pos);
    CU_add_test(suite, "test_bignum_div_pos_neg", test_div_pos_neg);
    CU_add_test(suite, "test_bignum_div_neg_pos", test_div_neg_pos);
    CU_add_test(suite, "test_bignum_div_neg_neg", test_div_neg_neg);
}
