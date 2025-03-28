#include <stdio.h>
#include <stdlib.h>
#include "Funcs.h"

int main(int argc, char *argv[]) {
	double **M1, **M2, **Rez;
	int n, i, j;
	printf("input size:\n");
	scanf("%d", &n);
	
	M1 = (double**)malloc(n * (sizeof(double*)));
	for (i = 0; i < n; i++){
		M1[i] = (double*)malloc(n *(sizeof(double)));
	}
	
	M2 = (double**)malloc(n * (sizeof(double*)));
	for (i = 0; i < n; i++){
		M2[i] = (double*)malloc(n *(sizeof(double)));
	}
	
	printf("Input 1M:\n");
	
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			printf("input M1[%d][%d]", i + 1, j + 1);
			scanf("%lf", &M1[i][j]);
		}
	}
	double **Rez = operations(M1, M2, n);
	
	printf("Result:\n");
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			
			printf("%lf %lf", Rez[i], Rez[j]);
		}
	}
	
	return 0;
}
