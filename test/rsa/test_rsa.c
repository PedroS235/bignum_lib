#include <CUnit/CUnit.h>

#include "bignum/bignum.h"
#include "bignum/common.h"
#include "bignum/random.h"
#include "rsa.h"

void test_rsa_small() {
    init_seed();

    bignum_t n = bignum_new();
    bignum_t e = bignum_new();
    bignum_t d = bignum_new();

    rsa_keygen(&n, &e, &d, 20);

    bignum_t m = bignum_new();
    str2bignum(&m, "1234567890");

    bignum_t c = bignum_new();
    rsa_encrypt(&c, &m, &n, &e);

    bignum_t decrypted = bignum_new();
    rsa_decrypt(&decrypted, &c, &n, &d);

    CU_ASSERT(compare_bignum(&decrypted, &m) == 0)

    free_bignum(&n);
    free_bignum(&e);
    free_bignum(&d);
    free_bignum(&m);
    free_bignum(&c);
    free_bignum(&decrypted);
}

void test_rsa_large() {
    init_seed();

    bignum_t n = bignum_new();
    bignum_t e = bignum_new();
    bignum_t d = bignum_new();

    rsa_keygen(&n, &e, &d, 256);

    bignum_t m = bignum_new();
    str2bignum(&m, "1234567890123141515070815124312");

    bignum_t c = bignum_new();
    rsa_encrypt(&c, &m, &n, &e);

    bignum_t decrypted = bignum_new();
    rsa_decrypt(&decrypted, &c, &n, &d);

    CU_ASSERT(compare_bignum(&decrypted, &m) == 0)

    free_bignum(&n);
    free_bignum(&e);
    free_bignum(&d);
    free_bignum(&m);
    free_bignum(&c);
    free_bignum(&decrypted);
}

void rsa_tests(CU_pSuite suite) {
    CU_add_test(suite, "test_rsa_small", test_rsa_small);
    CU_add_test(suite, "test_rsa_large", test_rsa_large);
}
