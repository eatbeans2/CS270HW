#include<stdlib.h>
#include<stdio.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_scrub(void * data){
  if(data == NULL)
    return -1;
  if(qmem_findVar(data) == 0)
    return -2;

  int x;
  for(x = 0; x < (*(int*)(data-sizeof(char)-sizeof(int)))/sizeof(int); x++){
    ((int*)data)[x] = 0;
  }

  return 0;
}
