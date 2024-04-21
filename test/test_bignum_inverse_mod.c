#include <CUnit/CUnit.h>

#include "arithmetic.h"
#include "bignum.h"

void test_inversemod_simple() {
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("18");
    bignum_t mod_inverse;
    inversemod(&mod_inverse, &a, &b);

    // To check the correctness of the inversemod, (mod_inverse * a) % b should be 1
    bignum_t product;
    mult_bignum(&product, &mod_inverse, &a);
    bignum_t remainder;
    bignum_remainder(&remainder, &product, &b);
    bignum_t one = str2bignum("1");
    CU_ASSERT(compare_bignum(&remainder, &one) == 0);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&product);
    free_bignum(&remainder);
    free_bignum(&one);
}

void bignum_inversemod_tests_to_suite(CU_pSuite suite) {
    CU_add_test(suite, "Inverse Mod Simple", test_inversemod_simple);
}
