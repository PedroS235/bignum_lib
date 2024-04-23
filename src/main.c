#include "common.h"
#include "modular_arithmetic.h"
#include "random.h"

int main() {
    init_seed();
    bignum_t res, base, exp, mod;
    genrandom(&base, 4048);
    genrandom(&exp, 2048);
    genrandom(&mod, 2048);

    // gen_random_prime(&res, 6);

    expmod(&res, &base, &exp, &mod);
    print_bignum(&res);

    free_bignum(&res);
    free_bignum(&base);
    free_bignum(&exp);
    free_bignum(&mod);
    return 0;
}
