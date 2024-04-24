#include "bignum/bitwise.h"

#include <string.h>

#include "bignum/common.h"

int left_shift(bignum_t *a, size_t shift) {
    if (shift == 0) return SUCCESS;  // No shift needed

    int new_size = a->size + shift;
    bignum_t result;
    if (init_bignum(&result, new_size, a->sign) != SUCCESS) return FAILURE;

    memcpy(result.digits + shift,
           a->digits,
           a->size * sizeof(uint8_t));  // Shift digits left

    if (copy_bignum(a, &result) != SUCCESS) return FAILURE;
    free_bignum(&result);

    return SUCCESS;
}

int right_shift(bignum_t *a, size_t shift) {
    if (shift == 0) return SUCCESS;  // No shift needed
    if (shift >= a->size) {
        // Entire number is shifted out, return zero
        free_bignum(a);
        return init_bignum(a, 1, POS);
    }

    int new_size = a->size - shift;
    bignum_t result;
    if (init_bignum(&result, new_size, a->sign) != SUCCESS) return FAILURE;

    memcpy(result.digits,
           a->digits + shift,
           new_size * sizeof(uint8_t));  // Shift digits right

    if (copy_bignum(a, &result) != SUCCESS) return FAILURE;
    free_bignum(&result);

    return SUCCESS;
}

int binary_shift(bignum_t *a, int shift) {
    if (shift > 0) {
        return left_shift(a, shift);
    }
    return right_shift(a, -shift);
}
