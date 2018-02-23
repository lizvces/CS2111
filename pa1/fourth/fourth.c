#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	
	if(argc ==1){
		exit(0);
	}
	FILE* file = fopen(argv[1], "r");
	int size, i,a,b, j,num ,k, count =0 , power;
	fscanf(file, "%d", &size);
	int **matrix, **result, **temp;
	matrix = (int**) malloc(sizeof(int*)*size);
	result = (int**) malloc(sizeof(int*)*size);
	temp = (int**) malloc(sizeof(int*)*size);
	if(file == NULL){
		exit(0);
	}
	for(i = 0; i<size; i++){
		matrix[i] = (int*) malloc(sizeof(int)*size);
		result[i] = (int*) malloc(sizeof(int)*size);
		temp[i] = (int*) malloc(sizeof(int*)*size);
	}
	
	for(i = 0; i<size; i++){
		for(j=0; j<size; j++){
			result[i][j] = 0;
			temp[i][j] = matrix[i][j];
		}
	}

	while(!feof(file)){
		for(i=0; i<size; i++){
			fscanf(file, "%d", &num);
			matrix[count][i] = num;
			temp[count][i] = num;
		}
		if(count != size-1){
			count++;
		}else{
			fscanf(file, "%d", &power);
			break;
		}
	}
	
	int times;
	for(times = 1; times<power; times++){	
		for(i=0; i<size; i++){
			for(j=0; j<size; j++){
				for(k=0; k<size; k++){
					result[i][j] += temp[i][k]*matrix[k][j];
				}
			}
		}
		for(a = 0; a<size; a++){
			for(b=0; b<size; b++){
				temp[a][b] = result[a][b];
				result[a][b] = 0;
			}
		}
	}
	
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			printf("%d\t", temp[i][j]);
		}
		printf("\n");
	}
	
		for(j=0; j<size; j++){
			free(matrix[j]);
			free(temp[j]);
			free(result[j]);
		}
	
	
	free(matrix);
	free(result);
	free(temp);
	
	return 0;
}
