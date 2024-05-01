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

    printf("|------------------------------------------------------------------|\n");
    printf(
        "| This is an example of our big number library, where we encrypt   |\n| and "
        "decrypt a message using RSA.                                 |\n");

    printf("|                                                                  |\n");

    printf(
        "| This project has been developed by Pedro Soares and Issam Jomaa, |\n| "
        "part "
        "of Algorithms for Numbers & Public-Key Cryptography course. |\n");
    printf("|------------------------------------------------------------------|\n");

    printf("\nGenerating RSA keys...\n");

    rsa_keygen(&n, &e, &d, 20);

    printf("n: ");
    print_bignum(&n);

    printf("e: ");
    print_bignum(&e);

    printf("d: ");
    print_bignum(&d);
    printf("\n");

    bignum_t m = bignum_new();
    str2bignum(&m, "1234567890");

    printf("Encrypting message -> ");
    print_bignum(&m);
    bignum_t c = bignum_new();
    rsa_encrypt(&c, &m, &n, &e);

    printf("Encrypted message -> ");
    print_bignum(&c);
    printf("\n");

    printf("Decrypting -> ");
    print_bignum(&c);
    bignum_t decrypted = bignum_new();
    rsa_decrypt(&decrypted, &c, &n, &d);

    printf("Decrypted message -> ");
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
