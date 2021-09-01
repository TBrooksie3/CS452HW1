#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
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

// Puts a piece of data (void *) in R (*Rep) at end e (Head (0)/Tail(1))
static void put(Rep r, End e, Data d) {

  Node newNode = (Node)malloc(sizeof(*newNode));
  if (!newNode) {
    ERROR("malloc() failed in put call");
  }
  newNode->data = d;
  newNode->np[Head] = 0;
  newNode->np[Tail] = 0;

  if (r->len == 0) {
    newNode->np[Head] = 0;
    newNode->np[Tail] = 0;
    r->ht[Head] = newNode;
    r->ht[Tail] = newNode;
    r->len++;
    return;
  } else if (e == Head) {
    newNode->np[Tail] = r->ht[Head];
    r->ht[Head]->np[Head] = newNode;
    r->ht[Head] = newNode;
  } else {
    newNode->np[Head] = r->ht[Tail];
    r->ht[Tail]->np[Tail] = newNode;
    r->ht[Tail] = newNode;
  }
  r->len++;
}

static Data ith(Rep r, End e, int i) { return 0; }
static Data get(Rep r, End e) { 
  if (r->len == 1) {
    Node temp = r->ht[e];
    r->ht[Head] = 0;
    r->ht[Tail] = 0;
    r->len--;
    return temp->data;
  }

  Node end = r->ht[e];
  Data data = end->data;

  if (e == Head) {
    r->ht[e] = end->np[Tail];
    r->ht[e]->np[Head] = 0;
    end->np[Tail] = 0;
  } else {
    r->ht[e] = end->np[Head];
    r->ht[e]->np[Tail] = 0;
    end->np[Head] = 0;
  }
  r->len--;
  return data; 
}
static Data rem(Rep r, End e, Data d) { return 0; }

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
