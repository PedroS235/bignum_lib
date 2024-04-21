#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

char *int2bin(int num, int *length) {
    size_t size = sizeof(int) * 8;
    char *result = (char *)malloc(size + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;  // Allow the caller to handle the error
    }

    result[size] = '\0';
    for (int i = size - 1; i >= 0; i--) {
        result[i] = (num & 1) + '0';
        num >>= 1;
    }

    // Count number of leading zeros
    size_t i = 0;
    while (i < size - 1 && result[i] == '0') {
        i++;
    }

    // Truncate the leading zeros
    if (i > 0) {
        memmove(result, result + i, size - i + 1);
    }

    *length = size - i;

    return result;
}

void trim_leading_zeros_bignum(bignum_t *num) {
    while (num->size > 1 && num->digits[num->size - 1] == 0) {
        num->size--;
    }
}

void resize_bignum(bignum_t *num, size_t new_size) {
    num->digits = (int *)realloc(num->digits, new_size * sizeof(int));
    if (num->digits == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    num->size = new_size;
}

void reverse_string(uint8_t *str) {
    if (str) {
        char *left = str;
        char *right = str + strlen(str) - 1;
        while (left < right) {
            char tmp = *left;
            *left++ = *right;
            *right-- = tmp;
        }
    }
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
#ifdef DEBUG
    if (num->sign == 1) printf("-");

    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
#endif
}

bignum_t left_shift(bignum_t a, int shift) {
    if (shift == 0) return a;  // No shift needed

    int new_size = a.size + shift;
    bignum_t result = init_bignum(new_size);
    memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
    memcpy(result.digits + shift,
           a.digits,
           a.size * sizeof(uint8_t));  // Shift digits left

    return result;
}

bignum_t right_shift(bignum_t a, int shift) {
    if (shift == 0) return a;  // No shift needed
    if (shift >= a.size) {
        // Entire number is shifted out, return zero
        bignum_t result = init_bignum(1);
        result.digits[0] = 0;
        return result;
    }

    int new_size = a.size - shift;
    bignum_t result = init_bignum(new_size);
    memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
    memcpy(result.digits,
           a.digits + shift,
           new_size * sizeof(uint8_t));  // Shift digits right

    return result;
}

bignum_t binary_shift(bignum_t a, int shift) {
    if (shift > 0) {
        return left_shift(a, shift);
    } else if (shift < 0) {
        return right_shift(a, -shift);
    } else {
        // No shift is required, return a copy of 'a'
        bignum_t result = init_bignum(a.size);
        memcpy(result.digits, a.digits, a.size * sizeof(uint8_t));
        return result;
    }
}
