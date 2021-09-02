#ifndef TESTS_H
#define TESTS_H

int run_tests(void);

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
