/*
 * File: tests.c
 * Author: Taylor Brooks
 * Date: Sat 28 Aug 2021
 * Description: Unit tests for double ended doubly linked list
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "deq.h"
#include "error.h"

// test create destroy deq
int test_create_destroy(void){
  char testName[] = "Create Destroy Test";
  Deq deqTest = deq_new();

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

  Deq deqTest = deq_new();

  if (deq_len(deqTest)) {
    fprintf(stderr, "%s failed: Deq length should be 0 but is %d\n", testName, deq_len(deqTest));
    return 1;
  }

  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// create deq with 1, 2, 3, 4 from head to tail
Deq create_deq_4_items() {
  int i = 1; int j = 2; int k = 3; int x = 4;
  int *p1 = &i; int *p2 = &j; int *p3 = &k; int *p4 = &x;
  Deq deqTest = deq_new();
  deq_head_put(deqTest, p4);
  deq_head_put(deqTest, p3);
  deq_head_put(deqTest, p2);
  deq_head_put(deqTest, p1);
  
  return deqTest;
}

// test get deq length of deq with items
int test_deq_len_full(void) {
  char testName[] = "Deq Length 4 Item List Test";

  Deq deqTest = create_deq_4_items();
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
  int i = 3;
  int *p = &i;
  Deq deqTest = deq_new();
  deq_head_put(deqTest, p); 

  if (*(int *)(deq_head_get(deqTest)) != 3) {
    fprintf(stderr, "%s failed: Deq head put/get failed %d\n", testName, deq_len(deqTest));
    return 1;
  }
  
  i = 4;
  deq_tail_put(deqTest, p); 
  
  if (*(int *)(deq_tail_get(deqTest)) != 4) {
    fprintf(stderr, "%s failed: Deq tail put/get failed%d\n", testName, deq_len(deqTest));
    return 1;
  }
  deq_del(deqTest, 0);
  fprintf(stderr, "%s passed\n", testName);
  return 0;
}

// test put with items in list (both head and tail)
// test put with null item
// test get with empty list (both head and tail)
// test get with items in list (both head and tail)
// test ith with empty list (both head and tail / negative number and nonexistent positive index)
// test ith with items in list (both head and tail / negative number and nonexistent positive index and existent index)
// test rem with empty list (both head and tail) 
// test rem with null item
// test rem with items in list (both head and tail / check item not null)
// test deq_map/deq_del/deq_st with a simple function????



// function to run all tests
// returns 0 if all tests passed otherwise nonzero if fail
int run_tests(void) {
  int status = 0;
  status += test_create_destroy();
  status += test_put_empty();
  status += test_deq_len_empty();
  status += test_deq_len_full();

  return status;
}
