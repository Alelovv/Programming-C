#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void fib_sum(int n, int current, long long sum, int a, int b) {
    if (current > n) {
        longjmp(env, sum);
    }
    sum += a;
    int next = a + b;
    fib_sum(n, current + 1, sum, b, next);
}

int main() {
    int n;
    printf("Enter number of numbers: ");
    scanf("%d", &n);
    int val = setjmp(env);
    if (val == 0) {
        fib_sum(n, 1, 0, 1, 1);
    } else {
        printf("Sum: %lld\n", n, (long long)val);
    }
    return 0;
}
