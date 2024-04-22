#include <random.h>
#include <time.h>

void init_seed() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    srand(ts.tv_nsec);
    return;
}

int genrandom(bignum_t *res, int bit_length) {
    int ret = init_bignum_(res, bit_length, POS);
    if (ret) {
        return ret;
    }
    // Set each bit randomly
    for (int i = 0; i < bit_length; i++) {
        res->digits[i] = rand() % 2;  // Each digit is only a single bit, set to 0 or 1
    }
    return 0;
}