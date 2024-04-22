#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdbool.h>

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
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int add_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers, ignoring sign
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int add_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers modulo m
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return 0 if success, 1 if failure
 */
int addmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n);

/**
 * @brief Subtract two big numbers
 * Expects a > b. If a < b, it will call sub(b, a) and return the result!
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int sub_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Subtract two big numbers, ignoring sign
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int sub_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Multiply two big numbers
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int mult_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Binary Euclidian Division of two big numbers
 *
 * @param q Quotient will be stored here
 * @param r Remainder will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int div_bignum(bignum_t *q, bignum_t *r, bignum_t *a, bignum_t *b, bool r_pos);

/**
 * @brief Multiply two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
int multmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n);

/**
 * @brief Divide two big numbers
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @return 0 if success, 1 if failure
 */
int bignum_mod(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Divide two big numbers modulo m
 *
 * @param res Result will be stored here
 * @param exp Exponent
 * @param m Modulo
 * @return 0 if success, 1 if failure
 */
int expmod(bignum_t *res, bignum_t *base, bignum_t *exp, bignum_t *m);

/**
 * @brief Extended Euclidean Algorithm
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param b Second big number
 * @param x Coefficient of a
 * @param y Coefficient of b
 * @return 0 if success, 1 if failure
 * @return bignum_t
 */
int extended_gcd(bignum_t *res, bignum_t a, bignum_t b, bignum_t *x, bignum_t *y);

/**
 * @brief Inverse modulo
 *
 * @param res Result will be stored here
 * @param a First big number
 * @param n Modulo
 * @return 0 if success, 1 if failure
 */
int inversemod(bignum_t *res, bignum_t *a, bignum_t *n);

#endif  // !ARITHMETIC_H
