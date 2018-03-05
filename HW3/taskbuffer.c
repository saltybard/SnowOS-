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

int buffer[MAX];
int fill = 0; 
int use = 0; 
int count = 0; 

void put (int value) { 
	buffer[fill] = value; 
	fill = (fill + 1) % MAX; 
	count++;
}

void get () {

}
