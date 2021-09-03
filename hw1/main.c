// /*
//  * File: main.c
//  * Author: Taylor Brooks & Professor Jim Buffenbarger
//  * Date: Sat 28 Aug 2021
//  * Description: Main source file to use implementation of deq and run tests
//  */
#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "tests.h"

int main() {
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}
