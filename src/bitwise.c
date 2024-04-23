#include "bitwise.h"

#include <common.h>
#include <string.h>

int left_shift(bignum_t *a, size_t shift) {
    if (shift == 0) return SUCCESS;  // No shift needed

    int new_size = a->size + shift;
    bignum_t result;
    int ret = init_bignum(&result, new_size, a->sign);
    if (ret != SUCCESS) return FAILURE;

    memcpy(result.digits + shift,
           a->digits,
           a->size * sizeof(uint8_t));  // Shift digits left

    free_bignum(a);
    copy_bignum(a, &result);
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
    int ret = init_bignum(&result, new_size, a->sign);
    if (ret != SUCCESS) return FAILURE;

    memcpy(result.digits,
           a->digits + shift,
           new_size * sizeof(uint8_t));  // Shift digits right

    free_bignum(a);
    copy_bignum(a, &result);
    free_bignum(&result);

    return SUCCESS;
}

int binary_shift(bignum_t *a, int shift) {
    if (shift > 0) {
        return left_shift(a, shift);
    }
    return right_shift(a, -shift);
}
