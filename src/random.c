#include <random.h>
#include <stdio.h>
#include <time.h>

#include "arithmetic.h"
#include "utils.h"
void init_seed() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);
    return;
}

int genrandom(bignum_t *res, int bit_length) {
    int ret = init_bignum_(res, bit_length, POS);
    if (ret || (bit_length == 0)) {
        return ret;
    }
    // Set each bit randomly
    for (int i = 0; i < bit_length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }
    int random_position = rand() % bit_length;
    res->digits[random_position] = 1;
    return 0;
}

// Fermat primality test
bool fermat_test(bignum_t p, int iterations) {
    bignum_t one = ONE();
    if (compare_bignum(&p, &one) == 0) {
        free_bignum(&one);
        return 0;  // 1 is not a prime
    }
    bignum_t temp;

    sub_bignum(&temp, &p, &one);

    for (int i = 0; i <= iterations; i++) {
        bignum_t res, a;
        genrandom(&a, p.size - 1);  // Needs refinement to ensure a < p
        printf("p_inside: ");
        print_bignum(&p);
        printf("a: ");
        print_bignum(&a);
        printf("p-1: ");
        print_bignum(&temp);

        expmod(&res, &a, &temp, &p);  // a^(p-1) % p should be 1
        printf("res: ");
        print_bignum(&res);

        if (compare_bignum(&res, &one) != 0) {
            free_bignum(&one);
            free_bignum(&temp);
            free_bignum(&res);
            free_bignum(&a);
            return 0;  // Composite found
        }
        free_bignum(&a);  // Free a after each loop iteration
        free_bignum(&res);
    }

    free_bignum(&one);
    free_bignum(&temp);
    return 1;  // Probably prime
}