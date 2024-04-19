#include "big_num.h"
#include "tests.h"

int main() {
  test_add();
  test_sub();
  test_mul();

  char *bin = int2bin(10);
  printf("%s\n", bin);

  free(bin);

  return 0;
}
