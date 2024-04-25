#include "bignum/bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum/common.h"

bignum_t bignum_new() { return (bignum_t){.digits = NULL, .size = 0, .sign = POS}; }

int init_bignum(bignum_t *num, size_t size, uint8_t sign) {
    num->size = size;
    num->sign = sign;
    num->digits = (uint8_t *)calloc(size, sizeof(int));

    if (num->digits == NULL) {
        fprintf(stderr, "Memory allocation failed in init_bignum(...)\n");
        return FAILURE;
    }

    return SUCCESS;
}

void free_bignum(bignum_t *a) {
    // if (a == NULL) return;
    // if (a->digits != NULL) return;
    free(a->digits);
    a->digits = NULL;
    a->sign = POS;
    a->size = 0;
}

void trim_leading_zeros_bignum(bignum_t *num) {
    while (num->size > 1 && num->digits[num->size - 1] == 0) {
        num->size--;
    }
}

int resize_bignum(bignum_t *num, size_t new_size) {
    num->digits = (uint8_t *)realloc(num->digits, new_size * sizeof(int));
    if (num->digits == NULL) {
        fprintf(stderr, "Memory allocation failed in resize_bignum(...)\n");
        return FAILURE;
    }
    num->size = new_size;

    return SUCCESS;
}

int str2bignum(bignum_t *num, char *str) {
    size_t size = strlen(str);
    size_t max_digits = size * MAX_DIGIT_SIZE;

    int sign;
    // Decide the sign of the number
    if (str[0] == '-') {
        sign = NEG;
        str++;
        size--;
    } else if (str[0] == '+') {
        sign = POS;
        str++;
        size--;
    } else {
        sign = POS;
    }

    if (init_bignum(num, max_digits, sign) != SUCCESS) return FAILURE;

    for (size_t i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            fprintf(stderr,
                    "Invalid character in string (%c) in str2bignum(...)\n",
                    str[i]);
            return FAILURE;
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

    return SUCCESS;
}

int copy_bignum(bignum_t *destination, const bignum_t *source) {
    if (destination->digits != NULL && destination->size != 0) {
        free(destination->digits);  // Free old memory to prevent leaks
    }

    destination->size = source->size;  // Copy size
    destination->sign = source->sign;  // Copy sign
    destination->digits =
        malloc(source->size * sizeof(uint8_t));  // Allocate new memory

    if (destination->digits == NULL) {
        fprintf(stderr, "Memory allocation failed in copy_bignum(...)\n");
        destination->size = 0;
        return FAILURE;
    }

    memcpy(destination->digits,
           source->digits,
           source->size);  // Copy the actual digits

    return SUCCESS;
}
