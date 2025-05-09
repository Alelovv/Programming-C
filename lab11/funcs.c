#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double num() {
    char n0[100];
    double n;

    printf("input number(s):\n");
    fgets(n0, sizeof(n0), stdin);
    n0[strcspn(n0, "\n")] = '\0';

    char *token = strtok(n0, " ");
    if (token == NULL) {
        printf("Error: empty input\n");
        return 0;
    }

    n = atof(token);
    printf("%lf", n);

    return n;
}