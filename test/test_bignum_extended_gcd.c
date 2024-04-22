#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

void test_extended_gcd_pos_pos_simple() {
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("15");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("5");
    bignum_t expected_x = str2bignum("1");
    bignum_t expected_y = str2bignum("-2");

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

void test_extended_gcd_large() {
    bignum_t a = str2bignum("334212341355133416799837891234");
    bignum_t b = str2bignum("6431434556123412341123412");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("2");
    bignum_t expected_x = str2bignum("1522489363060904105881595");
    bignum_t expected_y = str2bignum("-79116833153873196738571871969");

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

void test_extended_gcd_neg_pos_simple() {
    bignum_t a = str2bignum("-100");
    bignum_t b = str2bignum("40");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("20");
    bignum_t expected_x = str2bignum("-1");
    bignum_t expected_y = str2bignum("-2");

    print_bignum(&gcd);
    print_bignum(&x);
    print_bignum(&y);

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

void test_extended_gcd_pos_neg_simple() {
    bignum_t a = str2bignum("100");
    bignum_t b = str2bignum("-40");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("20");
    bignum_t expected_x = str2bignum("1");
    bignum_t expected_y = str2bignum("2");

    CU_ASSERT(compare_bignum(&gcd, &expected_gcd) == 0);
    CU_ASSERT(compare_bignum(&x, &expected_x) == 0);
    CU_ASSERT(compare_bignum(&y, &expected_y) == 0);

    print_bignum(&gcd);
    print_bignum(&x);
    print_bignum(&y);

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
    CU_add_test(suite, "test_extended_gcd_large", test_extended_gcd_large);
    CU_add_test(
        suite, "test_extended_gcd_neg_pos_simple", test_extended_gcd_neg_pos_simple);
    CU_add_test(
        suite, "test_extended_gcd_pos_neg_simple", test_extended_gcd_pos_neg_simple);
}
