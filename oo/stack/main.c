#include <stdio.h>
#include "stack.h"

main () {

  Stack <int> inst;

  
  inst.Push(40);
  inst.Push(4);
  inst.Push(4);
  inst.Push(41);
  printf("%d\n", inst.Pop());
  inst.Peek(1);
}
