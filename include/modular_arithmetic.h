/**
 * @file modular_arithmetic.h
 * Authors: Pedro Soares & Issam Jomaa
 * @brief Modular arithmetic operations on big numbers modulo m
 */
#ifndef MODULAR_ARITHMETIC_H
#define MODULAR_ARITHMETIC_H

#include "bignum.h"

/**
 * @brief Add two big numbers modulo m
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @param *n Modulo
 * @return 0 if success, 1 if failure
 */
int addmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n);

/**
 * @brief Multiply two big numbers modulo m
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @param *n Modulo
 * @return bignum_t
 */
int multmod_bignum(bignum_t *res, bignum_t *a, bignum_t *b, bignum_t *n);

/**
 * @brief Divide two big numbers
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int bignum_mod(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Modular exponentiationo of Big Numbers
 *
 * @param *res Result will be stored here
 * @param *base Base
 * @param *exp Exponent
 * @param *m Modulo
 * @return 0 if success, 1 if failure
 */
int expmod(bignum_t *res, bignum_t *base, bignum_t *exp, bignum_t *m);

/**
 * @brief Extended Euclidean Algorithm
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @param *x Coefficient of a
 * @param *y Coefficient of b
 * @return 0 if success, 1 if failure
 * @return bignum_t
 */
int extended_gcd(bignum_t *res, bignum_t a, bignum_t b, bignum_t *x, bignum_t *y);

/**
 * @brief Inverse modulo
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *n Modulo
 * @return 0 if success, 1 if failure
 */
int inversemod(bignum_t *res, bignum_t *a, bignum_t *n);

#endif  // MODULAR_ARITHMETIC_H!
