#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char** argv){
	
	char* uncompressed = argv[1]; 
	int sizeU = strlen(uncompressed);
	uncompressed[sizeU] = '\0';
	int i =0, amount = 1, sizeC =0;
	char* compressed = NULL;
	char currChar;
	
	while(i < sizeU){
		if(uncompressed[i]>='0' && uncompressed[i]<='9'){
			printf("error\n");
			return 0;
		}
		i++;
	}
	for(i=1; i<sizeU+1; i++){
		currChar = uncompressed[i-1];
		if((uncompressed[i] == uncompressed[i-1])){
			amount++;
		}else{
			if(compressed==NULL){
				asprintf(&compressed, "%c%d", currChar, amount);
				amount = 1;
			}else{
				asprintf(&compressed, "%s%c%d", compressed, currChar, amount);
				amount = 1;		
			}
		}
		
	}
	
	sizeC= strlen(compressed);
	
	if(sizeC>sizeU){
		printf("%s\n", uncompressed);
	}else{
		printf("%s\n", compressed);
	}
	
	return 0;
}
