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

static inline void test_div() {
    printf("Testing div...\n");

    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("5");
    div_result_t c = div_bignum(&a, &b);

    bignum_t q_c = str2bignum("2");
    bignum_t r_c = str2bignum("0");

    if (compare_bignum(&q_c, &c.quotient) == 0 &&
        compare_bignum(&r_c, &c.remainder) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);

    a = str2bignum("5000");
    b = str2bignum("5000");
    c = div_bignum(&a, &b);

    q_c = str2bignum("1");
    r_c = str2bignum("0");

    if (compare_bignum(&q_c, &c.quotient) == 0 &&
        compare_bignum(&r_c, &c.remainder) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);

    a = str2bignum("25");
    b = str2bignum("3");
    c = div_bignum(&a, &b);

    q_c = str2bignum("8");
    r_c = str2bignum("1");

    if (compare_bignum(&q_c, &c.quotient) == 0 &&
        compare_bignum(&r_c, &c.remainder) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);

    a = str2bignum("32423423523423423433423");
    b = str2bignum("2342342346767456");
    c = div_bignum(&a, &b);

    q_c = str2bignum("13842307");
    r_c = str2bignum("1660367839872431");

    if (compare_bignum(&q_c, &c.quotient) == 0 &&
        compare_bignum(&r_c, &c.remainder) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);

    a = str2bignum("82374982374892374982739847293472983479283478237498");
    b = str2bignum("9283748237458329758324792834729384");
    c = div_bignum(&a, &b);

    q_c = str2bignum("8873030619521053");
    r_c = str2bignum("7430152715228522944387360532516146");

    if (compare_bignum(&q_c, &c.quotient) == 0 &&
        compare_bignum(&r_c, &c.remainder) == 0) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c.quotient);
    free_bignum(&c.remainder);
    free_bignum(&q_c);
    free_bignum(&r_c);

    printf("Done testing mul\n");
}

static inline void test_remainder() {
    printf("Testing remainder...\n");

    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("5");
    bignum_t c = bignum_remainder(a, b);
    bignum_t r_c = str2bignum("0");

    if (compare_bignum(&c, &r_c) == 0) {
        printf("Test 1: OK\n");
    } else {
        printf("Test 1: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);

    a = str2bignum("5000");
    b = str2bignum("5000");
    c = bignum_remainder(a, b);

    r_c = str2bignum("0");

    if (compare_bignum(&c, &r_c) == 0) {
        printf("Test 2: OK\n");
    } else {
        printf("Test 2: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);

    a = str2bignum("25");
    b = str2bignum("3");
    c = bignum_remainder(a, b);

    r_c = str2bignum("1");

    if (compare_bignum(&c, &r_c) == 0) {
        printf("Test 3: OK\n");
    } else {
        printf("Test 3: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);

    a = str2bignum("32423423523423423433423");
    b = str2bignum("2342342346767456");
    c = bignum_remainder(a, b);

    r_c = str2bignum("1660367839872431");

    if (compare_bignum(&c, &r_c) == 0) {
        printf("Test 4: OK\n");
    } else {
        printf("Test 4: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);

    a = str2bignum("82374982374892374982739847293472983479283478237498");
    b = str2bignum("9283748237458329758324792834729384");
    c = bignum_remainder(a, b);

    r_c = str2bignum("7430152715228522944387360532516146");

    if (compare_bignum(&c, &r_c) == 0) {
        printf("Test 5: OK\n");
    } else {
        printf("Test 5: FAIL\n");
    }

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&r_c);
    printf("Done testing remainder\n");
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

static inline void test_addmod() {
    printf("Testing addmod...\n");

    bignum_t a = str2bignum("10");
    bignum_t b = str2bignum("20");
    bignum_t n = str2bignum("4");
    bignum_t result = addmod(&a, &b, &n);
    bignum_t expected = str2bignum("2");

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
    printf("Done testing addmod\n");
}
static inline void test_multmod() {
    printf("Testing multmod...\n");

    bignum_t a = str2bignum("7");
    bignum_t b = str2bignum("6");
    bignum_t n = str2bignum("11");
    bignum_t result = multmod(a, b, n);
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
