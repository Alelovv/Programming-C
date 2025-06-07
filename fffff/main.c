#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	FILE *F;
	FILE *out;
	int n, g;
	long long count;
	long long buf;
	F = fopen("input.txt", "w");
	printf("Input size of digits:\n");
	scanf("%d", &n);
	count = n;
	g = n;
	
	while(count > 0){
		long long digits;
		digits = 1 + rand() % (n);
		fprintf(F, "%llu\n", digits);
		count -= 1;
	}
	fclose(F);
	F = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	while (g > 0) {
        long long f; 
        sscanf(buf, "%llu", &f);
        if (f % 5 == 0){
			fprintf(out, "five\n");
		}
		else if (f % 7 == 0){
			fprintf(out, "seven\n");
		}
		else if (f % 7 == 0 && f %5 == 0){
			fprintf(out, "FiveSeven\n");
		}
		else{
			fprintf(out, "%llu\n", f);
		}
    }

	return 0;
}
