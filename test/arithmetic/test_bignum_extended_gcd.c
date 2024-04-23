#include <CUnit/CUnit.h>

#include "common.h"
#include "modular_arithmetic.h"

void test_extended_gcd_pos_pos_simple() {
    bignum_t a, b, x, y, gcd, expected_gcd, expected_x, expected_y;
    str2bignum(&a, "35");
    str2bignum(&b, "15");
    extended_gcd(&gcd, a, b, &x, &y);
    str2bignum(&expected_gcd, "5");
    str2bignum(&expected_x, "1");
    str2bignum(&expected_y, "-2");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);
}

void test_extended_gcd_pos_pos() {
    bignum_t a, b, x, y, gcd, expected_gcd, expected_x, expected_y;
    str2bignum(&a, "334212341355133416799837891234");
    str2bignum(&b, "6431434556123412341123412");
    extended_gcd(&gcd, a, b, &x, &y);
    str2bignum(&expected_gcd, "2");
    str2bignum(&expected_x, "1522489363060904105881595");
    str2bignum(&expected_y, "-79116833153873196738571871969");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);
}

void test_extended_gcd_neg_neg() {
    bignum_t a, b, x, y, gcd, expected_gcd, expected_x, expected_y;
    str2bignum(&a, "-35");
    str2bignum(&b, "-15");
    extended_gcd(&gcd, a, b, &x, &y);
    str2bignum(&expected_gcd, "5");
    str2bignum(&expected_x, "-1");
    str2bignum(&expected_y, "2");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);
}

void test_extended_gcd_neg_pos() {
    bignum_t a, b, x, y, gcd, expected_gcd, expected_x, expected_y;
    str2bignum(&a, "-100");
    str2bignum(&b, "40");
    extended_gcd(&gcd, a, b, &x, &y);
    str2bignum(&expected_gcd, "20");
    str2bignum(&expected_x, "-1");
    str2bignum(&expected_y, "-2");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);
}

void test_extended_gcd_pos_neg() {
    bignum_t a, b, x, y, gcd, expected_gcd, expected_x, expected_y;
    str2bignum(&a, "100");
    str2bignum(&b, "-40");
    extended_gcd(&gcd, a, b, &x, &y);
    str2bignum(&expected_gcd, "20");
    str2bignum(&expected_x, "1");
    str2bignum(&expected_y, "2");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);
}

void bignum_extended_gcd_tests_to_suite(CU_pSuite suite) {
    CU_add_test(
        suite, "test_extended_gcd_pos_pos_simple", test_extended_gcd_pos_pos_simple);
    CU_add_test(suite, "test_extended_gcd_pos_pos", test_extended_gcd_pos_pos);
    CU_add_test(suite, "test_extended_gcd_neg_neg", test_extended_gcd_neg_neg);
    CU_add_test(suite, "test_extended_gcd_neg_pos_simple", test_extended_gcd_neg_pos);
    CU_add_test(suite, "test_extended_gcd_pos_neg_simple", test_extended_gcd_pos_neg);
}
