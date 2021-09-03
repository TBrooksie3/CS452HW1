// /*
//  * File: deq.c
//  * Author: Taylor Brooks & Professor Jim Buffenbarger
//  * Date: Sat 28 Aug 2021
//  * Description: Doubly linked list source file that implements all necessary list functions
//  *              Taylor Brooks - Doubly linked list put/get/ith/rem function implementations
//  *              Professor Jim Buffenbarger - Other functions
//  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

/* put: generic put data function that appends data on a specific end of the list
 * r - Rep structure that represents the list
 * e - enum either Head (0) or Tail (1) to append to
 * d - Data that is going to be attached to a Node and inserted
 * 
 * returns - void
 *         - Error on putting null data
 */
static void put(Rep r, End e, Data d) {
  if (!r) {
    ERROR("Deq is null");
  }
  if (!d) {
    ERROR("cannot put null data");
  }
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

/* ith: generic ith data function that returns (but does not remove) the data of the ith object in list from a specific end
 * r - Rep structure that represents the list
 * e - enum either Head (0) or Tail (1) to start counting from
 * i - int index to remove from specific end (end is index 0)
 * 
 * returns - Data the data in the node at the specific index from the end
 *         - Error on ith from empty list or i that is < 0 or > list length
 */
static Data ith(Rep r, End e, int i) { 
  if (!r) {
    ERROR("Deq is null");
  }
  if (r->len == 0) {
    ERROR("Cannot ith from empty list");
  }
  if (i < 0 || i >= r->len) {
    ERROR("Cannot call ith with negative index or greater than or equal to list length");
  }
  Node next = r->ht[e];
  int j;
  
  for (j = 0;j < i; j++) {
    next = next->np[!e];
  }
  return next->data;
}

/* get: generic get data function that removes and returns the data from a specific end.
 * r - Rep structure that represents the list
 * e - enum either Head (0) or Tail (1) to remove from
 * 
 * returns - Data the data in the node at the specific end
 *         - Error on getting from empty list
 */
static Data get(Rep r, End e) { 
  if (!r) {
    ERROR("Deq is null");
  }
  if (r->len == 0) {
    ERROR("Cannot get from empty list");
  }
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

/* rem: generic rem data function that searches the list for a specific data and removes and returns the data
 * r - Rep structure that represents the list
 * e - enum either Head (0) or Tail (1) to start search from
 * d - Data index to remove from specific end (end is index 0)
 * 
 * returns - Data that is going to be searched for or 0/null if not found
 *         - Error on rem from empty list
 */
static Data rem(Rep r, End e, Data d) { 
  if (!r) {
    ERROR("Deq is null");
  }
  if (!d) {
    ERROR("Cannot get null data");
  }
  if (r->len == 0) {
    ERROR("Cannot rem from empty list");
  }
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
