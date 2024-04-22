#include <string.h>

#include "arithmetic.h"
#include "bignum.h"
#include "utils.h"

int main() {
    bignum_t a = str2bignum("3402823669209384634");
    bignum_t b = str2bignum("-18446744073709551615");
    bignum_t n = str2bignum("1042");
    bignum_t c;
    multmod_bignum(&c, &a, &b, &n);
    print_bignum(&c);
    bignum_t expected = str2bignum("736");
    // CU_ASSERT(compare_bignum(&c, &expected) == 0)
    free_bignum(&a);
    free_bignum(&b);
    free_bignum(&c);
    free_bignum(&n);
    free_bignum(&expected);

    return 0;
}
