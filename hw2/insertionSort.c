#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "insertionSort.h"

int insertionSort(char** arrays, int stringCount, int stringLength){
  int x;
  for(x = 0; x < stringCount; x++){
    insert(arrays, x, stringCount, stringLength);
  }
  return 0;
}

void insert(char** arrays, int x, int stringCount, int stringLength){
  int y;
  char* buffer = malloc(sizeof(char[stringLength]));
  buffer = strcpy(buffer, arrays[x]);
  int isDone = 0;
  for(y = x-1; y >= 0; y--){
    int curChar;

    if(y==0){
      int z;
      for(z = x-1; z >= 0; z--){
	strcpy(arrays[z+1], arrays[z]);
      }
      strcpy(arrays[0], buffer);
    }
    
    for(curChar = 0; curChar < stringLength; curChar++){
      if(arrays[x][curChar] > arrays[y][curChar]){
	break;	
      }
      
      else if(arrays[y][curChar] > arrays[x][curChar]){
	int z;
	for(z = x-1; z > y; z--){
	  strcpy(arrays[z+1], arrays[z]);
	}
	strcpy(arrays[y+1], buffer);
	isDone = 1;
	break;
      }
    }
    if(isDone == 1)
      break;
  }
  free(buffer);
  return;
}
