#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "tests.c"

int main() {
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}