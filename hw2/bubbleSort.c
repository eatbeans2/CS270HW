#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bubbleSort.h"

int bubbleSort(char** arrays, int arraySize, int stringSize){
  int needsSwap = 1;
  int x;
  int loops = 0;
  
  while(needsSwap == 1){
    needsSwap = 0;
    loops++;
    //if(loops%100 == 0)
    //printf("# of loops: %d \n", loops);
    for(x = 0; x < arraySize-1; x++){
      if(checkValues(arrays[x],arrays[x+1], stringSize) == 1){
	needsSwap = 1;
	char* buffer = malloc(sizeof(stringSize));
	buffer = strcpy(buffer, arrays[x]);
	arrays[x] = strcpy(arrays[x], arrays[x+1]);
	arrays[x+1] = strcpy(arrays[x+1], buffer);
	free(buffer);
	//printf("Swapped strings \n");
      }
    }
  }

  return 0;
}

int checkValues(char* word1, char* word2, int stringSize){
  int needsSwap = 0;
  int x;
  for(x = 0; x < stringSize; x++){
    if(word1[x] > word2[x]){
      break;
    }
    if(word2[x] > word1[x]){
      needsSwap = 1;
      break;
    }
  }
  return needsSwap;
}
