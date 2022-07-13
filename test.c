#include "test.h"

#include <stdlib.h>
#include <string.h>

typedef struct node_t {
  test_r T;

  struct node_t *next;
} *node;

node head = NULL;
node tail = NULL;

test_f *fs = NULL;
int TESTS = 0;

static node create_node(test_r T, node next) {
  node n = (node) malloc( sizeof(struct node_t) );

  n->T = T;
  n->next = next;

  return n;
}

test_r test_r_init(int success, char *name, char *message) {
  test_r T;

  T.success = success;
  T.message = message;
  T.name = name;

  return T;
}

void test_add(test_f f) {
  test_f *fs2 = (test_f *) malloc ( (TESTS + 1) * sizeof(test_f) );

  if ( TESTS > 0 ) {
    memcpy(fs2, fs, (TESTS) * sizeof( test_f ));
    free(fs);
  }

  fs2[TESTS] = f;

  ++TESTS;
  fs = fs2;
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
    test_r T = test_r_init(0, NULL, NULL);
    fs[i](&T);
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
  free_not_void(T.name);
}

void test_unload() {
  test_r T;

  while ( test_pop(&T) != -1 )
    test_r_free(T);

  free(fs);
  TESTS = 0;
}
