#include <stdio.h>
#include <stdlib.h>

double** operations(double **M1, double **M2, int n){
	
	int c, i, j;
	double = **temp;
	temp = (double **)malloc(n * (sizeof(double*)));
	for (i = 0; i < n; i++){
		temp[i] = (double*)malloc(n *(sizeof(double)));
	}
	print("choose option: (1) = sum; (2) = subtraction; (3) = multiplication\n");
	scanf("%d", &c);
	
	swich(c) {
		case 1:
		for (i = 0; i < n; i++){
			for (j = 0; j < n; j++){
				tempi[i][j] = M1[i][j] + M2[i][j];
		}	 
		
		default: printf("ERROR");
	}
			
			
	
	
	}
}
