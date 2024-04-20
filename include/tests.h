#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

#include "big_num.h"

static inline void test_add() {
    printf("Testing add...\n");
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("1");
    bignum_t c = add(&a, &b);
    if (compare_bignum(&b, &c) == 0) {
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
    if (compare_bignum(&expected, &c) == 0) {
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
    if (compare_bignum(&expected, &c) == 0) {
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

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    // Starting negative tests
    a = str2bignum("-10");
    b = str2bignum("-5");
    c = add(&a, &b);
    expected = str2bignum("-15");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("20");
    b = str2bignum("-100");
    c = add(&a, &b);
    expected = str2bignum("-80");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 6: OK\n");
    } else {
        printf("Test 6: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    printf("Done testing add\n");
}

static inline void test_sub() {
    printf("Testing sub...\n");

    bignum_t a = str2bignum("1");
    bignum_t b = str2bignum("0");
    bignum_t c = sub(&a, &b);
    if (compare_bignum(&a, &c) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);

    a = str2bignum("10");
    b = str2bignum("5");
    c = sub(&a, &b);
    bignum_t expected = str2bignum("5");
    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("5");
    b = str2bignum("10");
    c = sub(&a, &b);
    expected = str2bignum("-5");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("36893488147419103230");
    b = str2bignum("18446744073709551615");
    c = sub(&a, &b);
    expected = str2bignum("18446744073709551615");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    // Negative tests
    a = str2bignum("-36893488147419103230");
    b = str2bignum("18446744073709551615");
    c = sub(&a, &b);
    expected = str2bignum("-55340232221128654845");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("-36893488147419103230");
    b = str2bignum("-18446744073709551615");
    c = sub(&a, &b);
    expected = str2bignum("-18446744073709551615");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 6: OK\n");
    } else {
        printf("Test 6: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    printf("Done testing sub\n");
}

static inline void test_mul() {
    printf("Testing mul...\n");

    bignum_t a = str2bignum("1");
    bignum_t b = str2bignum("0");
    bignum_t c = mul(&a, &b);

    if (compare_bignum(&b, &c) == 0) {
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

    if (compare_bignum(&expected, &c) == 0) {
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

    if (compare_bignum(&expected, &c) == 0) {
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

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("10");
    b = str2bignum("-5");
    c = mul(&a, &b);
    expected = str2bignum("-50");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("-10");
    b = str2bignum("5");
    c = mul(&a, &b);
    expected = str2bignum("-50");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 6: OK\n");
    } else {
        printf("Test 6: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    a = str2bignum("-5");
    b = str2bignum("-5");
    c = mul(&a, &b);
    expected = str2bignum("25");

    if (compare_bignum(&expected, &c) == 0) {
        printf("Test 7: OK\n");
    } else {
        printf("Test 7: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&expected);

    printf("Done testing mul\n");
}

static inline void test_compare() {
    printf("Testing Compare...\n");
    bignum_t a = str2bignum("0");
    bignum_t b = str2bignum("0");

    if (compare_bignum(&a, &b) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("10");
    b = str2bignum("0");

    if (compare_bignum(&a, &b) == 1) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("0");
    b = str2bignum("10");

    if (compare_bignum(&a, &b) == -1) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("-1");
    b = str2bignum("10");

    if (compare_bignum(&a, &b) == -1) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("10");
    b = str2bignum("-10");

    if (compare_bignum(&a, &b) == 1) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("-10");
    b = str2bignum("-10");

    if (compare_bignum(&a, &b) == 0) {
        printf("Test 6: OK\n");
    } else {
        printf("Test 6: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("-5");
    b = str2bignum("-10");

    if (compare_bignum(&a, &b) == 1) {
        printf("Test 7: OK\n");
    } else {
        printf("Test 7: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("-10");
    b = str2bignum("-5");

    if (compare_bignum(&a, &b) == -1) {
        printf("Test 8: OK\n");
    } else {
        printf("Test 8: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    a = str2bignum("-33333");
    b = str2bignum("33333");

    if (compare_bignum(&a, &b) == -1) {
        printf("Test 9: OK\n");
    } else {
        printf("Test 9: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);

    printf("Done testing Compare\n");
}

#endif  // !TESTS_H
