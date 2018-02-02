#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **parseCommand();



int main() {
	char cmd1[255], cmd2[255], cmd3[255], filename[255];
	char *token, *newline;
	//char* command1[7], *command2[7], *command3[7];
	//don't need to worry about buffer overflow :> 

	//read in 3 strings from the console
	 
	printf("mash-1>");
	char ** command1 = parseCommand();
	
	printf("mash-2>");
	char ** command2 = parseCommand();
	
	
	printf("mash-3>");
	char ** command3 = parseCommand();
	
	printf("filename>");
	fscanf(stdin, "%s", filename);
	

	//each array needs to be pointing to an array of strings, which end w/ the file name then w/ null

	printf("cmd 1: %s\n", command1[0]);
	printf("cmd 2: %s\n", cmd2);
	printf("cmd 3: %s\n", cmd3);
	printf("filename: %s\n", filename);
	
	//printf("File name?: %s\n", command1[i]);
	
	

	//execvp(command1[0], command1); 

	//printf("-----LAUNCH CMD 1: %s ----------------------------------------\n", cmdTest[0]);
	//execvp(command you want to execute, array w/ whole command + filename at end if applicable);


}

char ** parseCommand () { 
	char **newCmd = (char **)malloc((sizeof(char *) * 7));
	for (int i = 0; i < sizeof(newCmd); i++){
		newCmd[0] = (char *)malloc ((255) * sizeof(char));
	}
	char *token;
	char *cmd1[7];
	char parseThis[255];


	fgets(parseThis, sizeof(parseThis), stdin);

	int i = 0; 
	token = strtok(parseThis, " \n");
	printf("First token grabbed: %s\n", token);
	while(token != NULL) { 
		newCmd[i] = token;
		//printf("Does my array work: %s\n", newCmd[i]);
		i++; 
		token = strtok(NULL, " \n");
		printf("Token grabbed: %s\n", token);
	} 
       	//newCmd[i] = filename;
	
	return newCmd;
}
