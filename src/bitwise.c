#include "bitwise.h"

#include <common.h>
#include <string.h>

bignum_t left_shift(bignum_t a, size_t shift) {
    if (shift == 0) return a;  // No shift needed

    int new_size = a.size + shift;
    bignum_t result;
    init_bignum(&result, new_size, POS);
    memcpy(result.digits + shift,
           a.digits,
           a.size * sizeof(uint8_t));  // Shift digits left

    return result;
}

bignum_t right_shift(bignum_t a, size_t shift) {
    if (shift == 0) return a;  // No shift needed
    if (shift >= a.size) {
        // Entire number is shifted out, return zero
        return ZERO();
    }

    int new_size = a.size - shift;
    bignum_t result;
    init_bignum(&result, new_size, POS);
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
        bignum_t result;
        init_bignum(&result, a.size, POS);
        memcpy(result.digits, a.digits, a.size * sizeof(uint8_t));
        return result;
    }
}
