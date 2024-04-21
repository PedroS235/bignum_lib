#include "arithmetic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "utils.h"

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

// TODO: Possibly ignore this and just use the compare_bignum function
int compare_bignum_unsigned(bignum_t *a, bignum_t *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

bignum_t add_unsigned(bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    bignum_t result = init_bignum(size + 1);

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];

        result.digits[i] = sum % BASE;
        carry = sum / BASE;
    }

    if (carry) {
        result.digits[size] = carry;
    } else {
        result.size = size;
    }

    return result;
}

bignum_t add(bignum_t *a, bignum_t *b) {
    if (a->sign == b->sign) {
        bignum_t result = add_unsigned(a, b);
        result.sign = a->sign;
        return result;
    } else {
        if (compare_bignum_unsigned(a, b) >= 0) {
            bignum_t result = sub_unsigned(a, b);
            result.sign = a->sign;
            return result;
        } else {
            bignum_t result = sub_unsigned(b, a);
            result.sign = b->sign;
            return result;
        }
    }
}

bignum_t sub(bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        // Different signs imply addition
        bignum_t result = add_unsigned(a, b);
        result.sign = a->sign;  // Result takes the sign of 'a'
        return result;
    } else {
        // Same signs
        if (compare_bignum_unsigned(a, b) >= 0) {
            bignum_t result = sub_unsigned(a, b);
            result.sign = a->sign;  // Result takes the sign of 'a'
            return result;
        } else {
            bignum_t result = sub_unsigned(b, a);
            result.sign = 1 - a->sign;  // Result takes the opposite sign
            return result;
        }
    }
}
bignum_t sub_unsigned(bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    bignum_t result = init_bignum(size);

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

        result.digits[i] = sum;
    }

    while (result.size > 1 && result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

bignum_t mul(bignum_t *a, bignum_t *b) {
    size_t size = a->size + b->size;
    bignum_t result = init_bignum(size);
    result.sign = (a->sign + b->sign) % 2;

    for (size_t i = 0; i < a->size; i++) {
        int carry = 0;
        for (size_t j = 0; j < b->size; j++) {
            int sum = a->digits[i] * b->digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        result.digits[i + b->size] = carry;
    }

    while (result.size > 1 && result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

div_result_t div_bignum(bignum_t *a, bignum_t *b) {
    bignum_t zero = str2bignum("0");
    if (compare_bignum(b, &zero) == 0) {
        printf("Division by zero\n");
        exit(1);
    }

    bignum_t q = init_bignum(a->size);
    bignum_t r = init_bignum(a->size);  // Remainder initially set to the dividend
    memcpy(r.digits, a->digits, a->size * sizeof(uint8_t));

    int shift = a->size - b->size;

    // Align the divisor with the highest non-zero digit of the dividend
    bignum_t shifted_b = binary_shift(*b, shift);

    while (shift >= 0) {
        if (compare_bignum_unsigned(&r, &shifted_b) >= 0) {
            bignum_t temp_r = sub_unsigned(&r, &shifted_b);
            free_bignum(&r);
            r = temp_r;
            q.digits[shift] = 1;
        } else {
            q.digits[shift] = 0;
        }

        shift--;
        bignum_t shifted_temp = binary_shift(shifted_b, -1);
        free_bignum(&shifted_b);
        shifted_b = shifted_temp;
    }

    // Correct signs based on input signs
    q.sign = a->sign ^ b->sign;
    r.sign = a->sign;

    // Ensure the remainder is non-negative
    if (r.sign > 0) {
        // Add n to the remainder to make it non-negative
        bignum_t adjusted_remainder = add(&r, b);
        free_bignum(&r);         // Free the original negative remainder
        r = adjusted_remainder;  // Return the adjusted, non-negative remainder
    }

    trim_leading_zeros_bignum(&q);
    trim_leading_zeros_bignum(&r);
    free_bignum(&zero);
    free_bignum(&shifted_b);
    return (div_result_t){.quotient = q, .remainder = r};
}

bignum_t bignum_remainder(bignum_t a, bignum_t n) {
    div_result_t res = div_bignum(&a, &n);
    free_bignum(&res.quotient);
    return res.remainder;
}

bignum_t addmod(bignum_t *a, bignum_t *b, bignum_t *n) {
    // First, add a and b
    bignum_t sum = add(a, b);

    // Then, calculate the remainder of sum divided by n
    bignum_t result = bignum_remainder(sum, *n);

    // Clean up intermediate sum if necessary
    free_bignum(&sum);

    return result;
}

bignum_t multmod(bignum_t a, bignum_t b, bignum_t n) {
    // First, multiply a and b
    bignum_t product = mul(&a, &b);

    // Then, calculate the remainder of product divided by n
    bignum_t result = bignum_remainder(product, n);

    // Clean up intermediate product if necessary
    free_bignum(&product);

    return result;
}

bignum_t expmod(bignum_t *a, bignum_t *b, bignum_t *n) {
    bignum_t result = init_bignum(1);
    result.digits[0] = 1;  // Initialize result to 1

    bignum_t base = init_bignum(a->size);
    memcpy(base.digits, a->digits, a->size * sizeof(uint8_t));

    size_t i;
    for (i = 0; i < b->size; i++) {
        uint8_t bit = b->digits[i];
        if (bit) {
            bignum_t temp = multmod(result, base, *n);
            free_bignum(&result);
            result = temp;
        }
        bignum_t temp = multmod(base, base, *n);
        free_bignum(&base);
        base = temp;
    }

    free_bignum(&base);
    return result;
}

bignum_t extended_gcd(bignum_t a, bignum_t b, bignum_t *x, bignum_t *y) {
    bignum_t zero = str2bignum("0");
    free_bignum(x);
    free_bignum(y);
    if (compare_bignum(&a, &zero) == 0) {
        *x = zero;
        *y = str2bignum("1");
        free_bignum(&a);
        return b;
    }

    bignum_t x1 = init_bignum(1);
    bignum_t y1 = init_bignum(1);

    bignum_t remainder = bignum_remainder(b, a);
    bignum_t gcd = extended_gcd(remainder, a, &x1, &y1);

    div_result_t tmp = div_bignum(&b, &a);
    bignum_t tmp2 = mul(&tmp.quotient, &x1);
    *x = sub(&y1, &tmp2);

    *y = init_bignum(x1.size);
    memcpy(y->digits, x1.digits, x1.size * sizeof(uint8_t));
    y->sign = x1.sign;

    free_bignum(&x1);
    free_bignum(&y1);
    // free_bignum(&remainder);
    free_bignum(&tmp.quotient);
    free_bignum(&tmp.remainder);
    free_bignum(&tmp2);
    free_bignum(&zero);

    return gcd;
}

bignum_t inversemod(bignum_t a, bignum_t n) {
    bignum_t x = init_bignum(1);
    bignum_t y = init_bignum(1);

    bignum_t gcd = extended_gcd(a, n, &x, &y);
    bignum_t one = str2bignum("1");

    if (compare_bignum(&gcd, &one) == 0) {
        if (x.sign == 1) {  // Negative sign, adjust by adding n
            x = add(&x, &n);
        }
        free_bignum(&y);
        free_bignum(&gcd);
        free_bignum(&one);
        return x;
    } else {
        printf("Inverse does not exist since gcd(a, n) != 1\n");
        free_bignum(&x);
        free_bignum(&y);
        free_bignum(&gcd);
        free_bignum(&one);
        // exit(1);  // or handle error appropriately
    }
}
