#ifndef CORE_H
#define CORE_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief Big number structure
 *
 * @param tab Array of integers in reverse order. The first element is the least
 * significant digit
 * @param size Size of the array
 */
typedef struct bignum {
    uint8_t *digits;
    size_t size;
    uint8_t sign;
} bignum_t;

/**
 * @brief Initialize a big number
 *
 * @param size Size of the big number
 * @return bignum_t
 */
bignum_t init_bignum(int size);

/**
 * @brief Free a big number
 *
 * @param a Big number to free
 */
void free_bignum(bignum_t *a);

/**
 * @brief Convert a string to a big number
 *
 * @param str String to convert
 * @return bignum_t
 */
bignum_t str2bignum(char *str);

/**
 * @brief Convert an integer to a big number
 *
 * @param num Integer to convert
 * @return bignum_t
 */
bignum_t int2bignum(int num);

#endif  // !CORE_H
