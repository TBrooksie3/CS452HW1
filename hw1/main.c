#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "tests.h"

// main function to run tests
int main() {
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}
