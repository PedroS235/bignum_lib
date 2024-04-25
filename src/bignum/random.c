#include "bignum/random.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bignum/arithmetic.h"
#include "bignum/bignum.h"
#include "bignum/common.h"
#include "bignum/modular_arithmetic.h"

void init_seed() {
    srand(time(NULL));
    return;
}

int genrandom(bignum_t *res, int length) {
    if (length < 0) {
        return FAILURE;
    }
    if (init_bignum(res, length, 0) != SUCCESS) return FAILURE;

    // Set each bit randomly
    for (int i = 0; i < length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }

    // Set the MSB to 1
    res->digits[length - 1] = 1;
    return SUCCESS;
}

bool fermat_test(bignum_t p, int iterations) {
    // Check first if p mod 2 == 0
    if (p.digits[0] == 0) {
        return false;
    }

    // Check if p mod 3 == 0
    bignum_t res = bignum_new();
    bignum_t three, zero;
    zero = ZERO();
    str2bignum(&three, "3");
    bignum_mod(&res, &p, &three);
    if (compare_bignum(&res, &zero) == 0) {
        free_bignum(&res);
        free_bignum(&three);
        free_bignum(&zero);
        return false;
    }

    bignum_t temp_p = bignum_new();
    if (copy_bignum(&temp_p, &p) != SUCCESS) return FAILURE;

    bignum_t one = ONE();
    if (compare_bignum(&p, &one) == 0) {
        free_bignum(&one);
        return 0;  // 1 is not a prime
    }
    bignum_t temp = bignum_new();
    int length = temp_p.size - 1;
    if (sub_bignum(&temp, &temp_p, &one) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&temp_p);
        return false;
    }

    for (int i = 0; i < iterations; i++) {
        bignum_t res = bignum_new();
        bignum_t a = bignum_new();
        if (genrandom(&a, length) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&temp_p);
            free_bignum(&temp);
            return false;
        }
        bignum_t t4 = bignum_new();
        if (expmod(&t4, &a, &temp, &p) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&temp_p);
            free_bignum(&temp);
            free_bignum(&a);
            return false;
        }
        if (copy_bignum(&res, &t4) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&temp_p);
            free_bignum(&temp);
            free_bignum(&a);
            free_bignum(&t4);
            return false;
        }
        free_bignum(&t4);

        if (compare_bignum(&res, &one) != 0) {
            free_bignum(&res);
            free_bignum(&one);
            free_bignum(&temp);
            free_bignum(&a);
            return false;  // Composite found
        }
        free_bignum(&res);
        free_bignum(&a);  // Free a after each loop iteration
    }

    free_bignum(&one);
    free_bignum(&temp);
    return true;  // Probably prime
}

int gen_random_prime(bignum_t *res, int length) {
    bool found = false;
    while (!found) {
        bignum_t a = bignum_new();
        if (genrandom(&a, length) != SUCCESS) return FAILURE;

        if (fermat_test(a, 10)) {
            if (copy_bignum(res, &a) != SUCCESS) {
                free_bignum(&a);
                return FAILURE;
            }
            found = true;
        }
        free_bignum(&a);
    }
    return SUCCESS;
}

int gen_random_coprime(bignum_t *e, bignum_t *phi) {
    bignum_t one = ONE();
    bignum_t two = bignum_new();
    str2bignum(&two, "2");

    while (true) {
        free_bignum(e);
        if (genrandom(e, phi->size) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&two);
            return FAILURE;
        }

        if (compare_bignum(e, &one) == 0) {
            continue;
        }

        if (compare_bignum(e, phi) >= 0) {
            continue;
        }

        bignum_t x = bignum_new();
        bignum_t y = bignum_new();

        bignum_t gcd = bignum_new();
        if (extended_gcd(&gcd, *e, *phi, &x, &y) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&two);
            free_bignum(&gcd);
            free_bignum(&x);
            free_bignum(&y);
            return FAILURE;
        }

        if (compare_bignum(&gcd, &one) == 0) {
            free_bignum(&one);
            free_bignum(&two);
            free_bignum(&gcd);
            free_bignum(&x);
            free_bignum(&y);
            return SUCCESS;
        }

        free_bignum(&gcd);
    }
}
