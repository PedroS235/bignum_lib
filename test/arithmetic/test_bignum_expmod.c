#include <CUnit/CUnit.h>

#include "common.h"
#include "modular_arithmetic.h"

void test_expmod_simple() {
    bignum_t base, exp, n, result, expected;
    str2bignum(&base, "2342");
    str2bignum(&exp, "6762");
    str2bignum(&n, "9343");
    expmod(&result, &base, &exp, &n);
    str2bignum(&expected, "7147");

    CU_ASSERT(compare_bignum(&expected, &result) == 0);

    free_bignum(&base);
    free_bignum(&exp);
    free_bignum(&n);
    free_bignum(&result);
    free_bignum(&expected);
}

void test_expmod_large() {
    bignum_t base, exp, n, result, expected;
    str2bignum(&base, "12345513512345552134123423");
    str2bignum(&exp, "33415533412333412341234");
    str2bignum(&n, "51234123412223413341341");
    expmod(&result, &base, &exp, &n);
    str2bignum(&expected, "19290576978205384361097");

    CU_ASSERT(compare_bignum(&expected, &result) == 0);

    free_bignum(&base);
    free_bignum(&exp);
    free_bignum(&n);
    free_bignum(&result);
    free_bignum(&expected);
}

void bignum_expmod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "test_bignum_expmod_simple", test_expmod_simple);
    CU_add_test(suite, "test_bignum_expmod_large", test_expmod_large);
}
