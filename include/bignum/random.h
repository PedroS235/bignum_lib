/**
 * @file common.h
 * Authors: Pedro Soares & Issam Jomaa
 * @brief Random large integer generation
 */
#ifndef RANDOM_H
#define RANDOM_H
#include <stdbool.h>

#include "bignum/bignum.h"

/**
 * @brief Initialize the randomness seed
 */
void init_seed();

/**
 * @brief Random Big Number
 *
 * @param *res Result will be stored here
 * @param length Bit length of the random BigNum
 * @return 0 if success, 1 if failure
 */
int genrandom(bignum_t *res, int length);

/**
 * @brief Random Big Number
 *
 * @param res Result will be stored here
 * @param bit_length Bit length of the random BigNum
 * @return true if prime, false otherwise
 */
bool fermat_test(bignum_t p, int iterations);

/**
 * @brief Random Prime Big Number
 *
 * @param *res Result will be stored here
 * @param length Bit length of the random BigNum
 * @return 0 if success, 1 if failure
 */
int gen_random_prime(bignum_t *res, int length);

#endif
