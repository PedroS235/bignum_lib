// Author: Pedro Soares (0200566850)
#ifndef TESTS_H
#define TESTS_H

#include "big_num.h"

static inline void test_add() {
    printf("Testing add...\n");
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("1");
    bignum_t c = add(&a, &b);
    if (cmp_bignum(&b, &c) == 0) {
        printf("Test 1 : OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);

    a = str2bignum("10");
    b = str2bignum("5");
    c = add(&a, &b);
    bignum_t expected = str2bignum("15");
    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("999");
    b = str2bignum("1");
    c = add(&a, &b);
    expected = str2bignum("1000");
    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    // Max uint64_t value
    a = str2bignum("18446744073709551615");
    b = str2bignum("18446744073709551615");
    c = add(&a, &b);
    expected = str2bignum("36893488147419103230");

    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    printf("Done testing add\n");
}

static inline void test_mul() {
    printf("Testing mul...\n");

    bignum_t a = str2bignum("1");
    bignum_t b = str2bignum("0");
    bignum_t c = mul(&a, &b);

    if (cmp_bignum(&b, &c) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);

    a = str2bignum("10");
    b = str2bignum("5");
    c = mul(&a, &b);
    bignum_t expected = str2bignum("50");

    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("999");
    b = str2bignum("2");
    c = mul(&a, &b);
    expected = str2bignum("1998");

    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("18446744073709551615");
    b = str2bignum("18446744073709551615");
    c = mul(&a, &b);
    expected = str2bignum("340282366920938463426481119284349108225");

    if (cmp_bignum(&expected, &c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    printf("Done testing mul\n");
}

static inline void test_expmod() {
    printf("Testing expmod...\n");

    int b = 2;
    int e = 3;
    int m = 10;
    int r = expmod(b, e, m);
    if (r == 8) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    b = 2;
    e = 4;
    m = 10;
    r = expmod(b, e, m);
    if (r == 6) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    b = 2342;
    e = 6762;
    m = 9343;
    r = expmod(b, e, m);
    if (r == 7147) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }
}

void test_fib() {
    printf("Testing fib...\n");
    bignum_t a = fibonacci(0);
    bignum_t b = str2bignum("1");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = fibonacci(1);
    b = str2bignum("1");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = fibonacci(10);
    b = str2bignum("89");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = fibonacci(100);
    b = str2bignum("573147844013817084101");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    printf("Done testing fib\n");
}

void test_factorial() {
    printf("Testing factorial...\n");

    bignum_t a = factorial(0);
    bignum_t b = str2bignum("1");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = factorial(1);
    b = str2bignum("1");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = factorial(10);
    b = str2bignum("3628800");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = factorial(30);
    b = str2bignum("265252859812191058636308480000000");
    if (cmp_bignum(&a, &b) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    printf("Done testing factorial\n");
}

#endif  // !TESTS_H
