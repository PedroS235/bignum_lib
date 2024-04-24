/**
 * @file arithmetic.h
 * Authors: Pedro Soares & Issam Jomaa
 * @brief Arithmetic operations on big numbers
 */
#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include <stdbool.h>

#include "bignum/bignum.h"

/**
 * @brief Add two big numbers
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int add_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers, ignoring sign
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int add_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Subtract two big numbers
 * Expects a > b. If a < b, it will call sub(b, a) and return the result!
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int sub_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Subtract two big numbers, ignoring sign
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int sub_bignum_unsigned(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Multiply two big numbers
 *
 * @param *res Result will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @return 0 if success, 1 if failure
 */
int mult_bignum(bignum_t *res, bignum_t *a, bignum_t *b);

/**
 * @brief Binary Euclidian Division of two big numbers
 *
 * @param *q Quotient will be stored here
 * @param *r Remainder will be stored here
 * @param *a First big number
 * @param *b Second big number
 * @param pos_remainder Ensure remainder is always positive
 * @return 0 if success, 1 if failure
 */
int div_bignum(bignum_t *q, bignum_t *r, bignum_t *a, bignum_t *b, bool pos_remainder);

/**
 * @brief Absolute value of a big number

 * @param *n Big number to take the absolute value of
 * @return true if abs applied, false if n is already positive
 */
bool abs_bignum(bignum_t *n);

#endif  // !ARITHMETIC_H
