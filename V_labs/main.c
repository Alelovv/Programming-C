#include <stdio.h>
#include <stdlib.h>

void sieveOfEratosthenes(int n) {
    int* P = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 2; i <= n; i++) {
        P[i] = i;
    }
    
    int p = 2;
    
    while (p * p <= n) {
        if (P[p] != 0) {
            for (int i = p * p; i <= n; i += p) {
                P[i] = 0;
            }
        }
        p++;
        while (p <= n && P[p] == 0) {
            p++;
        }
    }
    
    printf("������� ����� �� %d:\n", n);
    for (int i = 2; i <= n; i++) {
        if (P[i] != 0) {
            printf("%d ", P[i]);
        }
    }
    printf("\n");
    
    free(P);
}

int main() {
    int n;
    printf("������� ����� n: ");
    scanf("%d", &n);
    
    if (n < 2) {
        printf("������� ����� ������ 2 �� ����������\n");
        return 0;
    }
    
    sieveOfEratosthenes(n);
    return 0;
}
