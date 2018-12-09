#include <stdlib.h>
#include <stdio.h>
#include "qmem.h"
#include "qmem_stats.h"

int qmem_free(void ** data){
  if(*data == NULL)
    return -1;
  if(data == NULL)
    return -2;
  if(qmem_findVar(*data) == 0)
    return -3;
  printf("Attempting Free...\n");
  char* allocated = *data - sizeof(char) - sizeof(int);
  free(allocated);
  printf("Current address: %p\n", *data);
  qmem_delVar(*data);
  *data = NULL;
  if(*data == NULL){
    printf("Pointer freed in function...\n");
    return 0;
  }
  else
    return -1;
}
