#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	FILE *F;
	int n;
	long long count;
	double buf[1000];
	F = fopen("input.txt", "w");
	printf("Input size of digits:\n");
	scanf("%d", &n);
	count = 0 + rand() % 101;
	while(count > 0){
		double digits;
		scanf()
		fprintf(F, "%lf", digits);
	}
	return 0;
}
