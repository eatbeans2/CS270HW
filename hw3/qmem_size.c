#include<stdio.h>
#include<stdlib.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_size(void * data, unsigned * rslt){
  if(data == NULL)
    return -1;
  if(qmem_findVar(data) == 0)
    return -2;
  *rslt = *(int*)(data-sizeof(char)-sizeof(int));
  return 0;
}
