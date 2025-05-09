#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main() {
	char locale = setlocale(LC_ALL, "");
    char expr[100];
    char* token;
    double num;
    double result = 0;
    char op = '+';

    printf("Введите выражение:\n ");
    fgets(expr, 100, stdin);
    
    expr[strlen(expr)-1] = '\0';

    token = strtok(expr, "+-");
    
    while (token != NULL) {
        num = atof(token);
        
        if (op == '+') result += num;
        else result -= num;
        
        op = expr[token - expr + strlen(token)];
        
        token = strtok(NULL, "+-");
    }
    
    printf("Результат: %.2f\n", result);
    return 0;
}
