#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void split(int n) {
    if (n < 10) {
        printf("%d", n);
        return;
    }
    split(n / 10);
    printf(" %d", n % 10); 
}


int main(int argc, char *argv[]) {
	int n;
	printf("input number:\n");
	scanf("%d", &n);
	split(n);
	
	return 0;
}

