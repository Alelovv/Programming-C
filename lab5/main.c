#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
	int n;
	double Matrix1[n][n], Matrix2[n][n];
	double * pMatrix1 = &Matrix1; 
	printf("%p\n", &pMatrix1);
	printf("%d", *pMatrix1);
	return 0;
}
