#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include 'triangle.h'


void triangle(){
	double x, y, z;
	double P, S, p;
	printf("Input 1 Side:\n");
	scanf("%lf", &x);
	
	printf("Input 2 Side:\n");
	scanf("%lf", &y);
	
	printf("Input 3 Side:\n");
	scanf("%lf", &z);

	
	if (proverka(x,y,z)){
		P = x + y + z;
		p = P/2;
		S = sqrt(p * (p - x)*(p - y)*(p - z));
		printf("P = %lf , S = %lf", P, S);
	}
	else{
		printf("ERROR");
	}
}



int main(int argc, char *argv[]) {
	triangle();
	return 0;
}
