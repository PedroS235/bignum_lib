/**
 * @file bitwise.h
 * Authors: Pedro Soares & Issam Jomaa
 * @brief Bitwise operations on big numbers
 */
#ifndef BITWISE_H
#define BITWISE_H

#include "bignum.h"

/**
 * @brief Shift a big number to the left by a given amount
 *
 * @param a Big number to shift
 * @param shift Amount to shift
 * @return bignum_t Shifted big number
 */
int left_shift(bignum_t *a, size_t shift);

/**
 * @brief Shift a big number to the right by a given amount
 *
 * @param a Big number to shift
 * @param shift Amount to shift
 * @return bignum_t Shifted big number
 */
int right_shift(bignum_t *a, size_t shift);

/**
 * @brief Shift a big number to the right/left by a given amount
 *
 * @param a Big number to shift
 * @param shift Amount to shift. Positive for left shift, negative for right shift
 * @return bignum_t Shifted big number
 */
int binary_shift(bignum_t *a, int shift);

#endif  // !BITWISE_H
