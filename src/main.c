#include <stdio.h>
#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "random.h"
#include "utils.h"

int main() {
    init_seed();
    bool ok = 0;
    while (!ok) {
        bignum_t a;
        genrandom(&a, 100);

        if (fermat_test(a, 10)) {
            printf("PRIME");
            print_bignum(&a);
            ok = 1;
        } else {
            printf("Not a prime");
        }
        free_bignum(&a);
    }
    // bignum_t a, p, p_1, res;
    // p = str2bignum("386987");
    // p_1 = str2bignum("386986");
    // a = str2bignum("165432");
    // expmod(&res, &a, &p_1, &p);
    // print_bignum(&res);
    // bignum_t a;
    // a = str2bignum(
    //    "125404852237341444108408392400596567118029983907145309055005310112300788777145"
    //    "2303242165494509435517");
    // if (fermat_test(a, 2)) {
    //    printf("PRIME");
    //} else {
    //    printf("Not a prime");
    //}
    // free_bignum(&a);
    return 0;
}
