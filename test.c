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

test_r test_r_init(int success, const char *str) {
  int len = strlen(str);
  test_r T;

  T.success = success;

  T.error = (char *) malloc( (len + 1) * sizeof(char) );
  strcpy(T.error, str);

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
    test_r T;
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

void test_r_free(test_r T) {
  if ( T.error != NULL )
    free(T.error);
}

void test_unload() {
  test_r T;

  while ( test_pop(&T) != -1 )
    test_r_free(T);

  free(fs);
  TESTS = 0;
}
