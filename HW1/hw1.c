#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *parseCommand(char cmd[], char *filename);


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
	fscanf(stdin, "%s", filename);

	
	char file[255] = "test.txt";	

	//each array needs to be pointing to an array of strings, which end w/ the file name then w/ null

	printf("cmd 1: %s\n", cmd1);
	printf("cmd 2: %s\n", cmd2);
	printf("cmd 3: %s\n", cmd3);
	printf("filename: %s\n", filename);
	

	//iterate over char array

	int i = 0; 
	token = strtok(cmd1, " \n");
	printf("First token grabbed: %s\n", token);
	while(token != NULL) { 
		command1[i] = token;
		i++; 
		token = strtok(NULL, " \n");
		printf("Token grabbed: %s\n", token);
	} 
       	command1[i] = filename;

	printf("%s\n", command1[0]);
	//printf("%s\n", command1[1]);
        //printf("%s\n", command1[2]); these can cause seg faults if there's nothing in these spots :))
	printf("File name?: %s\n", command1[i]);


	char *test[6];
	test[0] = "grep";
	test[1] = "-c"; 
	test[2] = "omae";
	test[3] = "test.txt";
	test[4] = NULL;
	

	//execvp(command1[0], command1); 

	//printf("-----LAUNCH CMD 1: %s ----------------------------------------\n", cmdTest[0]);
	//execvp(command you want to execute, array w/ whole command + filename at end if applicable);

	char *parsedCmd1 = parseCommand(cmd1, filename);
	//printf("Parsed CMD 1: %s", parsedCmd1[0]);

}

char * parseCommand (char cmd[], char *filename) { 
	char *newCmd = (char *)malloc(sizeof(char)*7);
	char *token;
	char cmd1[7];
	printf("Parser here: %c\n", cmd[6]);

	int i = 0; 
	token = strtok(cmd, " \n");
	printf("First token grabbed: %s\n", token);
	while(token != NULL) { 
		cmd1[i] = token;
		//printf("New CMD: %s", newCmd[i]);
		i++; 
		token = strtok(NULL, " \n");
		printf("Token grabbed: %s\n", token);
	} 
       	//newCmd[i] = filename;

	return newCmd;
}
