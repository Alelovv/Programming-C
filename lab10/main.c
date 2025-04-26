#include <stdio.h>
#include <stdlib.h>

#define input int n, i; double digits[100]; printf("Input number of digits:\n"); scanf("%d", &n); for(i = 0; i < n; i++){ double d; scanf("%lf", &d); digits[i] = d; }
#define output(digits, n) int i, j; for(i = 0; i < n; i++){ for(j = 0; j < n-i-1; j++){ if(digits[j] < digits[j+1]){ double temp = digits[j]; digits[j] = digits[j+1]; digits[j+1] = temp; } } } printf("%lf", digits[0]);

int main(int argc, char *argv[]) {
    input output(digits, n)
    return 0;
}
