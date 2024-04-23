#include <random.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arithmetic.h"
#include "common.h"
#include "modular_arithmetic.h"

void init_seed() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);
    return;
}

int genrandom(bignum_t *res, int length) {
    if (length < 0) {
        return FAILURE;
    }
    int ret = init_bignum(res, length, 0);
    if (ret != SUCCESS) {
        return FAILURE;
    }
    // Set each bit randomly
    for (int i = 0; i < length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }

    // Set the MSB to 1
    res->digits[length - 1] = 1;
    return SUCCESS;
}

bool fermat_test(bignum_t p, int iterations) {
    bignum_t temp_p;
    if (copy_bignum(&temp_p, &p) != SUCCESS) return FAILURE;

    bignum_t one = ONE();
    if (compare_bignum(&p, &one) == 0) {
        free_bignum(&one);
        return 0;  // 1 is not a prime
    }
    bignum_t temp;
    int length = temp_p.size - 1;
    if (sub_bignum(&temp, &temp_p, &one) != SUCCESS) {
        free_bignum(&one);
        free_bignum(&temp_p);
        return false;
    }

    for (int i = 0; i < iterations; i++) {
        bignum_t res, a;
        if (genrandom(&a, length) != SUCCESS) {
            free_bignum(&one);
            free_bignum(&temp_p);
            free_bignum(&temp);
            return false;
        }
        bignum_t t4;
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
        bignum_t a;
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
