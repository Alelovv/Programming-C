#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void triangle(){
	double x, y, z;
	double P, S, p;
	printf("Input 1 Side:\n");
	scanf("%lf", &x);
	
	printf("Input 2 Side:\n");
	scanf("%lf", &y);
	
	printf("Input 3 Side:\n");
	scanf("%lf", &z);
	if (x <= 0 || y <= 0 || z <= 0) {
        printf("ERROR");
        return;
    }
	
	if ((x + y > z ) && (x + z > y) && (z + y > x)){
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
