#include "common.h"

#include <stdio.h>

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

void print_bignum(bignum_t *num) {
    int decimal[MAX_DIGITS] = {0};  // Array to store decimal digits
    int len = num->size;
    int i, j, carry, temp;

    for (i = 0; i < len; i++) {
        int bit = num->digits[len - 1 - i];  // Current binary bit (0 or 1)

        // Add bit*2^i to the decimal number
        carry = bit;
        for (j = 0; j <= i || carry; j++) {
            if (j < MAX_DIGITS) {
                temp = decimal[j] * 2 + carry;
                decimal[j] = temp % 10;
                carry = temp / 10;
            } else {
                break;  // Prevent writing outside the bounds of the array
            }
        }
    }

    // Print the decimal number
    if (num->sign == 1) printf("-");
    int start = 0;
    for (i = MAX_DIGITS - 1; i >= 0; i--) {
        if (decimal[i] != 0) {
            start = 1;
        }
        if (start) {
            printf("%d", decimal[i]);
        }
    }
    if (!start) {
        printf("0");  // Handle case for zero
    }
    printf("\n");
}

bignum_t ZERO() {
    bignum_t zero;
    init_bignum_(&zero, 1, POS);
    return zero;
}
bignum_t ONE() {
    bignum_t one;
    str2bignum_(&one, "1");
    return one;
}
