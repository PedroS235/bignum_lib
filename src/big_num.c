#include "big_num.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 2
#define MAX_DIGITS 1000
// #define DEBUG

bignum_t init_big_num(int size) {
    bignum_t num;
    num.size = size;
    num.sign = 0;
    num.digits = (uint8_t *)calloc(size, sizeof(int));

    if (num.digits == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    return num;
}

char *int2bin(int num) {
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
    size_t i = 0;
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

bignum_t int2bignum(int num) {
    if (num == 0) {
        bignum_t result = init_big_num(1);
        result.digits[0] = 0;
        return result;
    }

    int tmp = num;
    int length = 0;
    while (tmp > 0) {
        tmp /= 10;
        length++;
    }

    bignum_t result = init_big_num(length);

    while (num > 0) {
        result.digits[result.size - length] = num % 10;
        num /= 10;
        length--;
    }

    return result;
}

void trim_bignum(bignum_t *num) {
    while (num->size > 1 && num->digits[num->size - 1] == 0) {
        num->size--;  // Reduce the size if the most significant digit is zero
    }
}

void free_bignum(bignum_t *a) { free(a->digits); }

int compare_bignum(bignum_t *a, bignum_t *b) {
    // First, compare signs
    if (a->sign != b->sign) {
        return a->sign > b->sign ? -1
                                 : 1;  // Assume sign 0 is non-negative, 1 is negative
    }

    // Sign is the same: compare sizes
    if (a->size != b->size) {
        if (a->sign == 0) {  // both non-negative
            return a->size > b->size ? 1 : -1;
        } else {  // both negative
            return a->size > b->size ? -1 : 1;
        }
    }

    // Same sign and size: compare digits from most significant
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] != b->digits[i]) {
            return (a->digits[i] > b->digits[i]) ? (a->sign == 0 ? 1 : -1)
                                                 : (a->sign == 0 ? -1 : 1);
        }
    }

    // All digits are the same
    return 0;
}
int compare_bignum_unsigned(bignum_t *a, bignum_t *b) {
    if (a->size > b->size) return 1;
    if (a->size < b->size) return -1;
    for (int i = a->size - 1; i >= 0; i--) {
        if (a->digits[i] > b->digits[i]) return 1;
        if (a->digits[i] < b->digits[i]) return -1;
    }
    return 0;
}

bignum_t add_unsigned(bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    bignum_t result = init_big_num(size + 1);

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum += b->digits[i];

        result.digits[i] = sum % BASE;
        carry = sum / BASE;
    }

    if (carry) {
        result.digits[size] = carry;
    } else {
        result.size = size;
    }

    return result;
}

bignum_t add(bignum_t *a, bignum_t *b) {
    if (a->sign == b->sign) {
        // Same sign addition (simple add and carry, preserve sign)
        bignum_t result = add_unsigned(a, b);
        result.sign = a->sign;  // The sign remains the same as both operands
        return result;
    } else {
        // Different signs, effectively a subtraction operation
        if (compare_bignum_unsigned(a, b) >= 0) {
            bignum_t result = sub_unsigned(a, b);
            result.sign =
                a->sign;  // Result takes the sign of the bigger number (in magnitude)
            return result;
        } else {
            bignum_t result = sub_unsigned(b, a);
            result.sign = b->sign;
            return result;
        }
    }
}

