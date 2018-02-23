#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  int data;
  struct node *next;
}node;


node* insertBefore(node* head, int data){

	node* newNode = (node*) malloc(sizeof(node));
	newNode->data = data;
	newNode->next = head;
	head = newNode;
	return head;
}

node* insertAfterN(node*head, int index, int data){
	int i;
	node* curr = head;
	for(i = 0; i<index-1; i++){
		if(curr->next != NULL){
		curr = curr->next;
	    }
	}
	if(curr->data == data){
		return head;
	}
	node* newNode = (node*) malloc(sizeof(node));
	newNode->data = data;
	newNode->next = curr->next;
	curr->next = newNode;
	
	
	return head;
}

node* deleteNode(node* head, int position){
	  
	  
	  if(head->next == NULL){
		  struct node* temp = malloc(sizeof(node*));
		  free(head);
		  return temp;
	  }
      struct node* temp = head;
      int i;
      for(i = 0; temp!=NULL && i<position-1; i++){
		  temp = temp->next;
	  }
	  
	struct node* next = temp->next->next;
	free(temp->next);
	temp->next = next;
	   return head;
    
}

int main(int argc, char** argv){

  FILE* file = fopen(argv[1], "r"); 
  if(file== NULL){
	  printf("error");
	  return 0;
  }

  int num; 
  struct node *root;
  char* currLine = malloc(sizeof(char*));
  
  while(fgets(currLine, sizeof(currLine), file)){
	  if(currLine[0] == 'i'){
		  num = atoi(&currLine[2]);
		  if(root == NULL){
			  root = (node*) malloc(sizeof(node));
			  root->data = num;
			  root->next = NULL;
		  }else{
			  if(num<root->data){ 
				  root = insertBefore(root, num);
			  }else {
				 int is_present = 0;
				 int position = 0;
				  struct node * curr = root;
				  while(curr != NULL){
					  if(curr->data == num){
						  is_present = 1;
					  }
					  if(curr->data < num){
					      position++;
					      curr = curr->next;
					  }else{
						  curr = curr->next;
					  }
				  }
				  if(is_present == 0){
				  root = insertAfterN(root, position, num);	 
			  }   
			  }
		  }
	  }else if(currLine[0] == 'd'){
		  num = atoi(&currLine[2]);
		  if(root == NULL){
			  continue;
		  }else if(num == root->data){
			  root = root->next;
			  continue;
		  }else{
			  struct node* curr = root;
			  int position = 0;
			  while(curr != NULL){
				  if(curr->data == num){
					  root = deleteNode(root, position);
					  break;
				  }else{
					  position++;
					  curr = curr->next;
				  }
			  }
		  }
	  }
	  
	 
  }
   struct node* temp = root;
   int count= 0;
	  while(temp != NULL){
		  count++;
		  temp = temp->next;
	  }
	 temp = root;
	 if(count==0){
	     printf("%d\n", 0);
	     return 0;
	 }
	 printf("%d\n", count);
	 while(temp!=NULL){
		 printf("%d\t", temp->data);
		 temp = temp->next;
	 }
	 printf("\n");
	 
	 free(root);
	 free(currLine);
return 0;
}
