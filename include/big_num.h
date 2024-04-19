#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <stdio.h>
#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
 * @brief Big number structure
 *
 * @param tab Array of integers in reverse order. The first element is the least
 * significant digit
 * @param size Size of the array
 */
typedef struct bignum {
  int *tab;
  int size;
} bignum_t;

/**
 * @brief Convert an integer to a binary string
 *
 * @param n Integer to convert
 * @return char*
 */
char *int2bin(int n);

/**
 * @brief Initialize a big number
 *
 * @param size Size of the big number
 * @return bignum_t
 */
bignum_t init_big_num(int size);

/**
 * @brief Convert a string to a big number
 *
 * @param str String to convert
 * @return bignum_t
 */
bignum_t str2bignum(char *str);
bignum_t int2bignum(int num);

/**
 * @brief Convert a big number to a string
 *
 * @param a Big number to convert
 * @return char*
 */
void print_bignum(bignum_t *a);

/**
 * @brief Free a big number
 *
 * @param a Big number to free
 */
void free_bignum(bignum_t *a);

/**
 * @brief Add two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
bignum_t add(bignum_t *a, bignum_t *b);

/**
 * @brief Add two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
bignum_t add_mod(bignum_t *a, bignum_t *b, bignum_t *m);

/**
 * @brief Subtract two big numbers
 * Expects a > b. If a < b, it will call sub(b, a) and return the result!
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
bignum_t sub(bignum_t *a, bignum_t *b);

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
bignum_t mul(bignum_t *a, bignum_t *b);

/**
 * @brief Multiply two big numbers modulo m
 *
 * @param a First big number
 * @param b Second big number
 * @param m Modulo
 * @return bignum_t
 */
bignum_t mul_mod(bignum_t *a, bignum_t *b, bignum_t *m);

/**
 * @brief Divide two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
bignum_t remainder_bignum(bignum_t *a, bignum_t *b);

/**
 * @brief Divide two big numbers modulo m
 *
 * @param base Base
 * @param exp Exponent
 * @param m Modulo
 * @return bignum_t
 */
bignum_t expmod(bignum_t *base, bignum_t *exp, bignum_t *m);
int expmod_(int base, int exp, int m);

/**
 * @brief Compare two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
int compare_bignum(bignum_t *a, bignum_t *b);

#endif // !BIG_NUM_H
