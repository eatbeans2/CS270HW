#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bubbleSort.h"
#include "insertionSort.h"
#include "quickSort.h"

const int STRINGCOUNT = 262144;
//const int STRINGCOUNT = 20000;
const int LINESIZE = 256;

char*** stringArray;

int initializeArray(char** arrays);

int main(){
  
  clock_t start1, start2, start3, end1, end2, end3;

  stringArray = malloc(sizeof(char**)*3);
  stringArray[0] = malloc(sizeof(char*)*STRINGCOUNT);
  stringArray[1] = malloc(sizeof(char*)*STRINGCOUNT);
  stringArray[2] = malloc(sizeof(char*)*STRINGCOUNT);
  initializeArray(stringArray[0]);
  initializeArray(stringArray[1]);
  initializeArray(stringArray[2]);

  printf("%s", stringArray[2][262143]);
  start2 = clock();
  insertionSort(stringArray[0], STRINGCOUNT, LINESIZE);
  end2 = clock();

  printf("Insertion Sort Time: %f \n", ((double)(end2-start2)/CLOCKS_PER_SEC));

  start1 = clock();
  bubbleSort(stringArray[1], STRINGCOUNT, LINESIZE);
  end1 = clock();

  printf("Bubble Sort Time: %f \n", ((double)(end1-start1)/CLOCKS_PER_SEC));
  
  start3 = clock();
  quickSort(stringArray[2], STRINGCOUNT, LINESIZE, 0, STRINGCOUNT-1);
  end3 = clock();
  
  printf("Quick Sort Time: %f \n", ((double)(end3-start3)/CLOCKS_PER_SEC));
  
  return 0;

}

int initializeArray(char** arrays){
  const char* filename = malloc(sizeof("hw2data.txt"));
  filename = "hw2data.txt";
  const char* readtype = malloc(sizeof("r"));
  readtype = "r";

  size_t lineSize = LINESIZE;

  FILE *fp;
  fp = fopen(filename, readtype);

  int i;
  for(i = 0; i < STRINGCOUNT; i++){
    arrays[i] = malloc(sizeof(char)*LINESIZE);
    getline(&(arrays[i]), &lineSize, fp);
  }

  fclose(fp);
  
  return 0;

}
