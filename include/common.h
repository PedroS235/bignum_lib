/**
 * @file common.h
 * Authors: Pedro Soares & Issam Jomaa
 * @brief Common functions for big numbers
 */
#ifndef COMMON_H
#define COMMON_H

#include "bignum.h"

#define BASE 2              // Base of the number system. SHOULD NOT BE CHANGED
#define POS 0               // Positive sign
#define NEG 1               // Negative sign
#define SUCCESS 0           // Success return value
#define FAILURE 1           // Failure return value
#define DIVISION_BY_ZERO 2  // Division by zero return value
#define MAX_DIGIT_SIZE 4    // A digit is a maximum of 4 bits, meaning 9 = 1001
#define MAX_DIGITS 5000     // Maximum value of a digit

/**
 * @brief Compare two big numbers
 *
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare_bignum(bignum_t *a, bignum_t *b);

/**
 * @brief Compare two big numbers, ignoring sign
 *
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare_bignum_unsigned(bignum_t *a, bignum_t *b);

/**
 * @brief Print a big number
 *
 * @param *a Big number to print
 * @return char*
 */
void print_bignum(bignum_t *a);

/**
 * @brief Generic Big Number Zero
 *
 * @return bignum_t
 */
bignum_t ZERO();

/**
 * @brief Generic Big Number one
 *
 * @return bignum_t
 */
bignum_t ONE();

#endif  // !COMMON_H
