#include <stdio.h>

int main() {
    FILE *F;
    FILE *out;
    char s[250];
    out = fopen("rez.txt", "w");
    F = fopen("Fio.txt", "r");
    if (F == NULL) {
        printf("ERROR\n");
        return 0;
    }

    while (fgets(s, 100, F) != NULL) {
        char f[70], i[70], o[70]; 
        int year;
        sscanf(s, "%s %s %s %d", f, i, o, &year);
        if (year > 1980) {
            fprintf(out, "%s", s);
        }
    }

    fclose(F);
    fclose(out);
    return 0;
}
