#include<stdio.h>
#include<stdlib.h>
#include "qmem.h"
#include "qmem_stats.h"

struct node{
  struct node* next;
  void * address;
};

struct node* head = NULL;

int qmem_stats(unsigned long * num_allocs, unsigned long * num_bytes_alloced){
  struct node* cur = head;
  *num_allocs = 0;
  *num_bytes_alloced = 0;

  while(cur != NULL){
    *num_bytes_alloced = *num_bytes_alloced + *((int*)(cur->address - sizeof(char) - sizeof(int)));
    *num_allocs = *num_allocs + 1;
    cur = cur->next;

  }
  return 0;
}

int qmem_addVar(void * newAddress){
  if(head == NULL){
    head = malloc(sizeof(struct node));
    head->next = NULL;
    head->address = newAddress;
    }
  else{
    struct node* cur = head;
    while(cur->next != NULL){
      cur = cur->next;
    }
    cur->next = malloc(sizeof(struct node));
    cur = cur->next;
    cur->next = NULL;
    cur->address = newAddress;
  }
  return 0;
}

int qmem_delVar(void * oldAddress){
  struct node* cur = head;
  if(cur->address == oldAddress){
    head = head->next;
    free(cur);
  }
  else{
    while(cur->next != NULL && cur->next->address != oldAddress){
      cur = cur->next;
    }
    if(cur->next != NULL){
      struct node* toFree = cur->next;
      cur->next = toFree->next;
      free(toFree);
    }
    else
      return -1;
  }
  return 0;
}

int qmem_findVar(void * searchAddress){
  struct node* cur = head;
  while(cur != NULL){
    if(cur->address == searchAddress)
      return 1;
    else
      cur = cur->next;
  }
  return 0;
}
