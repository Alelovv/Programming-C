#include <stdio.h>
#include <stdlib.h>

double** size(){
	int s1, s2;
	printf("Size 1 matrix:\n");
	scanf("%d", &s1);
	printf("Size 2 matrix:\n");
	scanf("%d", &s2);
	
	double** M1 = (double **) malloc(s1 * sizeof(double*));
	for (int i = 0; i < s1; i++) {
    	M1[i] = (double*)malloc(s1 * sizeof(double));
	}
	
	double** M2 = (double **) malloc(s2 * sizeof(double*));
	for (int i = 0; i < s2; i++) {
    	M2[i] = (double*)malloc(s2 * sizeof(double));
	}


    
	int i,j;
	for (i = 0; i < s1; i++){
		for (j = 0; j < s1; j++){
			printf("Vvedite element M1[%d][%d]", i + 1, j + 1);
			scanf("%lf", &M1[i][j]);
		}
		
	}
	

	for (i = 0; i < s2; i++) {
	    for (j = 0; j < s2; j++) {
	        printf("Vvedite element M2[%d][%d]: ", i + 1, j + 1);
	        scanf("%lf", &M2[i][j]);
	    }
	}
	return M1;
}





int main(int argc, char *argv[]) {
	size();
	printf("%lf", M1[1][2]);
	return 0;
}
