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
        // Same sign addition (simple add and carry, preserve sign)
        bignum_t result = add_unsigned(a, b);
        result.sign = a->sign;  // The sign remains the same as both operands
        return result;
    } else {
        // Different signs, effectively a subtraction operation
        if (compare_bignum_unsigned(a, b) >= 0) {
            bignum_t result = sub_unsigned(a, b);
            result.sign =
                a->sign;  // Result takes the sign of the bigger number (in magnitude)
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

bignum_t binary_shift(bignum_t a, int shift) {
    int new_size;
    bignum_t result;

    if (shift == 0) {
        // No shift required, return a copy of 'a'
        result = init_bignum(a.size);
        memcpy(result.digits, a.digits, a.size * sizeof(uint8_t));
        return result;
    }

    if (shift > 0) {
        // Left shift (positive shift)
        new_size = a.size + shift;
        result = init_bignum(new_size);
        memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
        memcpy(result.digits + shift, a.digits, a.size * sizeof(uint8_t));
    } else {
        // Right shift (negative shift)
        // Ensure we do not create a negative size if the shift is larger than the
        // number of digits
        if (-shift >= a.size) {
            result = init_bignum(1);  // At minimum keep one digit set to zero
            result.digits[0] = 0;
            return result;
        }
        new_size = a.size + shift;  // shift is negative, so this actually subtracts
        result = init_bignum(new_size);
        memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
        memcpy(result.digits,
               a.digits - shift,
               new_size * sizeof(uint8_t));  // Shift digits right
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
    memcpy(r.digits, a->digits, a->size);

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
        bignum_t shifted_temp =
            binary_shift(shifted_b, -1);  // Shift the divisor one position to the right
        free_bignum(&shifted_b);
        shifted_b = shifted_temp;
    }

    // Correct signs based on input signs
    q.sign = (a->sign + b->sign) % 2;  // XOR of the signs
    r.sign = 0;  // Remainder is always non-negative in Euclidean division

    trim_bignum(&q);
    trim_bignum(&r);
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
    memcpy(base.digits, a->digits, a->size);

    int i;
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
    memcpy(y->digits, x1.digits, x1.size);
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
