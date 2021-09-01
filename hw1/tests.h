#ifndef TESTS_H
#define TESTS_H

int run_tests(void);

int test_create_destroy(void);

int test_deq_len_empty(void);

int test_deq_len_full(void);

int test_put_empty(void);

int test_put_non_empty(void);

int test_get_item(void);

int test_ith(void);

int test_rem_no_item(void);

int test_rem(void);

#endif
