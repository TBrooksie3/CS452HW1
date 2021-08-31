#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "tests.h"

int main() {
  //Deq deqTest = deq_new();
  //int i = 3;
  //int *p = &i;
  //deq_head_put(deqTest, p);
  //printf("%d\n", *(int *)deq_head_get(deqTest));
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}
