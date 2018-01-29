#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char cmd1[255], cmd2[255], cmd3[255];
	//change to 256, check for a '\n' and if there isn't one then there might be an issue

	//read in 3 strings from the console
	// Error handling: no more than 255 characters, no more than 5 total strings when split up 
	printf("mash-1>");
	fgets(cmd1, sizeof(cmd1), stdin);
	while((getchar()) != '\n');
        //scanf("%s", cmd1);
	printf("mash-2>");
	fgets(cmd2, sizeof(cmd2), stdin);
	while((getchar()) != '\n');
	printf("mash-3>");
	fgets(cmd3, sizeof(cmd3), stdin);
	while((getchar()) != '\n');
	printf("cmd 1: %s", cmd1);
	printf("cmd 2: %s", cmd2);
	printf("cmd 3: %s", cmd3);



}
