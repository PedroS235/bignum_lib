#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

bignum_t init_bignum(int size) {
    bignum_t num;
    num.size = size;
    num.sign = 0;
    num.digits = (uint8_t *)calloc(size, sizeof(int));

    if (num.digits == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    return num;
}

int init_bignum_(bignum_t *num, int size) {
    num->size = size;
    num->sign = 0;
    num->digits = (uint8_t *)calloc(size, sizeof(int));

    if (num->digits == NULL) {
        fprintf(stderr, "Memory allocation failed in init_bignum(...)\n");
        return 1;
    }

    return 0;
}

void free_bignum(bignum_t *a) { free(a->digits); }

bignum_t str2bignum(char *str) {
    size_t size = strlen(str);
    size_t max_digits =
        size * 4;  // Maximum possible digits based on input string length
    bignum_t num = init_bignum(max_digits);

    if (str[0] == '-') {
        num.sign = 1;  // Set sign to negative
        str++;         // Skip the negative sign character
        size--;        // Adjust size to exclude the negative sign
    } else if (str[0] == '+') {
        num.sign = 0;  // Set sign to positive
        str++;         // Skip the negative sign character
        size--;        // Adjust size to exclude the negative sign
    } else {
        num.sign = 0;  // Set sign to positive
    }

    for (size_t i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("Invalid character in string: %c\n", str[i]);
            exit(1);
        }

        int digit = str[i] - '0';

        // Multiply existing number by 10 and add the new digit
        int carry = digit;
        for (size_t j = 0; j < num.size || carry > 0; j++) {
            int value = carry;
            if (j < num.size) value += num.digits[j] * 10;
            num.digits[j] = value % 2;
            carry = value / 2;
        }
    }

    // Trim leading zeros
    while (num.size > 1 && num.digits[num.size - 1] == 0) {
        num.size--;
    }

    return num;
}

int str2bignum_(bignum_t *num, char *str) {
    size_t size = strlen(str);
    size_t max_digits = size * MAX_DIGIT_SIZE;
    init_bignum_(num, max_digits);

    // Decide the sign of the number
    if (str[0] == '-') {
        num->sign = NEG;
        str++;
        size--;
    } else if (str[0] == '+') {
        num->sign = POS;
        str++;
        size--;
    } else {
        num->sign = POS;
    }

    for (size_t i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            fprintf(stderr,
                    "Invalid character in string (%c) in str2bignum(...)\n",
                    str[i]);
            return 1;
        }

        int digit = str[i] - '0';

        int carry = digit;
        for (size_t j = 0; j < num->size || carry > 0; j++) {
            int value = carry;
            if (j < num->size) value += num->digits[j] * 10;
            num->digits[j] = value % 2;
            carry = value / 2;
        }
    }

    trim_leading_zeros_bignum(num);

    return 0;
}
