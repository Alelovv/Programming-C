
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void erat(int n) {

    bool *isPrime = (bool *)malloc((n + 1) * sizeof(bool));
    for (int i = 0; i <= n; i++) {
        isPrime[i] = true; 
    }

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p] == true) {
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    
    for (int p = 2; p <= n; p++) {
        if (isPrime[p]) {
            printf("%d ", p);
        }
    }
    free(isPrime);
}

int main() {
    int n;
    printf("¬ведите целое неотрицательное число n: ");
    scanf("%d", &n);
    printf("\n");
    erat(n);
    
    return 0;
}

