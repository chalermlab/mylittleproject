#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef void (*ListNodeDestructor)( void * );

typedef struct liststruct {
  ListNodeDestructor DestructFunc;
  struct liststruct *next;
  } list, *plist;

plist add_2_list( plist head, void * data, size_t datasize,ListNodeDestructor Destructor );

void *get_current_node( plist head );

void *get_next_node( plist head );

void DeleteList( plist head );


