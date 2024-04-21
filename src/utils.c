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

void trim_bignum(bignum_t *num) {
    while (num->size > 1 && num->digits[num->size - 1] == 0) {
        num->size--;  // Reduce the size if the most significant digit is zero
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
    if (num->sign == 1) printf("- ");
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
