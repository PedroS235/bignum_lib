#ifndef UTILS_H
#define UTILS_H

#include "core.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
 * @brief Converts an integer to a binary string
 *
 * @param n Integer to convert
 * @param *size Size of the binary string
 * @return char*
 */
char *int2bin(int n, int *size);

/**
 * @brief Convert a big number to a string
 *
 * @param a Big number to convert
 * @return char*
 */
void print_bignum(bignum_t *a);

/**
 * @brief Trim leading zeros from a big number
 *
 * @param num Big number to trim
 */
void trim_bignum(bignum_t *num);

#endif  // !UTILS_H
