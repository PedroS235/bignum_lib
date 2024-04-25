#include "bignum/bignum.h"
#include "bignum/common.h"
#include "bignum/random.h"
#include "rsa.h"
#include "stdio.h"

int main() {
    init_seed();

    bignum_t n = bignum_new();
    bignum_t e = bignum_new();
    bignum_t d = bignum_new();

    printf("Generating RSA keys...\n");

    rsa_keygen(&n, &e, &d, 20);

    printf("n: ");
    print_bignum(&n);
    printf("\n");

    printf("e: ");
    print_bignum(&e);
    printf("\n");

    printf("d: ");
    print_bignum(&d);
    printf("\n");

    bignum_t m = bignum_new();
    str2bignum(&m, "1234567890");

    bignum_t c = bignum_new();
    rsa_encrypt(&c, &m, &n, &e);

    printf("Encrypted message: ");
    print_bignum(&c);
    printf("\n");

    bignum_t decrypted = bignum_new();
    rsa_decrypt(&decrypted, &c, &n, &d);

    printf("Decrypted message: ");
    print_bignum(&decrypted);
    printf("\n");

    free_bignum(&n);
    free_bignum(&e);
    free_bignum(&d);
    free_bignum(&m);
    free_bignum(&c);
    free_bignum(&decrypted);

    return 0;
}
