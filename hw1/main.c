#include <stdio.h>
#include <stdlib.h>

#include "deq.h"
#include "tests.h"
#include "error.h"
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

void print_list(Deq deqTest) {
  Node head = rep(deqTest)->ht[Head];
  printf("%d\n", *(int *)head->data);
  Node next = head->np[Tail];
  while (next) {
    printf("%d\n", *(int *)next->data);
    next = next->np[Tail];
  }
}

int main() {
  // Deq deqTest = deq_new();
  // int i = 3; int j = 2; int k = 1;
  // int *p3 = &i; int *p2 = &j; int *p1 = &k;
  // deq_head_put(deqTest, p3);
  // print_list(deqTest);
  // deq_head_put(deqTest, p2);
  // print_list(deqTest);
  // deq_head_put(deqTest, p1);
  // print_list(deqTest);
  // printf("%d\n", *(int *)deq_tail_get(deqTest));

  // print_list(deqTest);

  // deq_del(deqTest, 0);
  int status = run_tests();
  printf("Tests completed with status: %d\n", status);
  return 0;
}
