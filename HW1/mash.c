//Stephanie Day and Cassie Renz
//Assignment 1 - MASH Shell 
//Due Feb 9th 2018

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>

char **parseCommand(char *cmd, char *filename);
int * forkIt(char** cmd1, char** cmd2, char** cmd3);
void printCmd(char** cmds, int cmdNum, char* filename);


/*
*  Program to take in three user commands that can be executed on the linux command line and a filename
*  Program then forks and runs three exec commands in parallel, quitting gracefully once all have returned to parent
*  Prints the order of launch as well as the time in milliseconds to completion for each command.
*/
int main() {
	char cmd1[255], cmd2[255], cmd3[255], filename[255]; 
	 
	printf("mash-1>");
	fgets(cmd1, sizeof(cmd1), stdin);
	
	
	printf("mash-2>");
	fgets(cmd2, sizeof(cmd2), stdin);
	
	
	printf("mash-3>");
	fgets(cmd3, sizeof(cmd3), stdin);
	
	printf("filename>");
	fscanf(stdin, "%s", filename);

	char ** command1 = parseCommand(cmd1, filename);
	char ** command2 = parseCommand(cmd2, filename);
	char ** command3 = parseCommand(cmd3, filename); 

	printCmd(command1, 1, filename);
	printCmd(command2, 2, filename);
	printCmd(command3, 3, filename);

	int *forkRet = forkIt(command1, command2, command3);

        if (((forkRet[0] >= 60) & (forkRet[1] >= 60)) & ((forkRet[2] > (forkRet[2] - 100)) & (forkRet[2] < (forkRet[2] + 100)))) {  //some voodoo to make sure it only prints when all three children have completed runing
            printf("Done waiting on children: %d, %d, %d\n", forkRet[0], forkRet[1], forkRet[2]);
            printf("exiting..\n");
        }

  if (forkRet[3] == -1) { 
      printf("CMD1:[SHELL 1] STATUS CODE =-1\n");
    }
  
    if (forkRet[4] == -1) { 
      printf("CMD2:[SHELL 2] STATUS CODE =-1\n");
    }
    if (forkRet[5] == -1) { 
      printf("CMD3:[SHELL 3] STATUS CODE =-1\n");
    }
	

}

//Function to split the user inputted sentence into a usable format for execvp
char ** parseCommand (char *cmd, char *filename) { 
	char **newCmd = (char **)malloc((sizeof(char *) * 7));
	for (int i = 0; i < sizeof(newCmd); i++){
		newCmd[0] = (char *)malloc ((255) * sizeof(char));
	}
	char *token;

	int i = 0; 
	token = strtok(cmd, " \n");
	while(token != NULL) { 
		newCmd[i] = token;
		i++; 
		token = strtok(NULL, " \n");
	} 
        newCmd[i] = filename;
	
	return newCmd;
}

//Function to print the initial launch commands with proper dilineations
void printCmd(char** cmds, int cmdNum, char* filename) {
  	int x = 0;
	int buffer = 61;
	printf("-----LAUNCH CMD %d: ", cmdNum);
	while ( cmds[x] != filename) { 
	  char* cmd = cmds[x];
	  for(int i = 0; i < strlen(cmd); i++) {
	    printf("%c", cmd[i]);
	    buffer--;
	  }
	  printf(" ");
	  buffer--;
	  x += 1; 
	}
	for(int i = 0; i < buffer; i++) {
	  printf("-");
	}
	printf("\n");

}

//Function to fork and run exec in parallel
//Prints to screen the exec output along with time in milliseconds
int * forkIt(char** cmd1, char** cmd2, char** cmd3) {
  int * childIds = (int *)malloc((sizeof(int *) * 6));
  int p1 = fork();
  struct timeval timecheck; 
  long start1, start2, start3, end1, end2, end3;
  gettimeofday(&timecheck, NULL);
  start1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
  if (p1 == 0) { // first child
    childIds[3] = execvp(cmd1[0], cmd1);//first child's command HERE
  }
  if (p1 > 0) { // back in the parent
    gettimeofday(&timecheck, NULL);
    start2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
    childIds[0] = p1;
    int p2 = fork();
    if (p2 == 0) {//second child
      childIds[4] = execvp(cmd2[0], cmd2);//second child's command HERE
    }
    if (p2 > 0) { // back in p1
      gettimeofday(&timecheck, NULL);
      start3 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
      childIds[1] = p2;
      int p3 = fork();
      if (p3 == 0) {
	childIds [4] = execvp(cmd3[0], cmd3);//third child's command HERE
      }
      if (p3 > 0) {
	childIds[5] = p3;
	wait(NULL);	
	if (childIds[0] >= 60) { //make sure to only print when the child has finished
          gettimeofday(&timecheck, NULL);
          end1 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
          printf("Result took: %ldms\n", (end1 - start1));
	  printf("--------------------------------------------------------------------------------\n");
        }
      }
      wait(NULL);
      if (childIds[1] >= 60) { //make sure to only print when the child has finished
          gettimeofday(&timecheck, NULL);
          end2 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
          printf("Result took: %ldms\n", (end2 - start2));
	  printf("--------------------------------------------------------------------------------\n");
        }
    }
    wait(NULL);
    if ((childIds[2] > (childIds[0] - 100)) & (childIds[2] < (childIds[0] + 100)) & (childIds[2] >= 60)) { //make sure to only print when the child has finished
      gettimeofday(&timecheck, NULL);
      end3 = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
      printf("Result took: %ldms\n", (end3 - start3));
      printf("--------------------------------------------------------------------------------\n");
    }
    
  }

  return childIds; 
  
}
