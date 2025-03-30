#include <stdio.h>
#include <stdlib.h>
#include "Funcs.h"

double** summ(double **M1, double **M2, int n){
	int i,j,k;
	double **temp;
	
	temp = (double **)malloc(n * (sizeof(double *)));
	for (i = 0; i < n; i++){
		temp[i] = (double*)malloc(n *(sizeof(double)));
	}
	
	for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				temp[i][j] = 0;
				temp[i][j] = M1[i][j] + M2[i][j];
			}
		}
	
	return temp;
	
}

double** subt(double **M1, double **M2, int n){
	int i,j,k;
	double **temp;
	
	temp = (double **)malloc(n * (sizeof(double *)));
	for (i = 0; i < n; i++){
		temp[i] = (double*)malloc(n *(sizeof(double)));
	}
	
	for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				temp[i][j] = M1[i][j] - M2[i][j];
			}
		}
	
	return temp;
	
}

double** mult(double **M1, double **M2, int n){
	int i,j,k;
	double **temp;
	
	temp = (double **)malloc(n * (sizeof(double *)));
	for (i = 0; i < n; i++){
		temp[i] = (double*)malloc(n *(sizeof(double)));
	}

	for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				temp[i][j] = 0;
				for (k = 0; k < n; k++) {
                	temp[i][j] += M1[i][k] * M2[k][j];
            	}
			}
		}
	
	return temp;
	
}
