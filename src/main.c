#include "bignum/bignum.h"
#include "bignum/common.h"
#include "bignum/random.h"
#include "stdio.h"

int main() {
    init_seed();

    bignum_t a = bignum_new();
    gen_random_prime(&a, 104);

    print_bignum(&a);

    printf("Big number library\n");
    return 0;
}
