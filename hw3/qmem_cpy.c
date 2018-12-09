#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_cpy(void * dst, void * src){
  if(dst == NULL)
    return -1;
  if(src == NULL)
    return -2;
  if(qmem_findVar(dst) == 0)
    return -3;
  if(qmem_findVar(src) == 0)
    return -4;
  if(dst == src)
    return -5;
  if(*((int*)(dst-sizeof(char)-sizeof(int))) !=  *((int*)(src-sizeof(char)-sizeof(int))))
    return -6;

  memcpy(dst, src, *(int*)(dst-sizeof(char)-sizeof(int)));

  return 0;
  

}
