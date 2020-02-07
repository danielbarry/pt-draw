#include "pt-draw.c"

#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define ASSERT(x,s) {x ? ++pass : ++fail; printf("  %s %s::%i %s\n", (x ? "[ OK ]  " : "  [FAIL]"), __FUNCTION__, __LINE__, s);}

int pass;
int fail;

int main(){
  /* Setup global variables */
  pass = fail = 0;
  /* Perform tests */
  ASSERT(TRUE, "test");
  ASSERT(FALSE, "hello");
  /* Print result */
  printf("%i / %i PASS\n", pass, pass + fail);
  printf("%i / %i FAIL\n", fail, pass + fail);
  /* Test was successful */
  return fail <= 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
