#include <stdio.h>
#include <string.h>

typedef unsigned int        u32;
typedef unsigned long long  u64;


u32 cnt_long(u32 n) {
	u32 result = 0;
	while (n) {
    	result += n & 1;
    	n >>= 1;
	}
	return result;
}


u64 cnt_double(u64 n) {
	u64 result = 0;
	while (n) {
    	result += n & 1;
    	n >>= 1;
  	}
	return result;
}

int main() {
	long a;
	double b;

	printf("Enter long number: ");
	scanf("%ld", &a);
	printf("Bits in long: %d\n", cnt_long((u32)a));

	printf("Enter double number: ");
	scanf("%lf", &b);

	u64 bits;
	memcpy(&bits, &b, sizeof(double));
	printf("Bits in double: %llu\n", cnt_double(bits));

	return 0;
}
//https://habr.com/ru/articles/276957
