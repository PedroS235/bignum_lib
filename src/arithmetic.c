#include "arithmetic.h"

#include <stdio.h>

#include "bignum.h"
#include "config.h"
#include "utils.h"
#include "stdbool.h"

int compare_bignum(bignum_t *a, bignum_t *b) {
    // First, compare signs
    if (a->sign != b->sign) {
        return a->sign > b->sign ? -1 : 1;
    }

    // Sign is the same: compare sizes
    if (a->size != b->size) {
        if (a->sign == 0) {  // both non-negative
            return a->size > b->size ? 1 : -1;
        } else {  // both negative
            return a->size > b->size ? -1 : 1;
        }
    }

    // Same sign and size: compare digits from most significant
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            return (a->digits[i] > b->digits[i]) ? (a->sign == 0 ? 1 : -1)
                                                 : (a->sign == 0 ? -1 : 1);
        }
    }

    // All digits are the same
    return 0;
}

int compare_bignum_unsigned(bignum_t *a, bignum_t *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

int add_bignum(bignum_t *res, bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        if (compare_bignum_unsigned(a, b) >= 0) {
            sub_bignum_unsigned(res, a, b);
            res->sign = a->sign;
            return 0;
        } else {
            sub_bignum_unsigned(res, b, a);
            res->sign = b->sign;
            return 0;
        }
    }

    return add_bignum_unsigned(res, a, b);
}

int add_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    int ret = init_bignum_(res, size + 1, a->sign);
    if (ret) return ret;  // init failed

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
    return 0;
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
        res->sign = a->sign;
        return ret;
    } else {
        int ret = sub_bignum_unsigned(res, b, a);
        res->sign = 1 - a->sign;
        return ret;
    }
}

int sub_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    int ret = init_bignum_(res, size, POS);
    if (ret) return ret;  // init failed

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

    while (res->size > 1 && res->digits[res->size - 1] == 0) {
        res->size--;
    }

    return 0;
}

int mult_bignum(bignum_t *res, bignum_t *a, bignum_t *b) {
    size_t size = a->size + b->size;

    int ret = init_bignum_(res, size, a->sign ^ b->sign);
    if (ret) return ret;  // init failed

    for (size_t i = 0; i < a->size; i++) {
        int carry = 0;
        for (size_t j = 0; j < b->size; j++) {
            int sum = a->digits[i] * b->digits[j] + res->digits[i + j] + carry;
            res->digits[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        res->digits[i + b->size] = carry;
    }

    while (res->size > 1 && res->digits[res->size - 1] == 0) {
        res->size--;
    }

    return 0;
}

int div_bignum(bignum_t *q, bignum_t *r, bignum_t *a, bignum_t *b) {
    bignum_t zero = str2bignum("0");
    if (compare_bignum(b, &zero) == 0) {
        fprintf(stderr, "Division by zero in div_bignum(...)\n");
        return 1;
    }

    int ret1 = init_bignum_(q, a->size, a->sign ^ b->sign);
    if (ret1) return 1;  // init failed
    copy_bignum(r, a);

    int shift = a->size - b->size;

    bignum_t shifted_b = binary_shift(*b, shift);

    while (shift >= 0) {
        if (compare_bignum_unsigned(r, &shifted_b) >= 0) {
            bignum_t temp_r;
            int ret = sub_bignum_unsigned(&temp_r, r, &shifted_b);
            if (ret) {
                free_bignum(&zero);
                free_bignum(&shifted_b);
                return ret;
            }  // sub failed
            free_bignum(r);
            *r = temp_r;
            q->digits[shift] = 1;
        } else {
            q->digits[shift] = 0;
        }

        shift--;
        bignum_t shifted_temp = binary_shift(shifted_b, -1);
        free_bignum(&shifted_b);
        shifted_b = shifted_temp;
    }

    // Correct signs based on input signs
    q->sign = a->sign ^ b->sign;
    r->sign = a->sign;

    // Ensure the remainder is non-negative
    if (r->sign > 0) {
        bignum_t adjusted_remainder;
        int ret = add_bignum(&adjusted_remainder, r, b);
        if (ret) {
            free_bignum(&zero);
            free_bignum(&shifted_b);
            return ret;
        }  // sub failed
        free_bignum(r);
        *r = adjusted_remainder;
    }

    trim_leading_zeros_bignum(q);
    trim_leading_zeros_bignum(r);
    free_bignum(&zero);
    free_bignum(&shifted_b);
    return 0;
}

int bignum_mod(bignum_t *res, bignum_t *a, bignum_t *n) {
    bignum_t q;
    int ret = div_bignum(&q, res, a, n);
    if (ret) return 1;  // div failed
    free_bignum(&q);
    return 0;
}

int addmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    // First, add a and b
    int ret = add_bignum(res, a, b);
    if (ret) return ret;  // add failed

    bignum_t tmp;
    bignum_mod(&tmp, res, n);
    free_bignum(res);
    *res = tmp;

    return 0;
}

int multmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n) {
    int ret = mult_bignum(res, a, b);
    if (ret) return ret;  // mult failed

    // Then, calculate the remainder of product divided by n
    bignum_t tmp;
    ret = bignum_mod(&tmp, res, n);
    if (ret) return ret;  // remainder failed
    free_bignum(res);
    *res = tmp;

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
    bignum_t zero;
    str2bignum_(&zero, "0");
    
    // Normalize a
    if (compare_bignum(&a_1, &zero) < 0) {
        a_1.sign = 0;
        negated_a = true;
    }
    
    // Normalize b
    if (compare_bignum(&b_1, &zero) < 0) {
        b_1.sign = 0;
        negated_b = true;
    }

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
    div_bignum(&q, &r, &b_1, &a_1);

    bignum_t tmp;
    mult_bignum(&tmp, &q, &x1);
    sub_bignum(x, &y1, &tmp);
    free_bignum(&tmp);

    *y = x1;

    if (negated_a) {
        x->sign = 1;  
    }
    if (negated_b) {
        y ->sign = 0;  
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
    bignum_t x;
    bignum_t y;
    int ret = extended_gcd(res, *a, *n, &x, &y);
    if (ret) return ret;  // extended gcd failed

    bignum_t one;
    ret = str2bignum_(&one, "1");
    if (ret) return ret;  // init failed

    if (compare_bignum(res, &one) == 0) {
        if (x.sign == 1) {  // Negative sign, adjust by adding n
            free_bignum(res);
            add_bignum(res, &x, n);
        }
        free_bignum(&y);
        free_bignum(&x);
        free_bignum(&one);
        return 0;
    } else {
        fprintf(stderr, "Inverse does not exist since gcd(a, n) != 1\n");
        free_bignum(&x);
        free_bignum(&y);
        free_bignum(res);
        free_bignum(&one);
        return 1;
    }
}
