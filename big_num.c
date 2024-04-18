// Author: Pedro Soares (0200566850)
// Use "gcc -I ./include big_num.c -o bignum"
#include "include/big_num.h"

#include "include/tests.h"

#define BASE 10

bignum_t init_bignum(int size) {
    bignum_t num;
    num.size = size;
    // Initialize array with 0's
    num.tab = (int *)calloc(size, sizeof(int));

    if (num.tab == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    return num;
}

bignum_t str2bignum(char *str) {
    if (str == NULL) {
        printf("Invalid string\n");
        exit(1);
    }
    int size = strlen(str);
    bignum_t num = init_bignum(size);

    for (int i = 0; i < size; i++) {
        num.tab[size - i - 1] = str[i] - '0';
    }

    return num;
}

bignum_t int2bignum(int num) {
    if (num == 0) {
        bignum_t result = init_bignum(1);
        result.tab[0] = 0;
        return result;
    }

    // Count number of digits
    int tmp = num;
    int length = 0;
    while (tmp > 0) {
        tmp /= 10;
        length++;
    }

    bignum_t result = init_bignum(length);

    while (num > 0) {
        result.tab[result.size - length] = num % 10;
        num /= 10;
        length--;
    }

    return result;
}

void free_bignum(bignum_t *a) {
    if (a->tab == NULL) {
        printf("Invalid bignum\n");
        exit(1);
    }

    free(a->tab);
}

bignum_t add(bignum_t *a, bignum_t *b) {
    if (a == NULL || b == NULL) {
        printf("Invalid bignum\n");
        exit(1);
    }
    int size = a->size > b->size ? a->size : b->size;
    bignum_t result = init_bignum(size + 1);

    int carry = 0;
    for (int i = 0; i < size; i++) {
        int sum = carry;
        if (i < a->size) sum += a->tab[i];
        if (i < b->size) sum += b->tab[i];

        result.tab[i] = sum % BASE;
        carry = sum / BASE;
    }

    if (carry) {
        result.tab[size] = carry;
    } else {
        result.size = size;
    }

    return result;
}

bignum_t mul(bignum_t *a, bignum_t *b) {
    if (a == NULL || b == NULL) {
        printf("Invalid bignum\n");
        exit(1);
    }
    int size = a->size + b->size;
    bignum_t result = init_bignum(size);

    for (int i = 0; i < a->size; i++) {
        int carry = 0;
        for (int j = 0; j < b->size; j++) {
            int sum = a->tab[i] * b->tab[j] + result.tab[i + j] + carry;
            result.tab[i + j] = sum % BASE;
            carry = sum / BASE;
        }
        result.tab[i + b->size] = carry;
    }

    while (result.size > 1 && result.tab[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

int expmod(int base, int exp, int mod) {
    char *exp_bin = int2bin(exp);
    int c = 1;

    for (int i = 0; i < strlen(exp_bin); i++) {
        c = (c * c) % mod;
        if (exp_bin[i] == '1') {
            c = (c * base) % mod;
        }
    }

    return c;
}

bignum_t fibonacci(int n) {
    bignum_t a = int2bignum(0);
    bignum_t b = int2bignum(1);

    for (int i = 0; i < n; i++) {
        bignum_t tmp = b;
        b = add(&a, &b);
        free_bignum(&a);
        a = tmp;
    }

    free_bignum(&a);

    return b;
}

bignum_t factorial(int n) {
    bignum_t result = int2bignum(1);
    for (int i = 1; i <= n; i++) {
        bignum_t tmp = int2bignum(i);
        bignum_t tmp2 = mul(&result, &tmp);
        free_bignum(&result);
        free_bignum(&tmp);
        result = tmp2;
    }
    return result;
}

int main() {
    test_add();
    test_mul();
    test_fib();
    test_factorial();

    return 0;
}
