#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char cmd1[255], cmd2[255], cmd3[255], filename[255];
	//don't need to worry about buffer overflow :> 

	char * cmd = "wc";
	char * cmdTest[3];
	cmdTest[0] = "ls";
	cmdTest[1] = "-a";
	cmdTest[2] = NULL; 

	//read in 3 strings from the console
	 
	printf("mash-1>");
	fgets(cmd1, sizeof(cmd1), stdin);
	
	printf("mash-2>");
	fgets(cmd2, sizeof(cmd2), stdin);
	
	printf("mash-3>");
	fgets(cmd3, sizeof(cmd3), stdin);

	printf("filename>");
	fgets(filename, sizeof(filename), stdin);

	
	
	printf("cmd 1: %s", cmd1);
	printf("cmd 2: %s", cmd2);
	printf("cmd 3: %s", cmd3);

	execvp(cmdTest[0], cmdTest);



}
