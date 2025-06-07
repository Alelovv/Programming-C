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
		digits = 1 + rand() % (n);
		if (digits % 5 == 0){
			fprintf(F, "five\n");
		}
		else if (digits % 7 == 0){
			fprintf(F, "seven\n");
		}
		else if (digits % 7 == 0 && digits %5 == 0){
			fprintf(F, "FiveSeven\n");
		}
		else{
			fprintf(F, "%llu\n", digits);
		}
		// fprintf(F, "%llu\n", digits);
		count -= 1;
	}
	return 0;
}
