#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void fibonaci(int count, int *sum, int curr, int next) {
    if (count <= 0) {
        longjmp(env, 1); 
    }

    *sum += curr;
    printf("%llu\n", curr);
    fibonaci(count - 1, sum, next, curr + next);
}

int main() {
	
    long count;
    printf("Input count: ");
    scanf("%llu", &count);

    long long result = 0;

    if (setjmp(env) == 0) {
        fibonaci(count, &result, 1, 1);
    } else {
        printf("Result: %llu\n", result);
    }

    return 0;
}
