#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char **parseCommand(char *cmd, char *filename);
void forkIt(char** cmd1, char** cmd2, char** cmd3);



int main() {
	char cmd1[255], cmd2[255], cmd3[255], filename[255];
	char *token;
	 
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

	int x = 0;
	printf("-----LAUNCH CMD 1: ");
	while ( command1[x] != filename) { 
		printf(" %s", command1[x]);
		x += 1; 
	}
	printf("---------------------------------------------------------------------------\n");
	x = 0; 
	printf("-----LAUNCH CMD 2: ");
	while ( command2[x] != filename) { 
		printf(" %s", command2[x]);
		x += 1; 
	}
	printf("---------------------------------------------------------------------------\n");
	x = 0;
	printf("-----LAUNCH CMD 3: ");
	while ( command3[x] != filename) { 
		printf(" %s", command3[x]);
		x += 1; 
	}
	printf("---------------------------------------------------------------------------\n");

	forkIt(command1, command2, command3);
	

}

char ** parseCommand (char *cmd, char *filename) { 
	char **newCmd = (char **)malloc((sizeof(char *) * 7));
	for (int i = 0; i < sizeof(newCmd); i++){
		newCmd[0] = (char *)malloc ((255) * sizeof(char));
	}
	char *token;
	char *cmd1[7];
	char parseThis[255];


	//fgets(parseThis, sizeof(parseThis), stdin);

	int i = 0; 
	token = strtok(cmd, " \n");
	//printf("First token grabbed: %s\n", token);
	while(token != NULL) { 
		newCmd[i] = token;
		//printf("Does my array work: %s\n", newCmd[i]);
		i++; 
		token = strtok(NULL, " \n");
		//printf("Token grabbed: %s\n", token);
	} 
        newCmd[i] = filename;
	
	return newCmd;
}

void forkIt(char** cmd1, char** cmd2, char** cmd3) {
  int childIds[3];
  int p1 = fork();
  if (p1 == 0) { // first child
    execvp(cmd1[0], cmd1);//first child's command HERE
  }
  if (p1 > 0) { // back in the parent
    childIds[0] = p1;
    int p2 = fork();
    if (p2 == 0) {//second child
      execvp(cmd2[0], cmd2);//second child's command HERE
    }
    if (p2 > 0) { // back in p1
      childIds[1] = p2;
      int p3 = fork();
      if (p3 == 0) {
	execvp(cmd3[0], cmd3);//third child's command HERE
      }
      if (p3 > 0) {
	childIds[2] = p3;
	wait(NULL);
      }
      wait(NULL);
    }
    wait(NULL);
  }
  printf("Children: %d, %d, %d\n", childIds[0], childIds[1], childIds[2]);
  printf("exiting..\n");
}
