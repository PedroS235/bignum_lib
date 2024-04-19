#include "big_num.h"

#include <stdlib.h>
#include <string.h>

#define BASE 2

bignum_t init_big_num(int size) {
  bignum_t num;
  num.size = size;
  num.tab = (int *)calloc(size, sizeof(int));

  if (num.tab == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  return num;
}

char *int2bin(int num) {
  size_t size = sizeof(int) * 8;
  char *result = (char *)calloc(size + 1, sizeof(char));
  if (result == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  for (int i = size - 1; i >= 0; i--) {
    result[i] = (num & 1) + '0';
    num >>= 1;
  }

  // Truncate leading zeros
  int i = 0;
  while (result[i] == '0') {
    i++;
  }

  if (i == size) {
    result[0] = '0';
    result[1] = '\0';
  } else {
    char *tmp = (char *)calloc(size + 1 - i, sizeof(char));
    if (tmp == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    strcpy(tmp, result + i);
    free(result);
    result = tmp;
  }

  return result;
}

bignum_t str2bignum(char *str) {
  int size = strlen(str);
  bignum_t num = init_big_num(size);

  for (int i = 0; i < size; i++) {
    num.tab[size - i - 1] = str[i] - '0';
  }

  return num;
}

bignum_t int2bignum(int num) {
  if (num == 0) {
    bignum_t result = init_big_num(1);
    result.tab[0] = 0;
    return result;
  }

  int tmp = num;
  int length = 0;
  while (tmp > 0) {
    tmp /= 10;
    length++;
  }

  bignum_t result = init_big_num(length);

  while (num > 0) {
    result.tab[result.size - length] = num % 10;
    num /= 10;
    length--;
  }

  return result;
}

void print_bignum(bignum_t *a) {
  for (int i = a->size - 1; i >= 0; i--) {
    printf("%d", a->tab[i]);
  }
  printf("\n");
}

void free_bignum(bignum_t *a) { free(a->tab); }

int compare_bignum(bignum_t *a, bignum_t *b) {
  if (a->size > b->size)
    return 1;
  if (a->size < b->size)
    return -1;
  for (int i = a->size - 1; i >= 0; i--) {
    if (a->tab[i] > b->tab[i])
      return 1;
    if (a->tab[i] < b->tab[i])
      return -1;
  }
  return 0;
}

bignum_t add(bignum_t *a, bignum_t *b) {
  int size = a->size > b->size ? a->size : b->size;
  bignum_t result = init_big_num(size + 1);

  int carry = 0;
  for (int i = 0; i < size; i++) {
    int sum = carry;
    if (i < a->size)
      sum += a->tab[i];
    if (i < b->size)
      sum += b->tab[i];

    result.tab[i] = sum % 10;
    carry = sum / 10;
  }

  if (carry) {
    result.tab[size] = carry;
  } else {
    result.size = size;
  }

  return result;
}

bignum_t sub(bignum_t *a, bignum_t *b) {
  int size = a->size > b->size ? a->size : b->size;
  if (compare_bignum(a, b) < 0) {
    return sub(b, a);
  }
  bignum_t result = init_big_num(size);

  int carry = 0;
  for (int i = 0; i < size; i++) {
    int sum = carry;
    if (i < a->size)
      sum += a->tab[i];
    if (i < b->size)
      sum -= b->tab[i];

    if (sum < 0) {
      sum += 10;
      carry = -1;
    } else {
      carry = 0;
    }

    result.tab[i] = sum;
  }

  while (result.size > 1 && result.tab[result.size - 1] == 0) {
    result.size--;
  }

  return result;
}

bignum_t mul(bignum_t *a, bignum_t *b) {
  int size = a->size + b->size;
  bignum_t result = init_big_num(size);

  for (int i = 0; i < a->size; i++) {
    int carry = 0;
    for (int j = 0; j < b->size; j++) {
      int sum = a->tab[i] * b->tab[j] + result.tab[i + j] + carry;
      result.tab[i + j] = sum % 10;
      carry = sum / 10;
    }
    result.tab[i + b->size] = carry;
  }

  while (result.size > 1 && result.tab[result.size - 1] == 0) {
    result.size--;
  }

  return result;
}

bignum_t binary_shift(bignum_t a, int shift) {
  bignum_t result = init_big_num(a.size + shift);
  memcpy(result.tab + shift, a.tab, a.size * sizeof(int));
  return result;
}

bignum_t div_bignum(bignum_t *a, bignum_t *b) {
  bignum_t zero = int2bignum(0);
  if (compare_bignum(b, &zero) == 0) {
    printf("Division by zero\n");
    exit(1);
  }

  bignum_t q = int2bignum(0);
  bignum_t r = int2bignum(0);

  for (int i = 0; i < a->size; i++) {
    r = binary_shift(r, 1);
    r.tab[0] = a->tab[i];
    if (compare_bignum(&r, b) >= 0) {
      r = sub(&r, b);
      q.tab[i] = 1;
    }
  }

  print_bignum(&q);
  print_bignum(&r);

  return r;
}

int expmod_(int base, int exp, int mod) {
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
