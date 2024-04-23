#include "common.h"

#include <stdio.h>

int compare_bignum(bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        return a->sign > b->sign ? LESS : GREATER;
    }

    if (a->size != b->size) {
        if (a->sign == 0) {
            return a->size > b->size ? GREATER : LESS;
        } else {
            return a->size > b->size ? LESS : GREATER;
        }
    }

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            if (a->digits[i] > b->digits[i]) {
                return a->sign == POS ? GREATER : LESS;
            }
            return (a->sign == POS ? LESS : GREATER);
        }
    }

    return EQUAL;
}

int compare_bignum_unsigned(bignum_t *a, bignum_t *b) {
    if (a->size > b->size) return GREATER;
    if (a->size < b->size) return LESS;

    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return GREATER;
        if (a->digits[i] < b->digits[i]) return LESS;
    }
    return EQUAL;
}

void print_bignum(bignum_t *num) {
    int decimal[MAX_DIGITS] = {0};
    int len = num->size;
    int i, j, carry, temp;

    for (i = 0; i < len; i++) {
        int bit = num->digits[len - 1 - i];

        carry = bit;
        for (j = 0; j <= i || carry; j++) {
            if (j < MAX_DIGITS) {
                temp = decimal[j] * 2 + carry;
                decimal[j] = temp % 10;
                carry = temp / 10;
            } else {
                break;
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
    init_bignum(&zero, 1, POS);
    return zero;
}

bignum_t ONE() {
    bignum_t one;
    str2bignum(&one, "1");
    return one;
}
