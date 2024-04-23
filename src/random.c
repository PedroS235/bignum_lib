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
    int ret = init_bignum_(res, bit_length, 0);
    if (ret || (bit_length == 0)) {
        return ret;
    }
    // Set each bit randomly
    for (int i = 0; i < bit_length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }
    while (res->size > 1 && res->digits[res->size - 1] == 0) {
        res->size--;
    }
    int random_position = rand() % res->size;
    res->digits[random_position] = 1;
    return 0;
}

// Fermat primality test
bool fermat_test(bignum_t p, int iterations) {
    bignum_t temp_p;
    copy_bignum(&temp_p, &p);
    bignum_t one = ONE();
    if (compare_bignum(&p, &one) == 0) {
        free_bignum(&one);
        return 0;  // 1 is not a prime
    }
    bignum_t temp;
    int leng = temp_p.size - 1;
    sub_bignum(&temp, &temp_p, &one);

    for (int i = 0; i < iterations; i++) {
        bignum_t res, a;
        genrandom(&a, leng);  // Needs refinement to ensure a < p
        bignum_t t4;
        printf("DEB\n");
        expmod(&t4, &a, &temp, &p);  // a^(p-1) % p should be 1
        printf("FIN\n");
        copy_bignum(&res, &t4);
        free_bignum(&t4);
        printf("res interior: ");
        print_bignum(&res);

        if (compare_bignum(&res, &one) != 0) {
            free_bignum(&res);
            free_bignum(&one);
            free_bignum(&temp);
            free_bignum(&a);
            return 0;  // Composite found
        }
        free_bignum(&res);
        free_bignum(&a);  // Free a after each loop iteration
    }

    free_bignum(&one);
    free_bignum(&temp);
    return 1;  // Probably prime
}