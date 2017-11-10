#include <stdlib.h>
#include <stdio.h>
#include "learn.h"

double** multiply(double** matrixA, double** matrixB, int matrix_a_row, int matrix_b_column, int matrix_a_column){
	double** result = (double**) malloc(matrix_a_row*sizeof(double*));
	int i,j,k;
	for(i = 0; i<matrix_a_row; i++){
		result[i] = (double*) malloc(matrix_b_column*sizeof(double));
	}
	for(i=0; i<matrix_a_row; i++){
		for(j=0; j<matrix_b_column; j++){
			for(k=0; k<matrix_a_column; k++){
				result[i][j] += matrixA[i][k]*matrixB[k][j];
			}
		}
	}
	
	return result;
}

double** transpose(double** matrix, int sizer, int sizec){
	
	double** t_matrix = (double**) malloc(sizer*sizeof(double*));
	 int i,j;
	 for(i = 0; i<sizer; i++){
		 t_matrix[i] = (double*) malloc(sizec*sizeof(double)); 
	 }
	
	 for(i = 0; i<sizer; i++){
		 for(j=0; j<sizec; j++){
			 t_matrix[i][j] = matrix[j][i];
		 }
	 }
	 
	 return t_matrix;
}

double** reducedRow(double** matrix, int count, int width, int row){
	int i, j, a, b;
	while(count!= width){
		for(i = count; i<width; i++){
			double div = matrix[i][count];
			for(j=0; j<width*2; j++){
					matrix[i][j] = matrix[i][j]/div;
			}
		}
		double* firstRow = matrix[count];	
		for(a=1; a<width; a++){
			if(a!=count){
				double* nextR = matrix[a];
				for(b=0; b<width*2; b++){
					nextR[b] = nextR[b] - firstRow[b];
				}
			}
		}	
		count++;
	} 
		count = width-1;
		while(count>= 0){
			for(i = count; i>=0; i--){
				double div = matrix[i][count];
				for(j=width*2-1; j>=0; j--){
						matrix[i][j] = matrix[i][j]/div;
				}
			}
			double* firstRow = matrix[count];	
			for(a=count-1; a>=0; a--){
				if(a != count){
					double* nextR = matrix[a];
					for(b=width*2-1; b>=0; b--){
						nextR[b] = nextR[b] - firstRow[b];
						if(nextR[b] == -0.0){
							nextR[b] = abs(nextR[b]);
						}
					}
				}else{
					continue;
				}
			}	
			count--;
		} 
		
		double** resultM = (double**) malloc(row*sizeof(double*));
		for(i = 0; i<row; i++){
			resultM[i] = (double*) malloc(width*sizeof(double));
		}
		
		for(i = 0; i<row; i++){
			for(j=0; j<width; j++){
				resultM[i][j] = matrix[i][(width)+j];
			}
		}
		
	return resultM;
}

void killMatrix(double** matrix, int row, int col){
	int i;
	for(i = 0; i<col; i++){
		free(matrix[i]);
	}
	
	free(matrix);
}

int main(int argc, char** argv){
	if(argc<2){
		exit(0);
	}
	FILE* training_file = fopen(argv[1], "r");
	FILE* test_file = fopen(argv[2], "r");
	int col, row, test_row;
	fscanf(training_file, "%d", &col);
	fscanf(training_file, "%d", &row);
	fscanf(test_file, "%d", &test_row);
	double num;
	double** matrix = (double**) malloc(row*sizeof(double*));
	double** test_matrix = (double**) malloc(test_row*sizeof(double*));
	double** prices = (double**) malloc(row*sizeof(double*));
	int x, count = 0;
	
	for(x = 0; x<row; x++){
		int amount = col+1;
		matrix[x] = (double*) malloc(amount*sizeof(double));
		prices[x] = (double*) malloc(sizeof(double));
		amount = 0;
	}
	
	
	for(x = 0; x<test_row; x++){
		test_matrix[x] = (double*) malloc((col+1)*sizeof(double));
	}
	
	while(!feof(training_file)){
		for(x=0; x<=col+1; x++){
			if(x==0){
				matrix[count][x] = 1;
			}else if(x != col+1){
				fscanf(training_file, "%lf ,", &num);
				matrix[count][x] = num;
			}else{
				fscanf(training_file, "%lf ,", &num);
				prices[count][0] = num;
			}
		}
		if(count != row-1){
			count++;
		}else{
			break;
		}
	}
	int i,j,k;
	
	count = 0;
	while(!feof(test_file)){
		for(x=0; x<col+1; x++){
			if(x == 0){
				test_matrix[count][x] = 1;
			}else {
				fscanf(test_file, "%lf ,", &num);
				test_matrix[count][x] = num; 
			}
			
		}
		
		if(count!= test_row-1){
			count++;
		}else{
			break;
		}
	}
	double** t_matrix = transpose(matrix, col+1, row);
	double ** w_matrix = multiply(t_matrix, matrix, col+1, col+1, row);
	double ** augMatrix = (double**) malloc((col+1) * sizeof(double*));
        for(j=0;j<col+1;j++){
                augMatrix[j] = (double *) malloc(((col+1)*2) * sizeof(double));
        }
        for (i=0; i<col+1; i++){
                for(j=0; j<col+1; j++){
                        augMatrix[i][j]=w_matrix[i][j];
                }
                for(k=(col+1); k<(col+1) *2; k++){
                        if(k==((col+1)+i)){
                                augMatrix[i][k]=1.0f;
                        }else{
                                augMatrix[i][k]=0.0f;
                        }
                }
        }  
         
	double** reduced = reducedRow(augMatrix, 0, col+1, col+1);
	w_matrix = multiply(t_matrix, prices, col+1, 1, row);
	w_matrix = multiply(reduced, w_matrix, col+1, 1, col+1);

	double** final_price = multiply(test_matrix, w_matrix, test_row, 1, col+1);
	
	for(i = 0; i<test_row; i++){
		printf("%0.0lf\n", final_price[i][0]);
	}
	
	killMatrix(reduced, col+1, col+1);
	killMatrix(final_price, col+1, 1);
	killMatrix(augMatrix, col+1, col+1);
	killMatrix(t_matrix, row, col+1);
	killMatrix(w_matrix, col+1, col+1);
	killMatrix(matrix, row, col+1);
	killMatrix(test_matrix, col+1, test_row);
	killMatrix(prices, row, col+1);
	
	
	return 0;
}
