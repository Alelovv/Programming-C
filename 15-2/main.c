#include <stdio.h>
#include <stdlib.h>

void print_forward(int n) {
    if (n < 10) {
        printf("%d ", n);
    } else {
        print_forward(n / 10);
        printf("%d ", n % 10);
    }
}

void print_reverse(int n) {
    if (n < 10) {
        printf("%d ", n);
    } else {
        printf("%d ", n % 10);
        print_reverse(n / 10);
    }
}

int main() {
    int num;
    printf("Enter num: ");
    scanf("%d", &num);
    
    printf("\nForward: ");
    print_forward(num);
    printf("\nReverse: ");
    print_reverse(num);
    
    return 0;
}
