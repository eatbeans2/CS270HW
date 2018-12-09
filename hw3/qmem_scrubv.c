#include<stdlib.h>
#include<stdio.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_scrubv(void * data, int mark){
  if(data == NULL)
    return -1;
  if(qmem_findVar(data) == 0)
    return -2;

  int x;
  for(x = 0; x < (*(int*)(data-sizeof(char)-sizeof(int)))/sizeof(char); x++){
    ((char*)data)[x] = (char)mark;
  }

  return 0;

}
