#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

static inline void test_multmod() {
    printf("Testing multmod...\n");

    bignum_t a = str2bignum("7");
    bignum_t b = str2bignum("6");
    bignum_t n = str2bignum("11");
    bignum_t result;
    multmod(&result, a, b, n);
    bignum_t expected = str2bignum("9");

    if (compare_bignum(&expected, &result) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&n);
    free_bignum(&result);
    free_bignum(&expected);

    // Additional tests can be added here
    printf("Done testing multmod\n");
}
static inline void test_expmod() {
    printf("Testing expmod...\n");

    bignum_t base = str2bignum("2342");
    bignum_t exp = str2bignum("6762");
    bignum_t n = str2bignum("9343");
    bignum_t result = expmod(&base, &exp, &n);
    bignum_t expected = str2bignum("7147");
    print_bignum(&result);
    if (compare_bignum(&expected, &result) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&base);
    free_bignum(&exp);
    free_bignum(&n);
    free_bignum(&result);
    free_bignum(&expected);

    // Additional tests can be added here
    printf("Done testing expmod\n");
}

static inline void test_extended_gcd() {
    printf("Testing extended_gcd...\n");

    // Test 1: Check gcd of coprime numbers and find inverse modulo
    bignum_t a = str2bignum("7");
    bignum_t b = str2bignum("5");
    bignum_t x = str2bignum("0");
    bignum_t y = str2bignum("0");
    bignum_t gcd = extended_gcd(a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("1");

    if (compare_bignum(&gcd, &expected_gcd) == 0) {
        printf("Test 1 (GCD): OK\n");
    } else {
        printf("Test 1 (GCD): FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);

    a = str2bignum("3");
    b = str2bignum("11");
    x = str2bignum("0");
    y = str2bignum("0");
    gcd = extended_gcd(a, b, &x, &y);
    expected_gcd = str2bignum("1");

    print_bignum(&x);
    print_bignum(&y);

    if (compare_bignum(&gcd, &expected_gcd) == 0) {
        printf("Test 2 (GCD): OK\n");
    } else {
        printf("Test 2 (GCD): FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);

    printf("Done testing extended_gcd\n");
}

static inline void test_inversemod() {
    printf("Testing extended_gcd and inversemod...\n");
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("18");
    bignum_t mod_inverse = inversemod(a, b);
    // To check the correctness of the inversemod, (mod_inverse * a) % b should be 1
    bignum_t product;
    mult_bignum(&product, &mod_inverse, &a);
    bignum_t remainder;
    bignum_remainder(&remainder, &product, &b);
    bignum_t one = str2bignum("1");
    if (compare_bignum(&remainder, &one) == 0) {
        printf("Test 1 (Inverse Mod): OK\n");
    } else {
        printf("Test 1 (Inverse Mod): FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&mod_inverse);
    free_bignum(&product);
    free_bignum(&remainder);
    free_bignum(&one);

    // Test 2: Check gcd and inversemod where gcd is not 1
    a = str2bignum("48");
    b = str2bignum("18");

    // Since gcd is not 1, there should be no modular inverse
    printf("Test 2 (Inverse Mod): Expecting failure message next...\n");
    inversemod(a, b);  // This should trigger an error and exit.

    free_bignum(&a);
    free_bignum(&b);

    // Test3
    a = str2bignum("3");
    b = str2bignum("11");
    bignum_t c = inversemod(a, b);
    bignum_t c_expected = str2bignum("4");

    if (compare_bignum(&c, &c_expected) == 0) {
        printf("Test 3 (Inverse Mod): OK\n");
    } else {
        printf("Test 3 (Inverse Mod): FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
}

// static inline void test_inversemod() {
//     printf("Testing inversemod...\n");
//
//     bignum_t a = str2bignum("3");
//     bignum_t n = str2bignum("11");
//     bignum_t result = inversemod(a, n);
//     bignum_t expected = str2bignum("4");  // 3*4 mod 11 = 1
//
//     if (compare_bignum(&expected, &result) == 0) {
//         printf("Test 1: OK\n");
//     } else {
//         printf("Test 1: FAIL\n");
//     }
//
//     free_bignum(&a);
//     free_bignum(&n);
//     free_bignum(&result);
//     free_bignum(&expected);
//
//     // Additional tests can be added here
//     printf("Done testing inversemod\n");
// }

#endif  // !TESTS_H
