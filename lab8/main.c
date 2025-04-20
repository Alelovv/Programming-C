#include <stdio.h>
#include <string.h>
#include <locale.h>

struct Person {
    char last_name[20];
    char first_name[20];
    int year;
    char gender;
    int height;
};

int main() {
	char *locale = setlocale(LC_ALL, "");
    FILE *f = fopen("text.txt", "r");
    if (f == NULL) {
        printf("Error\n");
        return 1;
    }

    struct Person p[100];
    int n = 0;
    int i, j;
    while (n < 100 && fscanf(f, "%s %s %d %c %d", 
           p[n].last_name, 
           p[n].first_name, 
           &p[n].year, 
           &p[n].gender, 
           &p[n].height) == 5) {
        n++;
    }
    fclose(f);

    if (n == 0) {
        printf("Error!\n");
        return 1;
    }

    printf("Sort for:\n");
    printf("1 - S\n2 - N\n3 - Y\n4 - G\n5 - H\n");
    int choice;
    scanf("%d", &choice);

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i; j++) {
            int swap = 0;
            
            switch(choice) {
                case 1: 
                    if (strcmp(p[j].last_name, p[j+1].last_name) > 0) swap = 1;
                    break;
                case 2:
                    if (strcmp(p[j].first_name, p[j+1].first_name) > 0) swap = 1;
                    break;
                case 3:
                    if (p[j].year > p[j+1].year) swap = 1;
                    break;
                case 4:
                    if (strcmp(p[j].gender, p[j+1].gender) > 0) swap = 1;
                    break;
                case 5:
                    if (p[j].height > p[j+1].height) swap = 1; 
                    break;
            }
            
            if (swap) {
                struct Person temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    printf("\nresult:\n");
    for (i = 0; i < n; i++) {
        printf("%s %s %d %c %d\n", 
               p[i].last_name, 
               p[i].first_name, 
               p[i].year, 
               p[i].gender, 
               p[i].height);
    }

    return 0;
}
