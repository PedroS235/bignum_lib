#ifndef RSA_H
#define RSA_H

#include "bignum/bignum.h"

/**
 * @brief Generate RSA key pair
 *
 * @param *n Modulus
 * @param *e Public exponent
 * @param *d Private exponent
 * @param length Length of the key
 * @return 0 if success, 1 if failure
 */
int rsa_keygen(bignum_t *n, bignum_t *e, bignum_t *d, int length);

/**
 * @brief Encrypt a message using RSA
 *
 * @param *c Cipher text
 * @param *m Message
 * @param *n Modulus
 * @param *e Public exponent
 * @return 0 if success, 1 if failure
 */
int rsa_encrypt(bignum_t *c, bignum_t *m, bignum_t *n, bignum_t *e);

/**
 * @brief Decrypt a message using RSA
 *
 * @param *m Message
 * @param *c Cipher text
 * @param *n Modulus
 * @param *d Private exponent
 * @return 0 if success, 1 if failure
 */
int rsa_decrypt(bignum_t *m, bignum_t *c, bignum_t *n, bignum_t *d);

#endif  // !RSA_H
