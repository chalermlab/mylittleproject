#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memwatch.h"

#include "utlist.h"

#define BUFLEN 20


/*
 gcc -g -o test -DMEMWATCH -DMEMWATCH_STDIO  memwatch.c single_linked.c
*/

typedef struct el {
  char bname[BUFLEN];
  int foo;
  struct el *next, *prev;
} el;


/* 
The comparison function must return an int that is negative, zero, or positive, which specifies whether the first item should sort before, equal to, or after the second item, respectively. 

   a  before b   => -1
   a  equal to b => 0
   a  after b    => 1
 */
int numbercmp(el *a, el *b) {
    return (a->foo > b->foo);
}

el *head = NULL; /* important- initialize to NULL! */


int add_number(int num) {

  el *number;

  if ( (number = (el*)malloc(sizeof(el))) == NULL)
    exit(-1);
  
    number->foo =num;
    LL_APPEND(head, number);
 }

int add_pre_number(int num) {

  el *number;

  if ( (number = (el*)malloc(sizeof(el))) == NULL)
    exit(-1);
  
    number->foo =num;
    LL_PREPEND(head, number);
}


int main(int argc, char *argv[]) {
  el *number,*number2, *tmp , *del = NULL, *nisse;

    char linebuf[BUFLEN];
    FILE *file;

    if ( (number = (el*)malloc(sizeof(el))) == NULL)
      exit(-1);

    {
      number->foo =1;
      LL_APPEND(head, number);


      if ( (number2 = (el*)malloc(sizeof(el))) == NULL)
	exit(-1);
      number2->foo =13;
      LL_APPEND(head, number2);
    }

    add_number(8);
    add_pre_number(19);

    printf("before sort...\n");
    LL_FOREACH(head,tmp) printf("%d ", tmp->foo);

    LL_SORT(head, numbercmp);
    printf("\nafter sort...\n");
    LL_FOREACH(head,tmp) printf("%d ", tmp->foo);


#if 1
    /* Delete first item */
    nisse = head;
    LL_DELETE(head, head);
    free(nisse);
#endif


#if 1
    /* Delete all items in the list */
    LL_FOREACH(head,tmp) { 
      if (del) 
	free(del);
      printf("deleting: %d\n", tmp->foo);
      del = tmp;
      LL_DELETE(head, tmp);
    }

    if (del) 
      free(del);
#endif


    return 0;
}
