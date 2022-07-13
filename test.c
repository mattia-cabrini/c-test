#include "test.h"

#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  test_r T;

  struct node_t *next;
} *node;

typedef struct {
  test_f f;
  const char *module;
} tester;

node head = NULL;
node tail = NULL;

tester *ts;

int TESTS = 0;

static node create_node(test_r T, node next) {
  node n = (node) malloc( sizeof(struct node_t) );

  n->T = T;
  n->next = next;

  return n;
}

test_r test_r_init(int success, int sequential, const char *module, char *message) {
  test_r T;

  T.success = success;
  T.sequential = sequential;
  T.module = module;
  T.message = message;

  return T;
}

void test_add(test_f f, const char *module) {
  tester *ts2 = (tester *) malloc ( (TESTS + 1) * sizeof(tester) );

  if ( TESTS > 0 ) {
    memcpy(ts2, ts, (TESTS) * sizeof( test_f ));
    free(ts);
  }

  ts2[TESTS].f = f;
  ts2[TESTS].module = module;

  ++TESTS;
  ts = ts2;
}

static void add_result(test_r T) {
  if ( tail == NULL ) {
    head = tail = create_node(T, NULL);
  } else {
    tail->next = create_node(T, NULL);
    tail = tail->next;
  }
}

void test_run() {
  int i;

  for ( i = 0; i < TESTS; ++i ) {
    test_r T = test_r_init(0, -1, ts[i].module, NULL);
    ts[i].f(&T);
    add_result(T);
  }
}

int test_pop(test_r *T) {
  node tmp;

  if ( head == NULL )
    return -1;

  *T = head->T;
  tmp = head->next;
  free(head);
  head = tmp;

  if ( head == NULL )
    tail = NULL;

  return 0;
}

static void free_not_void(void *ptr) {
  if ( ptr != NULL ) free(ptr);
}

void test_r_free(test_r T) {
  free_not_void(T.message);
}

void test_unload() {
  test_r T;

  while ( test_pop(&T) != -1 )
    test_r_free(T);

  free(ts);
  TESTS = 0;
}
