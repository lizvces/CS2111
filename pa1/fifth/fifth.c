#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv){
	
	if(argc ==1){
		exit(0);
	}
	FILE* file = fopen(argv[1], "r");
	int size, i, j, k, z, num , count =0;
	fscanf(file, "%d", &size);
	int **matrix, **matrix2;
	matrix = (int**) malloc(sizeof(int*)*size);
	matrix2 = (int**) malloc(sizeof(int*)*size);
	if(file == NULL){
		exit(0);
	}
	for(i = 0; i<size; i++){
		matrix[i] = (int*) malloc(sizeof(int)*size);
		matrix2[i] = (int*) malloc(sizeof(int)*size);
	}
	
	while(!feof(file)){
		for(i=0; i<size; i++){
			fscanf(file, "%d", &num);
			if(num>(size*size) || num<1){
				printf("not-magic");
				return 0;
			}else{
				matrix[count][i] = num;
				matrix2[count][i] = num;
			}
		}
		if(count != size-1){
			count++;
		}else{
			break;
		}
	}
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			for(k = 0; k<size; k++){
				for(z = 0; z<size; z++){
					if((matrix[i][j] == matrix2[k][z]) && (i !=k) && (j!=z)){
						printf("not-magic");
						return 0;
					}
				}
			}
		}
	}
	
	int sum, sum2, sum3;
	sum = 0;
	for(i=0; i<size; i++){
		sum += matrix[0][i];
	}
	for(i = 0; i<size; i++){
		for(j=0; j<size; j++){
			sum2 += matrix[i][j];
		}
		if(sum!=sum2){
			printf("not-magic");
			return 0;
		}
		
		sum2 = 0;
	}
	
	sum2 = 0;
	for(i=0; i<size; i++){
		for(j = 0; j<size; j++){
			sum2+=matrix[i][j];
		}
		if(sum!=sum2){
			printf("not-magic");
			return 0;
		}
		
		sum2 = 0;
	}
	sum2 = 0;
	sum3 =0;
	i = j = 0;
	while(i<size && j<size){
			sum2 += matrix[i][j];
			sum3 += matrix[size-1-i][size-1-j];
			j++;
			i++;
	}
		if(sum!=sum2 || sum!=sum3){
			printf("not-magic");
			return 0;
		}
		
	printf("magic");	
	return 0;
}
