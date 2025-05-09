#include <stdio.h>


int main() {
	int sum(int count, ...);
	int max(int count, ...);
	int min(int count, ...);
	float average(int count, ...);

    printf("Sum: %d\n", sum(3, 5, 10, 15));
    printf("Max: %d\n", max(4, 8, 3, 12, 7));
    printf("Min: %d\n", min(5, 9, 4, 7, 2, 5));
    printf("Average: %.2f\n", average(4, 10, 20, 30, 40));
    return 0;
}
