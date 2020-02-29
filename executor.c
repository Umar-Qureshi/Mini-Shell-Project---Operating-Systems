#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include "executor.h"
#include <sys/stat.h>
#include <time.h>

extern int alphasort();

enum colour { black=30, red, green, yellow, blue, purple, cyan };

//Print function with color, more info: http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
void myPrint(char* text, int colourcode){

    printf("\033[0;%im%s\033[0m", colourcode, text);
}

//#1.Internal command functions:
 
void help() {
    myPrint("HELP MENU\n", yellow);
    myPrint("Available commands:\n", blue);
    myPrint("	cd - ", 36);
    myPrint("Change Directory\n", 32);
    myPrint("	clr - ", 36);
    myPrint("Clear Terminal\n", 32);
    myPrint("	dir - ", 36);
    myPrint("Current Directory\n", 32);
    myPrint("	environ - ", 36);
    myPrint("Environment\n", 32);
    myPrint("	echo <arg('s)> - ", 36);
    myPrint("Prints out all text after echo statement\n", 32);
    myPrint("	help - ", 36);
    myPrint("Displays Help Menu\n", 32);
    myPrint("	pause - ", 36);
    myPrint("Pauses the screen\n", 32);
    myPrint("	quit - ", cyan);
    myPrint("Exits the program\n", green);
}

void ChangeDir(char* path[]){

	if (chdir(path[1]) != 0){
		printf("Directory was unable to open, most likely does not exist");
	}
	//using system call chdir to change our directory
        chdir(path[1]);
}

void clearTerminal() {
	// \033 = escape char
	// 2J = clear screen
	// 1;1H set cursor at (1,1)
	//Marcelo Cantos answer: https://stackoverflow.com/questions/4062045/clearing-terminal-in-linux-with-c-code
	printf("\033[2J\033[1;1H");
}

//#6. Command Line Prompt:
void path_Name(char* directory) {
	myPrint(directory, purple);
	myPrint("/myshell $ ", cyan);
}

//Show Working Directory and its contents
void swd(char* directory) {
    
    //showing working directory
    myPrint("cwd:  ", 32);
    myPrint(directory, 32);
    printf("\n");
	
    //Printing contents of direcotry
    //more info: https://latesthackingnews.com/2017/03/22/c-program-implement-ls-command/
    struct direct **namelist;
    int content_numb = scandir(".", &namelist, NULL, alphasort);
   
    for (int z=0; z<content_numb; ++z){
	printf("%s\n", namelist[z]->d_name);
	free(namelist[z]);
     }
    free(namelist);
}

//Listing all Environment stings
void environ() {
    
    //Storing system call in the s variable
    const char* s = getenv("PATH");
    printf("PATH: %s\n", s);
}

void echo(char* text[], int size) {
    
    //printing all words after echo
    for (int q=1; q < size; q++){
        printf("%s ", text[q]);
    }
    printf("\n");
}

//Pausing the terminal
void mypause() {

    int usleep();
    myPrint("Press enter to continue...", 34);

    while(getchar() != '\n') {
      usleep(100000);
    }
    myPrint("---Enter detected, now returning to myShell:\n", 34);
}
