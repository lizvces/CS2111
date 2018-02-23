#include <stdlib.h>
#include <stdio.h>

struct node{
	
	int value;
	int height;
	struct node* right;
	struct node* left;
};
struct node* insert(int value, struct node* n){
	
	if(n == NULL){
		n = (struct node*) malloc(sizeof(struct node));
		n->left = n->right = NULL;
		n->value = value;
		return n;
	}
	
	if(value < n->value){
		n->left = insert(value, n->left);
	}else if(value > n->value){
		n->right = insert(value, n->right);
	}
	
	return n;
}

int search(int value, struct node* n){
	if(n == NULL){
		return 0;
	}else{
		if(value == n->value){
			return 1;
		}else{
			int final = search(value, n->left);
			int final2 = search(value, n->right);
			
			if(final == 1 || final2==1){
				return 1;
			}
		}
	return 0;
	}
}

void deallocate(struct node* n){
	if(n!=NULL){
		deallocate(n->left);
		deallocate(n->right);
		free(n);
	}
}

int getHeight(struct node* root, int value, int height){
		
		if(root == NULL){
			return 0;
		}
		if(root->value == value){
			return height;
		}
		
		int heightDown = getHeight(root->left, value, height+1);
		
		if(heightDown != 0){
			return heightDown;
		}
		
		heightDown = getHeight(root->right, value, height+
		1);
		
		return heightDown;
}

struct node* findMin(struct node* root){
	struct node* temp = root;
	while(temp->left != NULL){
		temp = temp->left;
	}
	
	return temp;
}

struct node* delete(struct node* parent, int value){
	
	if(value<parent->value){
		parent->left = delete(parent->left, value);
	}else if(value>parent->value){
		parent->right = delete(parent->right, value);
	}else{
		if(parent->left == NULL && parent->right == NULL){
			struct node* temp = parent->right;
			free(parent);
			printf("success\n");
			return temp;
		}else if((parent->left == NULL && parent->right != NULL)){
			struct  node* temp = parent->right;
			free(parent);
			printf("success\n");
			return temp;
		}else if((parent->left != NULL && parent->right == NULL)){
			struct node* temp = parent->left;
			free(parent);
			printf("success\n");
			return temp;
		}else{
			struct node* temp = findMin(parent->right);
			parent->value = temp->value;
			parent->right = delete(parent->right, temp->value);
		}
	}
	return parent;
}

int main(int argc, char** argv){
	
	if(argc ==1){
		printf("error\n");
		return 0;
	}
	struct node* root = NULL;
	char action;
	int val;
	FILE* file = fopen(argv[1], "r");
	if(file == NULL){
		printf("error\n");
		return 0;
	}	
	while(!feof(file)){
		fscanf(file, "%c %d", &action, &val);
		if(action == 'i'){
			int duplicate = search(val, root);
			if(duplicate == 1){
				printf("duplicate\n");
			}else{
			root = insert(val, root);
			int height = getHeight(root, val, 1);
			printf("inserted %d\n", height);
			}
		}else if(action == 's'){
			if(search(val, root) == 1){
				int height = getHeight(root, val, 1);
				printf("present %d\n", height);
			}else{
				printf("absent\n");
			}
		}else if(action == 'd'){
			if(search(val, root) == 0){
				printf("fail\n");
			}else{
				root = delete(root, val);
			}
			
		}
	}
	deallocate(root);
	fclose(file);
	return 0;	
}
