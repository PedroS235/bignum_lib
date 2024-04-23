#include <stdio.h>
#include <string.h>

#include "bignum.h"

int main() {
    init_seed();
    bool ok = 0;
    while (!ok) {
        bignum_t a;
        genrandom(&a, 1024);

        if (fermat_test(a, 10)) {
            printf("PRIME");
            print_bignum(&a);
            ok = 1;
        } else {
            printf("Not a prime");
        }
        free_bignum(&a);
    }
    return 0;
}
