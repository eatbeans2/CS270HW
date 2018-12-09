#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_cmp(void * p1, void * p2, int * diff){
  if(p1 == NULL)
    return -1;
  if(p2 == NULL)
    return -2;
  if(qmem_findVar(p1) == 0)
    return -3;
  if(qmem_findVar(p2) == 0)
    return -4;
  int size1 = *(int*)(p1-sizeof(char)-sizeof(int));
  int size2 = *(int*)(p2-sizeof(char)-sizeof(int));
  int smallersize;
  if(size1 < size2)
    smallersize = size1;
  else
    smallersize = size2;
  *diff = memcmp((char*)p1, (char*)p2, smallersize);
 return 0;
}
