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
	count = n;
	while(count > 0){
		long long digits;
		digits = 1 + rand() % (10);
		fprintf(F, "%llu\n", digits);
		count -= 1;
	}
	return 0;
}
