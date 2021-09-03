// /*
//  * File: tests.c
//  * Author: Taylor Brooks
//  * Date: Sat 28 Aug 2021
//  * Description: Unit tests for double ended doubly linked list source file.
//  *              Includes new declaration of rep function if "make try" is wanted to be used to use a 100% bug free implementation of deq.c
//  *              This must be uncommented because in the other implementation rep is a static function that cannot be used outside deq.c
//  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"
#include "tests.h"

// // only include if trying "make try"
// extern Rep rep(Deq q) {
//   if (!q) ERROR("zero pointer");
//   return (Rep)q;
// }

// instantiating global variables for use in create_4_item_deq()
int i = 1; int j = 2; int k = 3; int x = 4;
int *p1 = &i; int *p2 = &j; int *p3 = &k; int *p4 = &x;
Deq deqTest;

/* put_list: helper function that prints the list if and only if int pointers were stored inside
 * deqTest - Deq that represents the list
 * 
 * returns - void
 */
void print_list(Deq deqTest) {
  Node head = rep(deqTest)->ht[Head];
  printf("%d\n", *(int *)head->data);
  Node next = head->np[Tail];
  while (next) {
    printf("%d\n", *(int *)next->data);
    next = next->np[Tail];
  }
}

/* create_4_item_deq: helper function that creates a list with 1,2,3,4 in it from head to tail
 * 
 * returns - Deq list with int pointers as data
 */
Deq create_4_item_deq() {
  deqTest = deq_new();
  deq_head_put(deqTest, p4);
  deq_head_put(deqTest, p3);
  deq_head_put(deqTest, p2);
  deq_head_put(deqTest, p1);
  return deqTest;
}

/* test_create_destroy: tests creating an empty deq and destroying it
 * 
 * returns - int 0 if pass and 1 if fail
 */
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

/* test_deq_len_empty: tests if deq_len function returns 0 with an empty list
 * 
 * returns - int 0 if pass and 1 if fail
 */
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

/* test_deq_len_full: tests if deq_len function returns 4 on 4 item list
 * 
 * returns - int 0 if pass and 1 if fail
 */
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

/* test_put_empty: tests putting in an empty list from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_put_empty(void) {
  char testName[] = "Put in Empty List Test";

  //test for head put
  int i = 3;
  int *p = &i;
  deqTest = deq_new();
  deq_head_put(deqTest, p); 
  
  Node head = rep(deqTest)->ht[Head];
  Node tail = rep(deqTest)->ht[Tail];

  // check if head and tail are null
  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  // check if head contains 3 and tail contains 3
  if (*(int *)(head->data) != 3 && *(int *)(tail->data) != 3) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  // check if head next and previous pointers are still null
  if (head->np[Head] != 0 || head->np[Tail] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }

  // check if tail next and previous pointers are still null
  if (tail->np[Head] != 0 || tail->np[Tail] != 0) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  //test for tail put with same checks as above
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

/* test_put_non_empty: tests putting in a non empty list from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_put_non_empty(void) {
  char testName[] = "Put in Non Empty List Test";

  //test for head put
  deqTest = create_4_item_deq();

  int y = 5;
  int *p = &y; 
  
  deq_head_put(deqTest, p);

  Node head = rep(deqTest)->ht[Head];
  Node tail = rep(deqTest)->ht[Tail];

  // check if head and tail are not null
  if (tail == 0 || head == 0) {
     fprintf(stderr, "%s failed: head or tail are 0/null\n", testName);
     return 1;
  }

  // check if head data is 5 and tail data is 4
  if (*(int *)(head->data) != 5 || *(int *)(tail->data) != 4) {
    fprintf(stderr, "%s failed: head or tail are not correct value\n", testName);
    return 1;
  }

  // ensure head next is 1 and previous is null
  if (*(int *)(head->np[Tail]->data) != 1 || head->np[Head] != 0) {
    fprintf(stderr, "%s failed: head next and/or previous are incorrect\n", testName);
    return 1;
  }
  
  // ensure tail next is null and previous is 3
  if (tail->np[Tail] != 0 || *(int *)(tail->np[Head]->data) != 3) {
    fprintf(stderr, "%s failed: tail next and/or previous are incorrect\n", testName);
    return 1;
  }

  deq_del(deqTest, 0);

  //test for tail put with same checks as above
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

/* test_get_item: tests getting an item from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_get_item(void) {
  char testName[] = "Get Item Test";
  deqTest = create_4_item_deq();

  // check data on head is 1
  if (*(int *)(deq_head_get(deqTest)) != 1) {
    fprintf(stderr, "%s failed: Deq head get failed\n", testName);
    return 1;
  }

  // check data on tail is 4
  if (*(int *)(deq_tail_get(deqTest)) != 4) {
    fprintf(stderr, "%s failed: Deq tail get failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

/* test_ith: tests getting the ith item from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_ith(void) {
  char testName[] = "Get Ith Item Test";
  deqTest = create_4_item_deq();

  // check if 1st index from head is 2
  if (*(int *)(deq_head_ith(deqTest, 1)) != 2) {
    fprintf(stderr, "%s failed: Deq head ith failed\n", testName);
    return 1;
  }

  // check if 1st index from tail is 3
  if (*(int *)(deq_tail_ith(deqTest, 1)) != 3) {
    fprintf(stderr, "%s failed: Deq tail ith failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

/* test_rem_no_item: tests removing item with rem that is not in list from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_rem_no_item(void) {
  char testName[] = "Rem No Item Test";
  deqTest = create_4_item_deq();

  int y = 5;
  int *p5 = &y;

  // ensure from head it returns 0/null
  if ((deq_head_rem(deqTest, p5)) != 0) {
    fprintf(stderr, "%s failed: Deq head rem failed\n", testName);
    return 1;
  }

  // ensure from tail it returns 0/null
  if ((deq_tail_rem(deqTest, p5)) != 0) {
    fprintf(stderr, "%s failed: Deq tail rem failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

/* test_rem_no_item: tests removing item with rem that is in list from head and tail
 * 
 * returns - int 0 if pass and 1 if fail
 */
int test_rem(void) {
  
  char testName[] = "Rem Test";
  deqTest = create_4_item_deq();

  // ensure from head it returns the data it checked for (3)
  if (*(int *)(deq_head_rem(deqTest, p3)) != 3) {
    fprintf(stderr, "%s failed: Deq head rem failed\n", testName);
    return 1;
  }

  // ensure from tail it returns the data it checked for (2)
  if (*(int *)(deq_tail_rem(deqTest, p2)) != 2) {
    fprintf(stderr, "%s failed: Deq tail rem failed\n", testName);
    return 1;
  }
  
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

/* run_tests: function that calls all above functions
 * 
 * returns - int overall status from all tests run
 */
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

