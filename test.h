#ifndef TEST_H_INCLUDED
#define TEST_H_INCLUDED

typedef struct {
  int success;
  int sequential;
  char *message;
  const char *module;
} test_r;

typedef void(*test_f)(test_r *);

extern test_r test_r_init(int success, int sequential, const char *module, char *message);
extern void   test_add(test_f f, int sequential, const char *module);
extern void   test_run();
extern int    test_pop(test_r*);
extern void   test_r_free(test_r);
extern void   test_unload();

#endif // TEST_H_INCLUDED
