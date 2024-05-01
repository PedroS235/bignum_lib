#include <CUnit/CUnit.h>

#include "bignum/bignum.h"
#include "bignum/random.h"

void test_fermat_one() {
    bignum_t a = bignum_new();
    str2bignum(&a, "1");

    bool ret = fermat_test(a, 10);

    CU_ASSERT(!ret);

    free_bignum(&a);
}

void test_fermat_two() {
    bignum_t a = bignum_new();
    str2bignum(&a, "2");

    bool ret = fermat_test(a, 10);

    CU_ASSERT(ret);

    free_bignum(&a);
}

void test_fermat_three() {
    bignum_t a = bignum_new();
    str2bignum(&a, "3");

    bool ret = fermat_test(a, 10);

    CU_ASSERT(ret);

    free_bignum(&a);
}

void test_fermat_false() {
    bignum_t a = bignum_new();
    str2bignum(&a, "51");

    bool ret = fermat_test(a, 10);

    CU_ASSERT(!ret);

    free_bignum(&a);
}

void test_fermat_large() {
    bignum_t a = bignum_new();
    str2bignum(&a,
               "93942193193743265650981324976509183264091650918263409128365098321658324"
               "09821634242134213521359");

    bool ret = fermat_test(a, 10);

    CU_ASSERT(ret);

    free_bignum(&a);
}

void fermat_primality_tests(CU_pSuite suite) {
    CU_add_test(suite, "test_fermat_one", test_fermat_one);
    CU_add_test(suite, "test_fermat_two", test_fermat_two);
    CU_add_test(suite, "test_fermat_three", test_fermat_three);
    CU_add_test(suite, "test_fermat_false", test_fermat_false);
    CU_add_test(suite, "test_fermat_large", test_fermat_large);
}
