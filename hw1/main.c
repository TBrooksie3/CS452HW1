#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "tests.h"
#include "error.h"

// helper function to print list if data type is int
void print_list(Deq deqTest) {
  Node head = rep(deqTest)->ht[Head];
  printf("%d\n", *(int *)head->data);
  Node next = head->np[Tail];
  while (next) {
    printf("%d\n", *(int *)next->data);
    next = next->np[Tail];
  }
}

// main function to run tests
int main() {
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}
