#include <stdio.h>
#include <stdlib.h>


void split(int n) {
    if (n < 10) {
        printf("%d", n);
        return;
    }
    printf("%d ", n % 10); 
    split(n / 10);
}

void split_reverse(int n) {
    if (n < 10) {
        printf("%d", n);
        return;
    }
    split_reverse(n / 10);
    printf(" %d", n % 10); 
}


int main(int argc, char *argv[]) {
	int n;
	printf("input number:\n");
	scanf("%d", &n);
	split(n);
	printf("\n");
	split_reverse(n);
	
	return 0;
}

