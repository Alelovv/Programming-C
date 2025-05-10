#include <stdio.h>
#include <stdarg.h>

int sum(double n, ...) {
    va_list factor;
    double result = 0;
    int i;
    
    va_start(factor, n);
    for(i = 0; i < n; i++) {
        result += va_arg(factor, double);
    }
    va_end(factor);
    printf("%lf", result);
    return 0;
}