bignum_t sub(bignum_t *a, bignum_t *b) {
    if (a->sign != b->sign) {
        // Different signs imply addition
        bignum_t result = add_unsigned(a, b);
        result.sign = a->sign;  // Result takes the sign of 'a'
        return result;
    } else {
        // Same signs
        if (compare_bignum_unsigned(a, b) >= 0) {
            bignum_t result = sub_unsigned(a, b);
            result.sign = a->sign;  // Result takes the sign of 'a'
            return result;
        } else {
            bignum_t result = sub_unsigned(b, a);
            result.sign = 1 - a->sign;  // Result takes the opposite sign
            return result;
        }
    }
}
bignum_t sub_unsigned(bignum_t *a, bignum_t *b) {
    size_t size = a->size > b->size ? a->size : b->size;
    bignum_t result = init_big_num(size);

    int carry = 0;
    for (size_t i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->digits[i];
        if (i < b->size) sum -= b->digits[i];

        if (sum < 0) {
            sum += BASE;
            carry = -1;
        } else {
            carry = 0;
        }

        result.digits[i] = sum;
    }

    while (result.size > 1 && result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

bignum_t mul(bignum_t *a, bignum_t *b) {
    size_t size = a->size + b->size;
    bignum_t result = init_big_num(size);
    result.sign = (a->sign + b->sign) % 2;

    for (size_t i = 0; i < a->size; i++) {
        int carry = 0;
        for (size_t j = 0; j < b->size; j++) {
            int sum = a->digits[i] * b->digits[j] + result.digits[i + j] + carry;
            result.digits[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        result.digits[i + b->size] = carry;
    }

    while (result.size > 1 && result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

bignum_t binary_shift(bignum_t a, int shift) {
    int new_size;
    bignum_t result;

    if (shift == 0) {
        // No shift required, return a copy of 'a'
        result = init_big_num(a.size);
        memcpy(result.digits, a.digits, a.size * sizeof(uint8_t));
        return result;
    }

    if (shift > 0) {
        // Left shift (positive shift)
        new_size = a.size + shift;
        result = init_big_num(new_size);
        memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
        memcpy(result.digits + shift, a.digits, a.size * sizeof(uint8_t));
    } else {
        // Right shift (negative shift)
        // Ensure we do not create a negative size if the shift is larger than the
        // number of digits
        if (-shift >= a.size) {
            result = init_big_num(1);  // At minimum keep one digit set to zero
            result.digits[0] = 0;
            return result;
        }
        new_size = a.size + shift;  // shift is negative, so this actually subtracts
        result = init_big_num(new_size);
        memset(result.digits, 0, new_size * sizeof(uint8_t));  // Initialize all to zero
        memcpy(result.digits,
               a.digits - shift,
               new_size * sizeof(uint8_t));  // Shift digits right
    }

    return result;
}

div_result_t div_bignum(bignum_t *a, bignum_t *b) {
    bignum_t zero = str2bignum("0");
    if (compare_bignum(b, &zero) == 0) {
        printf("Division by zero\n");
        exit(1);
    }

    bignum_t q = init_big_num(a->size);
    bignum_t r = *a;  // Remainder initially set to the dividend

    int shift = a->size - b->size;

    // Align the divisor with the highest non-zero digit of the dividend
    bignum_t shifted_b = binary_shift(*b, shift);

    while (shift >= 0) {
        if (compare_bignum_unsigned(&r, &shifted_b) >= 0) {
            r = sub_unsigned(&r, &shifted_b);
            q.digits[shift] = 1;
        } else {
            q.digits[shift] = 0;
        }

        shift--;
        shifted_b =
            binary_shift(shifted_b, -1);  // Shift the divisor one position to the right
    }

    // Correct signs based on input signs
    q.sign = (a->sign + b->sign) % 2;  // XOR of the signs
    r.sign = 0;  // Remainder is always non-negative in Euclidean division

    trim_bignum(&q);
    trim_bignum(&r);
    free_bignum(&zero);
    free_bignum(&shifted_b);
    return (div_result_t){.quotient = q, .remainder = r};
}

bignum_t bignum_remainder(bignum_t a, bignum_t n) {
    // Check if the divisor is zero
    bignum_t zero = str2bignum("0");
    if (compare_bignum(&n, &zero) == 0) {
        printf("Division by zero in remainder calculation\n");
        free_bignum(&zero);
        exit(1);  // Ideally handle errors more gracefully in real applications
    }
    free_bignum(&zero);

    // Initialize the remainder to 'a' (copy of a)
    bignum_t r = init_big_num(a.size);
    memcpy(r.digits, a.digits, a.size * sizeof(uint8_t));

    // Calculate the necessary shift to align the most significant digits of 'n' and 'a'
    int shift = a.size - n.size;
    bignum_t shifted_n = binary_shift(n, shift);

    // Subtract shifted 'n' from 'r' until 'r' is less than 'n'
    while (shift >= 0) {
        while (compare_bignum_unsigned(&r, &shifted_n) >= 0) {
            r = sub_unsigned(&r, &shifted_n);
        }
        shifted_n = binary_shift(shifted_n, -1);  // Shift right
        shift--;
    }

    // At this point, 'r' is the remainder of 'a' divided by 'n'
    trim_bignum(&r);
    return r;
}

int expmod_(int base, int exp, int mod) {
    char *exp_bin = int2bin(exp);
    int c = 1;

    for (size_t i = 0; i < strlen(exp_bin); i++) {
        c = (c * c) % mod;
        if (exp_bin[i] == '1') {
            c = (c * base) % mod;
        }
    }

    return c;
}

bignum_t addmod(bignum_t *a, bignum_t *b, bignum_t *n) {
    // First, add a and b
    bignum_t sum = add(a, b);

    // Then, calculate the remainder of sum divided by n
    bignum_t result = bignum_remainder(sum, *n);

    // Clean up intermediate sum if necessary
    free_bignum(&sum);

    return result;
}

bignum_t multmod(bignum_t a, bignum_t b, bignum_t n) {
    // First, multiply a and b
    bignum_t product = mul(&a, &b);

    // Then, calculate the remainder of product divided by n
    bignum_t result = bignum_remainder(product, n);

    // Clean up intermediate product if necessary
    free_bignum(&product);

    return result;
}

bignum_t expmod(bignum_t *a, bignum_t *b, bignum_t *n) {
    bignum_t result = init_big_num(1);
    result.digits[0] = 1;  // Initialize result to 1
    bignum_t base = *a;

    int i;
    for (i = 0; i < b->size; i++) {
        uint8_t bit = b->digits[i];
        if (bit) {
            result = multmod(result, base, *n);
        }
        base = multmod(base, base, *n);
    }

    return result;
}

void resize_bignum(bignum_t *num, size_t new_size) {
    num->digits = (int *)realloc(num->digits, new_size * sizeof(int));
    if (num->digits == NULL) {
        printf("Memory reallocation failed\n");
        exit(1);
    }
    num->size = new_size;
}

bignum_t str2bignum(char *str) {
    int size = strlen(str);
    int max_digits = size * 4;  // Maximum possible digits based on input string length
    bignum_t num = init_big_num(max_digits);

    if (str[0] == '-') {
        num.sign = 1;  // Set sign to negative
        str++;         // Skip the negative sign character
        size--;        // Adjust size to exclude the negative sign
    } else if (str[0] == '+') {
        num.sign = 0;  // Set sign to positive
        str++;         // Skip the negative sign character
        size--;        // Adjust size to exclude the negative sign
    } else {
        num.sign = 0;  // Set sign to positive
    }

    for (int i = 0; i < size; i++) {
        if (str[i] < '0' || str[i] > '9') {
            printf("Invalid character in string: %c\n", str[i]);
            exit(1);
        }

        int digit = str[i] - '0';

        // Multiply existing number by 10 and add the new digit
        int carry = digit;
        for (int j = 0; j < num.size || carry > 0; j++) {
            int value = carry;
            if (j < num.size) value += num.digits[j] * 10;
            num.digits[j] = value % 2;
            carry = value / 2;
        }

        // Update the size of the bignum representation
        if (num.size < max_digits) {
            num.size++;
        }
    }

    // Trim leading zeros
    while (num.size > 1 && num.digits[num.size - 1] == 0) {
        num.size--;
    }

    return num;
}

void reverse_string(uint8_t *str) {
    if (str) {
        char *left = str;
        char *right = str + strlen(str) - 1;
        while (left < right) {
            char tmp = *left;
            *left++ = *right;
            *right-- = tmp;
        }
    }
}

void print_bignum(bignum_t *num) {
    int decimal[MAX_DIGITS] = {0};  // Array to store decimal digits
    int len = num->size;
    int i, j, carry, temp;

    for (i = 0; i < len; i++) {
        int bit = num->digits[len - 1 - i];  // Current binary bit (0 or 1)

        // Add bit*2^i to the decimal number
        carry = bit;
        for (j = 0; j <= i || carry; j++) {
            if (j < MAX_DIGITS) {
                temp = decimal[j] * 2 + carry;
                decimal[j] = temp % 10;
                carry = temp / 10;
            } else {
                break;  // Prevent writing outside the bounds of the array
            }
        }
    }

    // Print the decimal number
    if (num->sign == 1) printf("- ");
    int start = 0;
    for (i = MAX_DIGITS - 1; i >= 0; i--) {
        if (decimal[i] != 0) {
            start = 1;
        }
        if (start) {
            printf("%d", decimal[i]);
        }
    }
    if (!start) {
        printf("0");  // Handle case for zero
    }
    printf("\n");
#ifdef DEBUG
    if (num->sign == 1) printf("-");

    for (int i = num->size - 1; i >= 0; i--) {
        printf("%d", num->digits[i]);
    }
    printf("\n");
#endif
}