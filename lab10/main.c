#include <stdio.h>
#include <stdlib.h>

#define input \
int n, i, j; \
double digits[100]; \
printf("Input number of digits:\n"); \
scanf("%d", &n); \
for(i = 0; i < n; i++){ \
	double d; \
	scanf("%lf", &d); \
	digits[i] = d; \
	}\
for(i = 0; i < n; i++){ \
	for(j = 0; j < n-i-1; j++){ \
		if(digits[j] < digits[j+1]){ \
			double temp = digits[j]; \
			digits[j] = digits[j+1]; \
			digits[j+1] = temp; \
			} \
		} \
	} \
printf("%lf\n", digits[0]);\
double rez = 0;\
for (i = 0; i < n; i++){\
	rez += digits[i];\
}\
rez /= n;\
printf("%lf", rez);

int main(int argc, char *argv[]) {
    input;
    return 0;
}
