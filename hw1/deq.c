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

static Data ith(Rep r, End e, int i) { 
  Node next = r->ht[e];
  int j;
  
  for (j = 0;j < i; j++) {
     if (e == Head) {
      next = next->np[Tail];
    } else {
        next = next->np[Head];
    }
  }
  return next->data;
}

static Data get(Rep r, End e) { 
  if (r->len == 1) {
    Node temp = r->ht[e];
    r->ht[Head] = 0;
    r->ht[Tail] = 0;
    r->len--;
    free(r->ht[e]);
    return temp->data;
  }

  Node end = r->ht[e];
  Data data = end->data;

  if (e == Head) {
    r->ht[e] = end->np[Tail];
    r->ht[e]->np[e] = 0;
    end->np[Tail] = 0;
    end->np[Head] = 0;
  } else {
    r->ht[e] = end->np[Head];
    r->ht[e]->np[Tail] = 0;
    end->np[Tail] = 0;
    end->np[Head] = 0;
  }
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
            if (e == Head) {
              return get(r, Tail);
            } else {
              return get(r, Head);
            }
        } else {
          if (e == Head) {
            prev->np[Tail] = current->np[Tail];
            current->np[Tail]->np[Head] = prev;
            current->np[Head] = 0;
            current->np[Tail] = 0;
            r->len--;
            Data data = current->data;
            free(current);
            return data;
          } else {
            prev->np[Head] = current->np[Head];
            current->np[Head]->np[Tail] = prev;
            current->np[Tail] = 0;
            current->np[Head] = 0;
            r->len--;
            Data data = current->data;
            free(current);
            return data;
          }
        }
      } else {
        prev = current;
        if (e == Head) {
          current = current->np[Tail];
        } else {
          current = current->np[Head];
        }
      }
  }
  return 0;
}

static Rep rep(Deq q) {
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
