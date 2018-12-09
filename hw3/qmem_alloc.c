#include <stdlib.h>
#include "qmem.h"
#include "qmem_stats.h"
#include <errno.h>

int qmem_alloc(unsigned num_bytes, void ** rslt){
  *rslt = malloc(num_bytes+sizeof(int)+sizeof(char)+5);
  *((int*)*rslt) = num_bytes;
  *(char*)(*rslt+sizeof(int)) = 'q';
  *rslt = *rslt+sizeof(int) + sizeof(char);
  if(*rslt == NULL)
    return -1;
  else if(errno != 0){
    //Catch the rest of the errors
    return -2;
  }
  qmem_addVar(*rslt);
  return 0;
}
