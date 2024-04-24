#include "bignum/modular_arithmetic.h"

#include <stdio.h>

#include "bignum/arithmetic.h"
#include "bignum/bignum.h"
#include "bignum/common.h"

int bignum_mod(bignum_t *res, bignum_t *a, bignum_t *n) {
    bignum_t q = bignum_new();
    if (div_bignum(&q, res, a, n, true) != SUCCESS) {
        return FAILURE;
    }
    free_bignum(&q);
    return SUCCESS;
}

int addmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    int ret = add_bignum(res, a, b);
    if (ret != SUCCESS) return FAILURE;

    bignum_t tmp = bignum_new();
    if (bignum_mod(&tmp, res, n) != SUCCESS) {
        return FAILURE;
    }
    free_bignum(res);
    *res = tmp;

    return SUCCESS;
}

int multmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    if (mult_bignum(res, a, b) != SUCCESS) return FAILURE;

    bignum_t tmp = bignum_new();
    if (bignum_mod(&tmp, res, n) != SUCCESS) {
        return FAILURE;
    }
    free_bignum(res);
    *res = tmp;

    return SUCCESS;
}

int expmod(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    if (str2bignum(res, "1") != SUCCESS) return FAILURE;

    bignum_t base = bignum_new();
    if (copy_bignum(&base, a) != SUCCESS) return FAILURE;

    for (size_t i = 0; i < b->size; i++) {
        uint8_t bit = b->digits[i];
        if (bit) {
            bignum_t temp = bignum_new();
            if (multmod_bignum(&temp, res, &base, n) != SUCCESS) {
                free_bignum(&base);
                return FAILURE;
            }
            if (copy_bignum(res, &temp) != SUCCESS) {
                free_bignum(&base);
                free_bignum(&temp);
                return FAILURE;
            }
            free_bignum(&temp);
        }
        bignum_t temp = bignum_new();
        if (multmod_bignum(&temp, &base, &base, n) != SUCCESS) {
            free_bignum(&base);
            return FAILURE;
        }
        if (copy_bignum(&base, &temp) != SUCCESS) {
            free_bignum(&base);
            free_bignum(&temp);
            return FAILURE;
        }
        free_bignum(&temp);
    }

    free_bignum(&base);
    return SUCCESS;
}

int extended_gcd(bignum_t *res, bignum_t a, bignum_t b, bignum_t *x, bignum_t *y) {
    bignum_t a_1 = bignum_new();
    bignum_t b_1 = bignum_new();
    if (copy_bignum(&a_1, &a) != SUCCESS) return FAILURE;

    if (copy_bignum(&b_1, &b) != SUCCESS) {
        free_bignum(&a_1);
        return FAILURE;
    }

    bool negated_a = false, negated_b = false;
    bignum_t zero = ZERO();

    negated_a = abs_bignum(&a_1);
    negated_b = abs_bignum(&b_1);

    if (compare_bignum(&a_1, &zero) == 0) {
        free_bignum(&zero);
        if (str2bignum(x, "0") != SUCCESS) {
            free_bignum(&a_1);
            free_bignum(&b_1);
            return FAILURE;
        }
        if (str2bignum(y, "1") != SUCCESS) {
            free_bignum(&a_1);
            free_bignum(&b_1);
            return FAILURE;
        }

        if (negated_b) {
            y->sign = 1;
        }
        free_bignum(&a_1);
        *res = b_1;
        return SUCCESS;
    }

    bignum_t x1 = bignum_new();
    bignum_t y1 = bignum_new();
    bignum_t b_mod_a = bignum_new();
    if (bignum_mod(&b_mod_a, &b_1, &a_1) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        return FAILURE;
    }

    if (extended_gcd(res, b_mod_a, a_1, &x1, &y1) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        free_bignum(&b_mod_a);
        return FAILURE;
    }

    bignum_t q = bignum_new();
    bignum_t r = bignum_new();
    if (div_bignum(&q, &r, &b_1, &a_1, true) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        free_bignum(&x1);
        free_bignum(&y1);
        free_bignum(&b_mod_a);
        return FAILURE;
    }

    bignum_t tmp = bignum_new();
    if (mult_bignum(&tmp, &q, &x1) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        free_bignum(&x1);
        free_bignum(&y1);
        free_bignum(&q);
        free_bignum(&r);
        free_bignum(&b_mod_a);
        return FAILURE;
    }

    if (sub_bignum(x, &y1, &tmp) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        free_bignum(&x1);
        free_bignum(&y1);
        free_bignum(&q);
        free_bignum(&r);
        free_bignum(&b_mod_a);
        free_bignum(&tmp);
        return FAILURE;
    }

    free_bignum(&tmp);

    if (copy_bignum(y, &x1) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&a_1);
        free_bignum(&b_1);
        free_bignum(&x1);
        free_bignum(&y1);
        free_bignum(&q);
        free_bignum(&r);
        free_bignum(&b_mod_a);
        return FAILURE;
    }
    free_bignum(&x1);

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

    return SUCCESS;
}

int inversemod(bignum_t *res, bignum_t *a, bignum_t *n) {
    bignum_t x = bignum_new();
    bignum_t y = bignum_new();
    bignum_t a_normalized = bignum_new();
    bignum_t n_normalized = bignum_new();
    bignum_t one = ONE();
    bignum_t zero = ZERO();

    if (copy_bignum(&a_normalized, a) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&zero);
        return FAILURE;
    }

    abs_bignum(&a_normalized);

    if (copy_bignum(&n_normalized, n) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&zero);
        free_bignum(&a_normalized);
        return FAILURE;
    }

    abs_bignum(&n_normalized);

    bignum_t temp1 = bignum_new();
    // Compute extended gcd
    if (extended_gcd(&temp1, a_normalized, n_normalized, &x, &y) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&zero);
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        return FAILURE;
    }

    if (copy_bignum(res, &temp1) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&zero);
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        free_bignum(&x);
        free_bignum(&y);
        free_bignum(&temp1);
        return FAILURE;
    }
    free_bignum(&temp1);

    // Check if the gcd is 1
    if (compare_bignum(res, &one) == 0) {
        bignum_t temp = bignum_new();
        if (bignum_mod(&temp, &x, n) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&zero);
            free_bignum(&a_normalized);
            free_bignum(&n_normalized);
            free_bignum(&x);
            free_bignum(&y);
            return FAILURE;
        }
        int ret = copy_bignum(res, &temp);
        free_bignum(&temp);
        free_bignum(&y);
        free_bignum(&x);
        free_bignum(&one);
        free_bignum(&zero);
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        return ret;
    } else {
        fprintf(stderr, "Inverse does not exist since gcd(a, n) != 1\n");
        free_bignum(&a_normalized);
        free_bignum(&n_normalized);
        free_bignum(&x);
        free_bignum(&y);
        free_bignum(&one);
        free_bignum(&zero);
        return FAILURE;
    }
}
