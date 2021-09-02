#ifndef TESTS_H
#define TESTS_H

typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

extern Rep rep(Deq q);

extern int run_tests(void);

extern int test_create_destroy(void);

extern int test_deq_len_empty(void);

extern int test_deq_len_full(void);

extern int test_put_empty(void);

extern int test_put_non_empty(void);

extern int test_get_item(void);

extern int test_ith(void);

extern int test_rem_no_item(void);

extern int test_rem(void);

#endif
