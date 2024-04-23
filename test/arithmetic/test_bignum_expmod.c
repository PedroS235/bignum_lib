#include <CUnit/CUnit.h>

#include "bignum.h"

void test_expmod_simple() {
    bignum_t base = str2bignum("2342");
    bignum_t exp = str2bignum("6762");
    bignum_t n = str2bignum("9343");
    bignum_t result;
    expmod(&result, &base, &exp, &n);
    bignum_t expected = str2bignum("7147");

    CU_ASSERT(compare_bignum(&expected, &result) == 0);

    free_bignum(&base);
    free_bignum(&exp);
    free_bignum(&n);
    free_bignum(&result);
    free_bignum(&expected);
}

void test_expmod_large() {
    bignum_t base = str2bignum("12345513512345552134123423");
    bignum_t exp = str2bignum("33415533412333412341234");
    bignum_t n = str2bignum("51234123412223413341341");
    bignum_t result;
    expmod(&result, &base, &exp, &n);
    bignum_t expected = str2bignum("19290576978205384361097");

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
