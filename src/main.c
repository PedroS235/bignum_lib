#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

int main() {
    bignum_t a = str2bignum("35");
    bignum_t b = str2bignum("15");
    bignum_t x;
    bignum_t y;
    bignum_t gcd;
    extended_gcd(&gcd, a, b, &x, &y);
    bignum_t expected_gcd = str2bignum("5");
    bignum_t expected_x = str2bignum("1");
    bignum_t expected_y = str2bignum("-2");

    print_bignum(&gcd);
    print_bignum(&x);
    print_bignum(&y);

    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&x);
    free_bignum(&y);
    free_bignum(&gcd);
    free_bignum(&expected_gcd);
    free_bignum(&expected_x);
    free_bignum(&expected_y);

    return 0;
}
