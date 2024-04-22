#ifndef RANDOM_H
#define RANDOM_H
#include <stdbool.h>

#include "bignum.h"
/**
 * @brief Initialize the randomness seed
 */
void init_seed();

/**
 * @brief Random Big Number
 *
 * @param res Result will be stored here
 * @param bit_length Bit length of the random BigNum
 * @return 0 if success, 1 if failure
 */
int genrandom(bignum_t *res, int bit_length);

/**
 * @brief Random Big Number
 *
 * @param res Result will be stored here
 * @param bit_length Bit length of the random BigNum
 * @return 0 if success, 1 if failure
 */
bool fermat_test(bignum_t p, int iterations);

#endif