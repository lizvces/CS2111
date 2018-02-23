#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){

	FILE * file = fopen(argv[1], "r");
	int amount;
	fscanf(file, "%d", &amount);
	int i, j, k, x, y, c;
	int arr[amount];
	
	for(i = 0; i<amount; i++){
		fscanf(file, "%d", &c);
		arr[i] = c;
	}
	for(j = 1; j<amount; j++){
		k = j;
		
		while(k>0 && arr[k]<arr[k-1]){
			y = arr[k];
			arr[k] = arr[k-1];
			arr[k-1] = y;
			k--;
		}
	 }
	 
	 for(x=0; x<amount; x++){
		 printf("%d\t", arr[x]);
	 }
	 
	return 0;
	
}

