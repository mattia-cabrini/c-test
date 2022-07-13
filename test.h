#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct {
  int success;
  char *message;
  char *name;
} test_r;

typedef void(*test_f)(test_r *);

extern test_r test_r_init(int, char *name, char *message);
extern void   test_add(test_f);
extern void   test_run();
extern int    test_pop(test_r*);
extern void   test_r_free(test_r);
extern void   test_unload();

#endif // TEST_H_INCLUDED
