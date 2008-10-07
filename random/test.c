
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
  /* initialize random generator */
  srand ( time(NULL) );

  /* generate random numbers */
  printf("RAND_MAX = ", RAND_MAX);
  
  printf ("A number between 0 and RAND_MAX : %d\n", rand());
  
  printf ("A number between 0 and 99: %d\n", rand() % 100);
  
  printf ("A number between 0 and 9: %d\n", rand() % 10);

  printf ("A number between 0 and 0xffff: %x\n", rand() % 0xffffffff);

  return 0;
}
