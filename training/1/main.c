#include <stdio.h>
#include <stdlib.h>


int main() {
    int a, b, c;
    int *p1 = &a, *p2 = &b, *p3 = &c;
    int *min = p1;

    printf("Input numbers: ");
    scanf("%d %d %d", p1, p2, p3);

    if (*p2 < *min) {
	min = p2;
	}
    if (*p3 < *min) {
	min = p3;
	}

    *p1 = *min;
    *p2 = *min;
    *p3 = *min;

    printf("%d %d %d\n", a, b, c);

    return 0;
}
