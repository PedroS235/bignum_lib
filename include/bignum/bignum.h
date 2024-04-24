#ifndef CORE_H
#define CORE_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Big number structure
 *
 * @param digits Internal representation of the big number in binary. Store in Little
 * Endian format
 * @param size Size of the array
 * @param sign Sign of the big number. 0 for positive, 1 for negative
 */
typedef struct bignum {
    uint8_t *digits;
    size_t size;
    uint8_t sign;
} bignum_t;

/**
 * @brief Create a new big number
 *
 * @return *bignum_t Pointer to the new big number
 */
bignum_t bignum_new();

/**
 * @brief Initialize a big number
 *
 * @param *num Big number to initialize
 * @param size Size of the big number
 * @param sign Sign that the big number should have
 * @return 0 if success, 1 otherwise
 */
int init_bignum(bignum_t *num, size_t size, uint8_t sign);

/**
 * @brief Free a big number
 *
 * @param *a Big number to free
 */
void free_bignum(bignum_t *a);

/**
 * @brief Trim leading zeros from a big number
 *
 * @param *num Big number to trim
 */
void trim_leading_zeros_bignum(bignum_t *num);

/**
 * @brief Resize a big number
 *
 * @param *num Big number to resize
 * @param new_size New size of the big number
 */
int resize_bignum(bignum_t *num, size_t new_size);

/**
 * @brief Convert a string to a big number
 *
 * @param *num Big where to store the result
 * @param *str String to convert
 * @return 0 if success, 1 otherwise
 */
int str2bignum(bignum_t *num, char *str);

/**
 * @brief Copy a big number
 *
 * @param *destination Big number to copy to
 * @return *source Big number to copy from
 */
int copy_bignum(bignum_t *destination, const bignum_t *source);

#endif  // !CORE_H
