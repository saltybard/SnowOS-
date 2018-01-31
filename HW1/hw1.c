#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	char cmd1[255], cmd2[255], cmd3[255], filename[255];
	char *token, *newline;
	char* command1[7], command2[7], command3[7];
	//don't need to worry about buffer overflow :> 

	//read in 3 strings from the console
	 
	printf("mash-1>");
	fgets(cmd1, sizeof(cmd1), stdin);
	
	printf("mash-2>");
	fgets(cmd2, sizeof(cmd2), stdin);
	
	printf("mash-3>");
	fgets(cmd3, sizeof(cmd3), stdin);

	printf("filename>");
	fgets(filename, sizeof(filename), stdin);

	
	char file[255] = "test.txt";	

	//each array needs to be pointing to an array of strings, which end w/ the file name then w/ null

	printf("cmd 1: %s", cmd1);
	printf("cmd 2: %s", cmd2);
	printf("cmd 3: %s", cmd3);
	printf("filename: %s", filename);
	

	//iterate over char array

	int i = 0; 
	token = strtok(cmd1, " ");

	while(token != NULL) { 
		command1[i] = token;
		i = i + 1; 
		token = strtok(NULL, " "); 
		token = strtok(token, "\n");
	} 

	command1[i] = NULL;
	token = strtok(filename, "\n");
	command1[i--] = token;


	printf("%s\n", command1[0]);
	printf("%s\n", command1[1]);
	printf("%s\n", command1[2]);
	//printf("%s\n", command1[i]);

	execvp(command1[0], command1); 

	//printf("-----LAUNCH CMD 1: %s ----------------------------------------\n", cmdTest[0]);
	//execvp(command you want to execute, array w/ whole command + filename at end if applicable);



}
