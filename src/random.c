#include <random.h>
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
    if (ret) {
        return ret;
    }
    // Set each bit randomly
    for (int i = 0; i < bit_length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }
    return 0;
}

// Fermat primality test
bool fermat_test(bignum_t p, int iterations) {
    bignum_t one = ONE();
    if (compare_bignum(&p, &one) == 0) {
        free_bignum(&one);
        return 0;  // 1 is not a prime
    }
    bignum_t zero = ZERO();
    free_bignum(&one);
    bignum_t temp, res, a, temp1;
    copy_bignum(&temp1, &p);
    for (int i = 0; i < iterations; i++) {
        bignum_t one = ONE();
        sub_bignum(&temp, &p, &one);  // p-1, used in exponentiation
        // Generate a random number a, 1 < a < p
        genrandom(&a, p.size - 1);  // Needs refinement to ensure a < p
        // Ensure a is greater than 1 and less than p
        if (compare_bignum(&a, &zero) == 0) {
            free_bignum(&one);
            free_bignum(&temp1);
            free_bignum(&temp);
            free_bignum(&res);
            free_bignum(&a);
            continue;  // Regenerate a if it's not in the range (1, p)
        }

        expmod(&res, &a, &temp, &temp1);  // a^(p-1) % p should be 1
        print_bignum(&a);
        print_bignum(&temp);
        print_bignum(&temp1);
        print_bignum(&res);
        abs_bignum(&res);
        if (compare_bignum(&res, &one) != 0) {
            free_bignum(&one);
            free_bignum(&temp1);
            free_bignum(&temp);
            free_bignum(&res);
            free_bignum(&a);
            return 0;  // Composite found
        }
        free_bignum(&one);
        free_bignum(&temp);
        free_bignum(&a);  // Free a after each loop iteration
        free_bignum(&res);
    }
    free_bignum(&temp1);
    return 1;  // Probably prime
}