#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char** argv){

	char* result = (char*) malloc(sizeof(char*));
	char* currWord = (char*) malloc(sizeof(char*));
	int i;
	
	for(i = 1; i<argc; i++){
		currWord = argv[i];
		int size = strlen(currWord);
		int resultSize = strlen(result);
		char c = currWord[size-1];
		result[resultSize] = c;
		
	}
	printf("%s\n", result);
	
	return 0;
	
}
