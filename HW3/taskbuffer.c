/*
 *  Buffer implementation for producer/consumer task structure
 *  Cassie Renz 
 *  Stephanie Day
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2018
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "taskbuffer.h"

// MAX should defined the size of the bounded buffer 
#define MAX 200
//TODO: Ask if this is okay. if not okay, fix.
char* buffer[MAX];
int fill = 0; 
int use = 0; 
int count = 0; 

void put (char* value) {
  printf("putting value in buffer: %s\n", value); 
	buffer[fill] = value; 
	fill = (fill + 1) % MAX; 
	count++;
}

char* get() {
  char* tmp = buffer[use];
  use = (use + 1) % MAX;
  count--;
  printf("getting value from buffer: %s\n", tmp);
  return tmp;

}

int getCount() {
  return count; 
}

int getMax() { 
	return MAX; 
} 
