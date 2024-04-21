#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void free_bignum(bignum_t *a) { free(a->digits); }

bignum_t str2bignum(char *str) {
    int size = strlen(str);
    int max_digits = size * 4;  // Maximum possible digits based on input string length
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

    for (int i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("Invalid character in string: %c\n", str[i]);
            exit(1);
        }

        int digit = str[i] - '0';

        // Multiply existing number by 10 and add the new digit
        int carry = digit;
        for (int j = 0; j < num.size || carry > 0; j++) {
            int value = carry;
            if (j < num.size) value += num.digits[j] * 10;
            num.digits[j] = value % 2;
            carry = value / 2;
        }

        // Update the size of the bignum representation
        if (num.size < max_digits) {
            num.size++;
        }
    }

    // Trim leading zeros
    while (num.size > 1 && num.digits[num.size - 1] == 0) {
        num.size--;
    }

    return num;
}

bignum_t int2bignum(int num) {
    if (num == 0) {
        bignum_t result = init_bignum(1);
        result.digits[0] = 0;
        return result;
    }

    int tmp = num;
    int length = 0;
    while (tmp > 0) {
        tmp /= 10;
        length++;
    }

    bignum_t result = init_bignum(length);

    while (num > 0) {
        result.digits[result.size - length] = num % 10;
        num /= 10;
        length--;
    }

    return result;
}
