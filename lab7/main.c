#include <stdio.h>
#include <stdlib.h>

struct Human {
	char name[30];
	char surname[30];
	int year;
};

int main(){
	int i, j;
	struct Human people1[4];
	struct Human people2[4];
	
	for(i = 0; i < 4 ; i++){
		printf("name%d:", i + 1);
		scanf("%s", people1[i].name);
		
		printf("surname%d:", i + 1);
		scanf("%s", people1[i].surname);
		
		printf("year%d:", i + 1);
		scanf("%d", &people1[i].year);
	}
	
	for(i = 0; i < 4 ; i++){
		people2[i] = people1[i];

	}
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3 - i; j++) {
            if(people2[j].year > people2[j + 1].year) {
                struct Human temp = people2[j];
                people2[j] = people2[j + 1];
                people2[j + 1] = temp;
            }
        }
    }
	for (i = 0; i < 4; i++) {
    printf("%s %s, %d\n", people2[i].surname, people2[i].name, people2[i].year);
	}
}

