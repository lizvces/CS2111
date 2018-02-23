#include <stdlib.h>
#include <stdio.h>

struct node{
	
	int value;
	int key;
	struct node* next;
	
}node;


int HashFunction(int size, int value){
	return value % size;
}
void insert(struct node** HashMap, int value){
	int key = abs(value%10000);
	
	if(HashMap[key] == NULL){
		struct node* newNode =  (struct node*) malloc(sizeof(struct node));
		newNode->value = value;
		newNode->next = NULL;
		HashMap[key] = newNode;
		printf("inserted\n");
	}else{
		struct node* temp = HashMap[key];
		while(temp->next != NULL){
			temp = temp->next;
			
		}
		
		struct node* newNode = (struct node*) malloc(sizeof(struct node));
		newNode->value = value;
		newNode->next = NULL;
		temp->next = newNode;
		printf("inserted\n");
	}
}

int search(struct node** HashMap, int value){
	int key = abs(value%10000);
	
	if(HashMap[key] == NULL){
		return 0;
	}else{
		struct node* temp = HashMap[key];
		while(temp != NULL){
			if(temp->value == value){
				return 1;
			}
			temp = temp->next;
			
		}
		
 	}
 	return 0;
 	
	
}
void print(struct node** HashMap, int value){
	
	int key = abs(value%10000);
	
	if(HashMap[key] == NULL){
		printf("null");
	}else{
		struct node* temp = HashMap[key];
		if(temp !=NULL){
			printf("%d\t", temp->value);
		}
	}
}
int main(int argc, char** argv){
	
	struct node* HashMap[10000];
	FILE* file = fopen(argv[1], "r");
	char c;
	int d, i;
	
	for(i = 0 ; i<10000; i++){
		HashMap[i] = NULL;	
	}
	while(!feof(file)){
		fscanf(file, "%c %d", &c ,&d);
		if(c == 'i'){
			int y = search(HashMap, d);
			if(y==1){
				printf("duplicate\n");
				continue;
			}
			insert(HashMap, d);
		}else if(c== 's'){
			int x = search(HashMap, d);
			if(x==1){
				printf("present\n");
			}else{
				printf("absent\n");
			}
		}
	}
	
	return 0;
}
