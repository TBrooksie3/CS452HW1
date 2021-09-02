// /*
//  * File: tests.c
//  * Author: Taylor Brooks
//  * Date: Sat 28 Aug 2021
//  * Description: Unit tests for double ended doubly linked list
//  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "tests.h"

// instantiating global variables for use in create_4_item_deq()
int i = 1; int j = 2; int k = 3; int x = 4;
int *p1 = &i; int *p2 = &j; int *p3 = &k; int *p4 = &x;
Deq deqTest;

// helper function to print list of ints
void print_list(Deq deqTest) {
  Node head = rep(deqTest)->ht[Head];
  printf("%d\n", *(int *)head->data);
  Node next = head->np[Tail];
  while (next) {
    printf("%d\n", *(int *)next->data);
    next = next->np[Tail];
  }
}

// create list with 1,2,3,4 from head to tail
Deq create_4_item_deq() {
  deqTest = deq_new();
  deq_head_put(deqTest, p4);
  deq_head_put(deqTest, p3);
  deq_head_put(deqTest, p2);
  deq_head_put(deqTest, p1);
  return deqTest;
}


// test create destroy deq
int test_create_destroy(void){
  char testName[] = "Create Destroy Test";
  deqTest = deq_new();

  if (!deqTest) {
    fprintf(stderr, "%s failed: Deq could not be created\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test get deq length of empty deq
int test_deq_len_empty(void) {
  char testName[] = "Deq Length Empty List Test";

  deqTest = deq_new();

  if (deq_len(deqTest)) {
    fprintf(stderr, "%s failed: Deq length should be 0 but is %d\n", testName, deq_len(deqTest));
    return 1;
  }

  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test get deq length of deq with items
int test_deq_len_full(void) {
  char testName[] = "Deq Length 4 Item List Test";
  deqTest = create_4_item_deq();
  if (deq_len(deqTest) != 4) {
    fprintf(stderr, "%s failed: Deq length should be 4 but is %d\n", testName, deq_len(deqTest));
    return 1;
  }

  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test put with empty list (both head and tail)
int test_put_empty(void) {
  char testName[] = "Put in Empty List Test";

  //test for head put
  int i = 3;
  int *p = &i;
  deqTest = deq_new();
  deq_head_put(deqTest, p); 
  
  Node head = rep(deqTest)->ht[Head];
  Node tail = rep(deqTest)->ht[Tail];
  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  if (*(int *)(head->data) != 3 && *(int *)(tail->data) != 3) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  if (head->np[Head] != 0 || head->np[Tail] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }

  if (tail->np[Head] != 0 || tail->np[Tail] != 0) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  //test for tail put
  i = 4;
  p = &i;
  deqTest = deq_new();
  deq_tail_put(deqTest, p); 
  
  head = rep(deqTest)->ht[Head];
  tail = rep(deqTest)->ht[Tail];
  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  if (*(int *)(head->data) != 4 || *(int *)(tail->data) != 4) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  if (head->np[Head] != 0 || head->np[Tail] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }

  if (tail->np[Head] != 0 || tail->np[Tail] != 0) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test put with items in list (both head and tail)
int test_put_non_empty(void) {
  char testName[] = "Put in Non Empty List Test";

  //test for head put
  deqTest = create_4_item_deq();

  int y = 5;
  int *p = &y; 
  
  deq_head_put(deqTest, p);

  Node head = rep(deqTest)->ht[Head];
  Node tail = rep(deqTest)->ht[Tail];

  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  if (*(int *)(head->data) != 5 || *(int *)(tail->data) != 4) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  if (*(int *)(head->np[Tail]->data) != 1 || head->np[Head] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }
  
  if (tail->np[Tail] != 0 || *(int *)(tail->np[Head]->data) != 3) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  //test for tail put
  deqTest = create_4_item_deq();

  int z = 6;
  int *p100 = &z; 
  
  deq_tail_put(deqTest, p100);

  head = rep(deqTest)->ht[Head];
  tail = rep(deqTest)->ht[Tail];

  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  if (*(int *)(head->data) != 1 || *(int *)(tail->data) != 6) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  if (*(int *)(head->np[Tail]->data) != 2 || head->np[Head] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }
  
  if (tail->np[Tail] != 0 || *(int *)(tail->np[Head]->data) != 4) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test get with item (both head and tail)
int test_get_item(void) {
  char testName[] = "Get Item Test";
  deqTest = create_4_item_deq();

  if (*(int *)(deq_head_get(deqTest)) != 1) {
    fprintf(stderr, "%s failed: Deq head get failed\n", testName);
    return 1;
  }

  if (*(int *)(deq_tail_get(deqTest)) != 4) {
    fprintf(stderr, "%s failed: Deq tail get failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test ith with items in list (both head and tail)
int test_ith(void) {
  char testName[] = "Get Ith Item Test";
  deqTest = create_4_item_deq();

  if (*(int *)(deq_head_ith(deqTest, 1)) != 2) {
    fprintf(stderr, "%s failed: Deq head ith failed\n", testName);
    return 1;
  }

  if (*(int *)(deq_tail_ith(deqTest, 1)) != 3) {
    fprintf(stderr, "%s failed: Deq tail ith failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test rem with item not in list (both head and tail) 
int test_rem_no_item(void) {
  char testName[] = "Rem No Item Test";
  deqTest = create_4_item_deq();

  int y = 5;
  int *p5 = &y;

  if ((deq_head_rem(deqTest, p5)) != 0) {
    fprintf(stderr, "%s failed: Deq head rem failed\n", testName);
    return 1;
  }

  if ((deq_tail_rem(deqTest, p5)) != 0) {
    fprintf(stderr, "%s failed: Deq tail rem failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test rem with item in list
int test_rem(void) {
  
  char testName[] = "Rem Test";
  deqTest = create_4_item_deq();

  if (*(int *)(deq_head_rem(deqTest, p3)) != 3) {
    fprintf(stderr, "%s failed: Deq head rem failed\n", testName);
    return 1;
  }

  if (*(int *)(deq_tail_rem(deqTest, p2)) != 2) {
    fprintf(stderr, "%s failed: Deq tail rem failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// function to run all tests
// returns 0 if all tests passed otherwise nonzero if fail
int run_tests(void) {
  int status = 0;
  status += test_create_destroy();
  status += test_deq_len_empty();
  status += test_deq_len_full();
  status += test_put_empty(); 
  status += test_put_non_empty();
  status += test_get_item();
  status += test_ith();
  status += test_rem_no_item();
  status += test_rem();

  return status;
}

