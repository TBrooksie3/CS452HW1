// /*
//  * File: deq.h
//  * Author: Taylor Brooks & Professor Jim Buffenbarger
//  * Date: Sat 28 Aug 2021
//  * Description: Doubly linked list (deq) header file where functions and types are declared
//  *              Taylor Brooks - Moved type definitions to header file as well as adding rep function to be used in tests
//  *              Professor Jim Buffenbarger - Other functions/type declarations
//  */
#ifndef DEQ_H
#define DEQ_H

typedef void *Deq;
typedef void *Data;

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

extern Deq deq_new();
extern int deq_len(Deq q);

extern void deq_head_put(Deq q, Data d);
extern Data deq_head_get(Deq q);
extern Data deq_head_ith(Deq q, int i);
extern Data deq_head_rem(Deq q, Data d);

extern void deq_tail_put(Deq q, Data d);
extern Data deq_tail_get(Deq q);
extern Data deq_tail_ith(Deq q, int i);
extern Data deq_tail_rem(Deq q, Data d);

typedef char *Str;
typedef void (*DeqMapF)(Data d);
typedef Str  (*DeqStrF)(Data d);

extern void deq_map(Deq q, DeqMapF f); // foreach
extern void deq_del(Deq q, DeqMapF f); // free
extern Str  deq_str(Deq q, DeqStrF f); // toString

#endif
