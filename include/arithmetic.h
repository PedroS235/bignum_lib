#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "bignum.h"

typedef struct div_result {
    bignum_t quotient;
    bignum_t remainder;
} div_result_t;

/**
 * @brief Compare two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare_bignum(bignum_t *a, bignum_t *b);

/**
 * @brief Compare two big numbers, ignoring sign
 *
 * @param a First big number
 * @param b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare_bignum_unsigned(bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
int add_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
bignum_t addmod_bignum(bignum_t *a, bignum_t *b, bignum_t *n);

/**
 * @brief Subtract two big numbers
 * Expects a > b. If a < b, it will call sub(b, a) and return the result!
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
int sub_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Subtract two big numbers, ignoring sign
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
int sub_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Subtract two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
bignum_t sub_mod(bignum_t *a, bignum_t *b, bignum_t *m);

/**
 * @brief Multiply two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
int mul_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Binary Euclidian Division of two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return div_result_t
 */
div_result_t div_bignum(bignum_t *a, bignum_t *b);

/**
 * @brief Multiply two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
bignum_t multmod(bignum_t a, bignum_t b, bignum_t m);

/**
 * @brief Divide two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
bignum_t bignum_remainder(bignum_t a, bignum_t b);

/**
 * @brief Divide two big numbers modulo m
 *
 * @param base Base
 * @param exp Exponent
 * @param m Modulo
 * @return bignum_t
 */
bignum_t expmod(bignum_t *base, bignum_t *exp, bignum_t *m);

bignum_t extended_gcd(bignum_t a, bignum_t b, bignum_t *x, bignum_t *y);
bignum_t inversemod(bignum_t a, bignum_t n);

#endif  // !ARITHMETIC_H
