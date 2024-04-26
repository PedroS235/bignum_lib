#include "rsa.h"

#include "bignum/arithmetic.h"
#include "bignum/common.h"
#include "bignum/modular_arithmetic.h"
#include "bignum/random.h"

int rsa_keygen(bignum_t *n, bignum_t *e, bignum_t *d, int length) {
    bignum_t p = bignum_new();
    bignum_t q = bignum_new();
    bignum_t phi = bignum_new();
    bignum_t one = ONE();

    gen_random_prime(&p, length);
    gen_random_prime(&q, length);

    while (compare_bignum(&p, &q) == 0) {
        free_bignum(&q);
        gen_random_prime(&q, length);
    }

    if (mult_bignum(n, &p, &q) != SUCCESS) {
        return FAILURE;
    }

    bignum_t p_minus_1 = bignum_new();
    bignum_t q_minus_1 = bignum_new();
    if (sub_bignum(&p_minus_1, &p, &one) != SUCCESS) return FAILURE;
    if (sub_bignum(&q_minus_1, &q, &one) != SUCCESS) return FAILURE;

    if (mult_bignum(&phi, &p_minus_1, &q_minus_1) != SUCCESS) return FAILURE;

    if (gen_random_coprime(e, &phi) != SUCCESS) return FAILURE;
    if (inversemod(d, e, &phi) != SUCCESS) return FAILURE;

    free_bignum(&p);
    free_bignum(&q);
    free_bignum(&phi);
    free_bignum(&one);
    free_bignum(&p_minus_1);
    free_bignum(&q_minus_1);

    return SUCCESS;
}

int rsa_encrypt(bignum_t *c, bignum_t *m, bignum_t *n, bignum_t *e) {
    return expmod(c, m, e, n);
}

int rsa_decrypt(bignum_t *m, bignum_t *c, bignum_t *n, bignum_t *d) {
    return expmod(m, c, d, n);
}
