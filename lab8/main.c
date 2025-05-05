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
    char locale = setlocale(LC_ALL, "");
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

    printf("Sort for (choose two fields):\n");
    printf("1 - S\n2 - N\n3 - Y\n4 - G\n5 - H\n");
    int choice1, choice2;
    printf("First field: ");
    scanf("%d", &choice1);
    printf("Second field: ");
    scanf("%d", &choice2);

    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            int swap = 0;

            switch(choice1) {
                case 1: 
                    if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                        swap = 1;
                    }
                    else if (strcmp(p[j].last_name, p[j+1].last_name) == 0) {
                        switch(choice2) {
                            case 1: 
                                if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 2:
                                if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 3:
                                if (p[j].year > p[j+1].year) {
                                    swap = 1;
                                }
                                break;
                            case 4:
                                if (p[j].gender > p[j+1].gender) {
                                    swap = 1;
                                }
                                break;
                            case 5:
                                if (p[j].height > p[j+1].height) {
                                    swap = 1;
                                }
                                break;
                        }
                    }
                    break;
                case 2:
                    if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                        swap = 1;
                    }
                    else if (strcmp(p[j].first_name, p[j+1].first_name) == 0) {
                        switch(choice2) {
                            case 1: 
                                if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 2:
                                if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 3:
                                if (p[j].year > p[j+1].year) {
                                    swap = 1;
                                }
                                break;
                            case 4:
                                if (p[j].gender > p[j+1].gender) {
                                    swap = 1;
                                }
                                break;
                            case 5:
                                if (p[j].height > p[j+1].height) {
                                    swap = 1;
                                }
                                break;
                        }
                    }
                    break;
                case 3:
                    if (p[j].year > p[j+1].year) {
                        swap = 1;
                    }
                    else if (p[j].year == p[j+1].year) {
                        switch(choice2) {
                            case 1: 
                                if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 2:
                                if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 3:
                                if (p[j].year > p[j+1].year) {
                                    swap = 1;
                                }
                                break;
                            case 4:
                                if (p[j].gender > p[j+1].gender) {
                                    swap = 1;
                                }
                                break;
                            case 5:
                                if (p[j].height > p[j+1].height) {
                                    swap = 1;
                                }
                                break;
                        }
                    }
                    break;
                case 4:
                    if (p[j].gender > p[j+1].gender) {
                        swap = 1;
                    }
                    else if (p[j].gender == p[j+1].gender) {
                        switch(choice2) {
                            case 1: 
                                if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 2:
                                if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 3:
                                if (p[j].year > p[j+1].year) {
                                    swap = 1;
                                }
                                break;
                            case 4:
                                if (p[j].gender > p[j+1].gender) {
                                    swap = 1;
                                }
                                break;
                            case 5:
                                if (p[j].height > p[j+1].height) {
                                    swap = 1;
                                }
                                break;
                        }
                    }
                    break;
                case 5:
                    if (p[j].height < p[j+1].height) {
                        swap = 1;
                    }
                    else if (p[j].height == p[j+1].height) {
                        switch(choice2) {
                            case 1: 
                                if (strcmp(p[j].last_name, p[j+1].last_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 2:
                                if (strcmp(p[j].first_name, p[j+1].first_name) > 0) {
                                    swap = 1;
                                }
                                break;
                            case 3:
                                if (p[j].year > p[j+1].year) {
                                    swap = 1;
                                }
                                break;
                            case 4:
                                if (p[j].gender > p[j+1].gender) {
                                    swap = 1;
                                }
                                break;
                            case 5:
                                if (p[j].height > p[j+1].height) {
                                    swap = 1;
                                }
                                break;
                        }
                    }
                    break;
            }

            if (swap) {
                struct Person temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    printf("result:\n");
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
