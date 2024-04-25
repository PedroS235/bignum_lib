#include "bignum/arithmetic.h"

#include <stdio.h>

#include "bignum/bignum.h"
#include "bignum/bitwise.h"
#include "bignum/common.h"

bool abs_bignum(bignum_t *n) {
    bool is_negative = false;
    if (n->sign == NEG) {
        n->sign = POS;
        is_negative = true;
    }
    return is_negative;
}

int add_bignum(bignum_t *res, bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        if (compare_bignum_unsigned(a, b) >= 0) {
            int ret = sub_bignum_unsigned(res, a, b);
            if (ret != SUCCESS) return FAILURE;
            res->sign = a->sign;
            return SUCCESS;
        } else {
            int ret = sub_bignum_unsigned(res, b, a);
            if (ret != SUCCESS) return FAILURE;
            res->sign = b->sign;
            return SUCCESS;
        }
    }

    return add_bignum_unsigned(res, a, b);
}

int add_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    int ret = init_bignum(res, size + 1, a->sign);
    if (ret != SUCCESS) return FAILURE;

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];

        res->digits[i] = sum % BASE;
        carry = sum / BASE;
    }

    if (carry) {
        res->digits[size] = carry;
    } else {
        res->size = size;
    }
    return SUCCESS;
}

int sub_bignum(bignum_t *res, bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        if (compare_bignum(a, b) < 0) {
            b->sign = a->sign;
        }
        return add_bignum_unsigned(res, a, b);
    }
    // Same signs
    if (compare_bignum_unsigned(a, b) >= 0) {
        int ret = sub_bignum_unsigned(res, a, b);
        if (ret != SUCCESS) return FAILURE;
        res->sign = a->sign;
        return SUCCESS;
    } else {
        int ret = sub_bignum_unsigned(res, b, a);
        if (ret != SUCCESS) return FAILURE;
        res->sign = 1 - a->sign;
        return SUCCESS;
    }
}

int sub_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    int ret = init_bignum(res, size, POS);
    if (ret != SUCCESS) return FAILURE;

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum -= b->digits[i];

        if (sum < 0) {
            sum += BASE;
            carry = -1;
        } else {
            carry = 0;
        }

        res->digits[i] = sum;
    }

    trim_leading_zeros_bignum(res);

    return SUCCESS;
}

int mult_bignum(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size + b->size;

    int ret = init_bignum(res, size, a->sign ^ b->sign);
    if (ret != SUCCESS) return FAILURE;

    for (size_t i = 0; i < a->size; i++) {
        int carry = 0;
        for (size_t j = 0; j < b->size; j++) {
            int sum = a->digits[i] * b->digits[j] + res->digits[i + j] + carry;
            res->digits[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        res->digits[i + b->size] = carry;
    }

    trim_leading_zeros_bignum(res);

    return SUCCESS;
}

int div_bignum(bignum_t *q, bignum_t *r, bignum_t *a, bignum_t *b, bool pos_remainder) {
    bignum_t zero = ZERO();
    if (compare_bignum(b, &zero) == 0) {
        *q = ZERO();
        *r = ZERO();
        free_bignum(q);
        free_bignum(r);
        free_bignum(&zero);
        fprintf(stderr, "Division by zero in div_bignum(...)\n");
        return DIVISION_BY_ZERO;
    }

    if (init_bignum(q, a->size, a->sign ^ b->sign) != SUCCESS) return FAILURE;

    if (copy_bignum(r, a) != SUCCESS) return FAILURE;

    int shift = a->size - b->size;

    bignum_t shifted_b = bignum_new();
    if (copy_bignum(&shifted_b, b) != SUCCESS) return FAILURE;
    if (binary_shift(&shifted_b, shift) != SUCCESS) return FAILURE;

    while (shift >= 0) {
        if (compare_bignum_unsigned(r, &shifted_b) >= 0) {
            bignum_t temp_r = bignum_new();
            if (sub_bignum_unsigned(&temp_r, r, &shifted_b) != SUCCESS) {
                free_bignum(&zero);
                free_bignum(&shifted_b);
                return FAILURE;
            }
            if (copy_bignum(r, &temp_r) != SUCCESS) {
                free_bignum(&zero);
                free_bignum(&shifted_b);
                return FAILURE;
            }
            free_bignum(&temp_r);
            q->digits[shift] = 1;
        } else {
            q->digits[shift] = 0;
        }

        shift--;
        if (binary_shift(&shifted_b, -1) != SUCCESS) {
            free_bignum(&zero);
            free_bignum(&shifted_b);
            return FAILURE;
        }
    }

    // Correct signs based on input signs
    q->sign = a->sign ^ b->sign;
    r->sign = a->sign;

    bignum_t tmp_b = bignum_new();
    if (copy_bignum(&tmp_b, b) != SUCCESS) {
        free_bignum(&zero);
        free_bignum(&shifted_b);
        return FAILURE;
    }
    abs_bignum(&tmp_b);

    // Ensure the remainder is non-negative
    while (r->sign > 0 && pos_remainder) {
        bignum_t adjusted_remainder = bignum_new();
        if (add_bignum(&adjusted_remainder, r, &tmp_b) != SUCCESS) {
            free_bignum(&zero);
            free_bignum(&shifted_b);
            return FAILURE;
        }
        if (copy_bignum(r, &adjusted_remainder) != SUCCESS) {
            free_bignum(&zero);
            free_bignum(&shifted_b);
            free_bignum(&tmp_b);
            return FAILURE;
        }
        free_bignum(&adjusted_remainder);
    }

    trim_leading_zeros_bignum(q);
    trim_leading_zeros_bignum(r);
    free_bignum(&zero);
    free_bignum(&tmp_b);
    free_bignum(&shifted_b);
    return SUCCESS;
}
