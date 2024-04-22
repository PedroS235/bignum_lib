#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "random.h"
#include "utils.h"

int main() {
    init_seed();
    bignum_t a;
    if (genrandom(&a, 2048)) {
        return 1;
    };
    print_bignum(&a);
    free_bignum(&a);

    return 0;
}
