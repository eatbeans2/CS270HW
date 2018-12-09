#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_allocv(unsigned num_bytes, int mark, void ** rslt){
  void* init = malloc(num_bytes + sizeof(int) + sizeof(char));
  init = init+sizeof(char) + sizeof(int);
  *(int*)(init - sizeof(int)-sizeof(char)) = num_bytes;
  *(char*)(init - sizeof(char)) = 'q';
  int x;
  for(x = 0; x < num_bytes/sizeof(char); x++){
    ((char*)init)[x] = (char)mark;
  } 
  *rslt = (void*)init;
  if(rslt == NULL)
    return -1;
  if( errno != 0)
    return -2;
  else{
    qmem_addVar(*rslt);
    return 0;
  }
}


