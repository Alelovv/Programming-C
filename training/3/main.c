#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


struct Human{
	char name[20];
	int age;
	double salary;
};

int main(int argc, char *argv[]){
	struct Human N1 = { "Egor", 18, 999999};
	
	printf("name: %s\n", N1.name);
	printf("age: %d\n", N1.age);
	printf("salary: %lf\n", N1.salary);
	return 0;
}
