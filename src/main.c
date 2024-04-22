#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "random.h"
#include "utils.h"

int main() {
    init_seed();
    bignum_t a;
    bool ok = 0;
    while (ok != 1) {
        genrandom(&a, 20);
        printf("Prime being tested: ");
        print_bignum(&a);
        ok = fermat_test(a, 2);
        if (ok) {
        } else {
            printf("Not prime\n");
        }
        free_bignum(&a);
        printf("a\n");
    }
    // bignum_t a, p, p_1, res;
    // p = str2bignum("386987");
    // p_1 = str2bignum("386986");
    // a = str2bignum("165432");
    // expmod(&res, &a, &p_1, &p);
    // print_bignum(&res);
    //// a = str2bignum("13");
    //// if (fermat_test(a, 50)) {
    ////     printf("PRIME");
    //// } else {
    ////     printf("Not a prime");
    //// }
    free_bignum(&a);
    return 0;
}
