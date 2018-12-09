#include <stdlib.h>
#include <stdio.h>
#include "qmem.h"

int main(){
  int errc;
  struct qbuf {int indx; char data[256]};
  struct qbuf * p = NULL;
  struct qbuf * q = NULL;
  struct qbuf * j = NULL;
  struct qbuf * k = NULL;
  errc = qmem_allocv(sizeof(struct qbuf), 'q', (void **)&p);
  errc = qmem_allocv(sizeof(struct qbuf), 'p', (void**)&q);
  errc = qmem_alloc(sizeof(struct qbuf), (void**)&j);
  errc = qmem_alloc(sizeof(struct qbuf), (void**)&k);
  if(errc != 0){
    printf("Something went wrong: %d\n", errc);
    printf("Contents of pointer: ");
    int x;
    for(x = 0; x < sizeof(struct qbuf)/sizeof(char); x++){
      printf("%c \n", ((char*)p)[x]);
    }
    printf("\n");
  }
  else{
    printf("Nothing went wrong\n");
    printf("Contents of pointer: ");
    int x;
    for(x = 0; x < sizeof(struct qbuf)/sizeof(char); x++){
      printf("%c", ((char*)p)[x]);
    }
    printf("\n");
  }

  printf("Size of pointer: %d\n", *(int*)((void*)p-sizeof(int)-sizeof(char)));
  int* diff = malloc(sizeof(int));
  *diff = 0;
  int errorvar = 0;
  errorvar = qmem_cmp(p, q, diff);
  printf("Difference between strings: %d\n", *diff);

  printf("Copying string named 'q' (contains p's) to string j\n");
  qmem_cpy(j, q);

  printf("Contents of j: ");
  int x;
  for(x = 0; x < sizeof(struct qbuf)/sizeof(char); x++){
    printf("%c", ((char*)j)[x]);
  }
  printf("\n");

  printf("Scrubbing k\n");
  qmem_scrubv(k, 'q');
  printf("Contents of k: ");
  for(x = 0; x < sizeof(struct qbuf)/sizeof(char); x++){
    printf("%c", ((char*)k)[x]);
  }
  printf("\n");

  unsigned* sizeK = malloc(sizeof(int));
  *sizeK = 0;
  int err3 = qmem_size(k, sizeK);
  printf("Size of k: %d \n", *sizeK);

  unsigned long* num_allocs = malloc(sizeof(unsigned long));
  unsigned long* num_bytes_alloced = malloc(sizeof(unsigned long));
  qmem_stats(num_allocs, num_bytes_alloced);

  printf("Total allocations: %lu, total bytes: %lu \n", *num_allocs, *num_bytes_alloced);

  printf("Freeing data...\n");
  qmem_free((void**)&p);
  qmem_free((void**)&q);
  qmem_free((void**)&j);
  qmem_free((void**)&k);
  if((void*)p == NULL)
    printf("Freed data\n");
  else
    printf("Address in freed pointer: %p", p);
  return 0;
}
