// Author: Pedro Soares (0200566850)
#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * @brief Initialize a big number
 *
 * @param size Size of the big number
 * @return bignum_t
 */
bignum_t init_bignum(int size);

/**
 * @brief Convert a string to a big number
 *
 * @param str String to convert
 * @return bignum_t
 */
bignum_t str2bignum(char *str);

/**
 * @brief Convert an integer to a big number (Max number is 0xFFFFFFFF)
 *
 * @param num Integer to convert
 * @return bignum_t
 */
bignum_t int2bignum(int num);

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
 * @brief Multiply two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return bignum_t
 */
bignum_t mul(bignum_t *a, bignum_t *b);

/**
 * @brief Modular exponentiation
 *
 * @param base
 * @param exp Exponent
 * @return int
 */
int expmod(int base, int exp, int m);

/**
 * @brief Fibonacci
 *
 * @param n
 * @return bignum_t
 */
bignum_t fibonacci(int n);

/**
 * @brief Factorial
 *
 * @param n
 * @return bignum_t
 */
bignum_t factorial(int n);

/**
 * @brief Compare two big numbers
 *
 * @param a First big number
 * @param b Second big number
 * @return 0 if a == b, 1 if a > b, -1 if a < b
 */
static inline int cmp_bignum(bignum_t *a, bignum_t *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->tab[i] > b->tab[i]) return 1;
        if (a->tab[i] < b->tab[i]) return -1;
    }
    return 0;
}

/**
 * @brief Prints a big number
 *
 * @param a Big number to print
 * @return char*
 */
static inline void print_bignum(bignum_t *a) {
    for (int i = a->size - 1; i >= 0; i--) {
        printf("%d", a->tab[i]);
    }
    printf("\n");
}

/**
 * @brief Convert an integer to a binary string
 *
 * @param n Integer to convert
 * @return char*
 */
static inline char *int2bin(int num) {
    size_t size = sizeof(int) * 8;
    char *result = (char *)calloc(size + 1, sizeof(char));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = size - 1; i >= 0; i--) {
        result[i] = (num & 1) + '0';
        num >>= 1;
    }

    // Truncate leading zeros
    int i = 0;
    while (result[i] == '0') {
        i++;
    }

    if (i == size) {
        result[0] = '0';
        result[1] = '\0';
    } else {
        char *tmp = (char *)calloc(size + 1 - i, sizeof(char));
        if (tmp == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        strcpy(tmp, result + i);
        free(result);
        result = tmp;
    }

    return result;
}

#endif  // !BIG_NUM_H
