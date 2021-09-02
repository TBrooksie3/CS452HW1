#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
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

static void put(Rep r, End e, Data d) {
  Node newNode = (Node)malloc(sizeof(*newNode));
  if (!newNode) {
    ERROR("malloc() failed in put call");
  }
  newNode->data = d;
  newNode->np[e] = 0;
  newNode->np[!e] = 0;

  if (r->len == 0) {
    newNode->np[e] = 0;
    newNode->np[!e] = 0;
    r->ht[e] = newNode;
    r->ht[!e] = newNode;
    r->len++;
    return;
  } else {
    newNode->np[!e] = r->ht[e];
    r->ht[e]->np[e] = newNode;
    r->ht[e] = newNode;
  }
  r->len++;
}

static Data ith(Rep r, End e, int i) { 
  Node next = r->ht[e];
  int j;
  
  for (j = 0;j < i; j++) {
    next = next->np[!e];
  }
  return next->data;
}

static Data get(Rep r, End e) { 
  if (r->len == 1) {
    Node temp = r->ht[e];
    r->ht[e] = 0;
    r->ht[!e] = 0;
    r->len--;
    free(r->ht[e]);
    return temp->data;
  }

  Node end = r->ht[e];
  Data data = end->data;

  r->ht[e] = end->np[!e];
  r->ht[e]->np[e] = 0;
  end->np[!e] = 0;
  end->np[e] = 0;

  r->len--;
  free(end);
  return data; 
}

static Data rem(Rep r, End e, Data d) { 
  Node current = r->ht[e];
  Node prev = 0;
  int i;
  for (i = 0; i < r->len; i++) {
      if (current->data == d) {
        if (i == 0 || r->len == 1) {
          return get(r, e);
        } else if (i == (r->len - 1)) {
          return get(r,!e);
        } else {
          prev->np[!e] = current->np[!e];
          current->np[!e]->np[e] = prev;
          current->np[e] = 0;
          current->np[!e] = 0;
          r->len--;
          Data data = current->data;
          free(current);
          return data;
        }
      } else {
        prev = current;
        current = current->np[!e];
      }
  }
  return 0;
}

extern Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

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
