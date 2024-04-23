#include "modular_arithmetic.h"

#include <stdio.h>

#include "arithmetic.h"
#include "common.h"

int bignum_mod(bignum_t *res, bignum_t *a, bignum_t *n) {
    bignum_t q;
    int ret = div_bignum(&q, res, a, n, true);
    free_bignum(&q);
    if (ret) return 1;  // div failed
    return 0;
}

int addmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    int ret = add_bignum(res, a, b);
    if (ret) return ret;  // add failed

    bignum_t tmp;
    ret = bignum_mod(&tmp, res, n);
    free_bignum(res);
    *res = tmp;
    if (ret) return ret;  // mod failed

    return 0;
}

int multmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    int ret = mult_bignum(res, a, b);
    if (ret) return ret;  // mult failed

    // Then, calculate the remainder of product divided by n
    bignum_t tmp;
    ret = bignum_mod(&tmp, res, n);
    free_bignum(res);
    *res = tmp;
    if (ret) return ret;  // remainder failed

    return 0;
}

int expmod(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    int ret = init_bignum_(res, 1, POS);
    if (ret) return ret;  // init failed
    res->digits[0] = 1;   // Initialize result to 1

    bignum_t base;
    copy_bignum(&base, a);

    size_t i;
    for (i = 0; i < b->size; i++) {
        uint8_t bit = b->digits[i];
        if (bit) {
            bignum_t temp;
            multmod_bignum(&temp, res, &base, n);
            free_bignum(res);
            *res = temp;
        }
        bignum_t temp;
        multmod_bignum(&temp, &base, &base, n);
        free_bignum(&base);
        base = temp;
    }

    free_bignum(&base);
    return 0;
}

int extended_gcd(bignum_t *res, bignum_t a, bignum_t b, bignum_t *x, bignum_t *y) {
    int ret;
    bignum_t a_1, b_1;
    copy_bignum(&a_1, &a);
    copy_bignum(&b_1, &b);

    bool negated_a = false, negated_b = false;
    bignum_t zero = ZERO();

    negated_a = abs_bignum(&a_1);
    negated_b = abs_bignum(&b_1);

    if (compare_bignum(&a_1, &zero) == 0) {
        free_bignum(&zero);
        str2bignum_(x, "0");
        str2bignum_(y, "1");
        if (negated_b) {
            y->sign = 1;
        }
        free_bignum(&a_1);
        *res = b_1;
        return 0;
    }

    bignum_t x1, y1;
    bignum_t b_mod_a;
    bignum_mod(&b_mod_a, &b_1, &a_1);
    ret = extended_gcd(res, b_mod_a, a_1, &x1, &y1);
    if (ret) return ret;

    bignum_t q, r;
    div_bignum(&q, &r, &b_1, &a_1, true);

    bignum_t tmp;
    mult_bignum(&tmp, &q, &x1);
    sub_bignum(x, &y1, &tmp);
    free_bignum(&tmp);

    *y = x1;

    if (negated_a) {
        x->sign = 1;
    }
    if (negated_b) {
        y->sign = 0;
    }

    free_bignum(&zero);
    free_bignum(&q);
    free_bignum(&r);
    free_bignum(&y1);
    free_bignum(&a_1);
    free_bignum(&b_1);
    free_bignum(&b_mod_a);

    return 0;
}

int inversemod(bignum_t *res, bignum_t *a, bignum_t *n) {
    bignum_t x, y, a_normalized, n_normalized;
    bignum_t one = ONE();
    bignum_t zero = ZERO();

    // Normalize a and n to be positive
    copy_bignum(&a_normalized, a);
    abs_bignum(&a_normalized);

    copy_bignum(&n_normalized, n);
    abs_bignum(&n_normalized);

    bignum_t temp1;
    // Compute extended gcd
    int ret = extended_gcd(&temp1, a_normalized, n_normalized, &x, &y);
    copy_bignum(res, &temp1);
    free_bignum(&temp1);
    if (ret) return ret;

    // Check if the gcd is 1
    if (compare_bignum(res, &one) == 0) {
        bignum_t temp;
        bignum_mod(&temp, &x, n);  // Reduce modulo n to ensure within range
        free_bignum(res);
        *res = temp;  // Store the corrected x as result
        free_bignum(&y);
        free_bignum(&x);
        free_bignum(&one);
        free_bignum(&zero);
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        return 0;
    } else {
        fprintf(stderr, "Inverse does not exist since gcd(a, n) != 1\n");
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        free_bignum(&x);
        free_bignum(&y);
        free_bignum(&one);
        free_bignum(&zero);
        return 1;
    }
}
