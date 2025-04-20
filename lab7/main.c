#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Human {
	char name[30];
	char surname[30];
	int year;
};

int main(){
	char *locale = setlocale(LC_ALL, "");
	int n = 0;
	char buffer[100];
	FILE *f;
	f = fopen("human.txt", "r");
	if(f == NULL){
		printf("ERROR\n");
		return 0;
	}
	while(fgets(buffer, sizeof(buffer), f) != NULL){
		n++;
	}
	fclose(f);
	
	int i, j;
	struct Human people1[n];
	struct Human people2[n];
	
	f = fopen("human.txt", "r");
	if(f == NULL){
		printf("ERROR\n");
		return 0;
	}	
	
	for(i = 0; i < n ; i++){
		fgets(buffer, sizeof(buffer), f);
		sscanf(buffer, "%s %s %d", people1[i].surname, people1[i].name, &people1[i].year);
		people2[i] = people1[i];

		}
	for(i = 0; i < n-1; i++) {
	        for(j = 0; j < n-i-1; j++) {
	            if(people2[j].year > people2[j+1].year) {
	                struct Human temp = people2[j];
	                people2[j] = people2[j+1];
	                people2[j+1] = temp;
	            }
	        }
	    }
	
	fclose(f);
	for (i = 0; i < n; i++) {
    printf("%s %s, %d\n", people2[i].surname, people2[i].name, people2[i].year);
	}
	
	return 0;

}
