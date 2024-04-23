#include "bignum.h"
#include "common.h"
#include "random.h"

int main() {
    init_seed();
    bignum_t res;
    gen_random_prime(&res, 6);

    print_bignum(&res);
    return 0;
}
