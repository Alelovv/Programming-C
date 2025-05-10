#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    char input[256];
    printf("Input expression: ");
    fgets(input, sizeof(input), stdin);
    
    double result = 0;
    char *ptr = input;
    int sign = 1;
    
    while (*ptr != "\0") {
        if (*ptr == ' ') {
			ptr++;
			continue;
		}
        
        if (*ptr == '+') {
            sign = 1;
            ptr++;
        } 
        else if (*ptr == '-') {
            sign = -1;
            ptr++;
        }
        
        char *end;
        double num = strtod(ptr, &end);
        if (ptr == end) {
        	break;
		}
        
        result += sign * num;
        ptr = end;
        sign = 1;  
    }
    
    printf("Result: %lf\n", result);
    return 0;
}
