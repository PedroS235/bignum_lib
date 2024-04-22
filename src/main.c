#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "random.h"
#include "utils.h"

int main() {
    init_seed();
    bignum_t a;
    // bool ok;
    // while (ok != 1) {
    //     genrandom(&a, 100);
    //     ok = fermat_test(a, 2);
    //     free_bignum(&a);
    //     printf("a");
    // }
    // print_bignum(&a);
    // free_bignum(&a);
    a = str2bignum("13");
    if (fermat_test(a, 1)) {
        printf("PRIME");
    } else {
        printf("Not a prime");
    }
    free_bignum(&a);
    return 0;
}
