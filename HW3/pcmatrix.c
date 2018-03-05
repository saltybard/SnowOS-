/*
 *  Matrix Task Processor
 *  Based on Operating Systems: Three Easy Pieces by R. Arpaci-Dusseau and A. Arpaci-Dusseau
 * 
 *  Assignment 3 code
 *  Program operates on tasks submitted to the tasks_input directory
 *  Results are created in the tasks_output directory
 *
 *  A bounded buffer is used to store pending tasks
 *  A producer thread reads tasks from the tasks_input directory 
 *  Consumer threads perform tasks in parallel
 *  Program is designed to run as a daemon (i.e. forever) until receiving a request to exit.
 *
 *  This program mimics the client/server processing model without the use of any networking constructs.
 *
 *  Wes J. Lloyd
 *  University of Washington, Tacoma
 *  TCSS 422 - Operating Systems
 *  Spring 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>
#include "matrix.h"
#include "tasks.h"
#include "pcmatrix.h"
#include "taskbuffer.h"

void * producer(void *arg) { 
    readtasks(arg); 
		return NULL;
}


int main (int argc, char * argv[])
{
  //variable to hold passed in millisecond argument
  int ms = 0;
	int rc; 
	pthread_t p1, p2, p3;
  if (argc == 2) {
    ms = strtol(argv[1], NULL,10); 
  } else {
    ms = 500;
  }

  printf("millisecond arg: %d\n", ms);
  
  // Uncomment to see example operation of the readtasks() routine
  //readtasks((void *)ms);  

  //Uncomment to see example operation of the dotasks() routine
  //dotasks((void *) NULL);

  // To do
  // Use pthreads
  // Create one pthread for readtasks()
  rc = pthread_create(&p1, NULL, producer, ms); assert(rc ==0);
  //
  // Create one or more pthreads for dotasks()
  return 0;
}
