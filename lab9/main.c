#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  
#include <locale.h>
int main() {
	char *locale = setlocale(LC_ALL, "");
    char str[256]; 
    printf("Введите выражение: ");
    fgets(str, sizeof(str), stdin);

    double result = 0.0;
    char *sep = str;  
    char *end;   
    int first = 1;    

    while (*sep) {
        while (isspace(*sep)) sep++;
        if (!*sep) break;

        if (first) {
            result = strtod(sep, &end);
            sep = end;
            first = 0;
        } else {
            char op = *sep++;
            double num = strtod(sep, &end);
            sep = end;
            result += (op == '+' ? num : -num);  
        }
    }

    printf("Результат: %g\n", result);
    return 0;
}









