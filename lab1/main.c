#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char f = 'Y';
	do{
		double a, b, c;
		double x1, x2, d;
		printf("Vvedite a:");
		scanf("%lf", &a);
		printf("Vvedite b:");
		scanf("%lf", &b);
		printf("Vvedite c:");
		scanf("%lf", &c);
		
		
		d = pow(b, 2)- 4 * a * c;
		printf("d = %lf \n", d);
		
		if (d > 0){
		x1 = -b + sqrt(d) / (2 * a);
		x2 = -b - sqrt(d) / (2 * a);
		
		printf("x1 = %lf \n", x1);
		printf("x2 = %lf \n", x2);
		}
		
		if (d ==0){
		x1 = -b + sqrt(d) / (2 * a);
		
		printf("x1 = %lf \n", x1);
			
		}
		
		if (d <0){
			printf("Kornei Net\n");
		}
		
		printf("Continue? (Y) - yes\n");
		scanf(" %c", &f);
		
	}
	while (f == 'Y');
	
	return 0;
}

