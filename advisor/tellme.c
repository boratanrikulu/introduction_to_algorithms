#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int chechStatus(int argc);
int decideWhattoDo(int argc);

int main(int argc, char  *argv[])
{
	srand(time(NULL));
	if (chechStatus(argc)){
		printf("%s\n", argv[decideWhattoDo(argc)]);
	}
	return 0;
}

int chechStatus(int argc){
	if (argc == 1){
		printf("Hey there! As far as seen from here, you need some advice.\nHere I am to be your mentor.\nFirst, please read below how the program works!\n\n");
		printf("Example: ~$ ./tellme study hangin'_out coding\n");
		return 0;
	}
	return 1;
}

int decideWhattoDo(int chance){
	int decision;
    do {
    	decision = rand()%chance;
   	} while (!decision);
	return decision;
}