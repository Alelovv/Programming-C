#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    int total = 0;
    int i;
    
    va_start(args, count);
    for(i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

int max(int count, ...) {
    va_list args;
    int max_val;
    int i;
    
    va_start(args, count);
    max_val = va_arg(args, int);
    for(i = 1; i < count; i++) {
        int num = va_arg(args, int);
        if(num > max_val) max_val = num;
    }
    va_end(args);
    return max_val;
}

int min(int count, ...) {
    va_list args;
    int min_val;
    int i;
    
    va_start(args, count);
    min_val = va_arg(args, int);
    for(i = 1; i < count; i++) {
        int num = va_arg(args, int);
        if(num < min_val) min_val = num;
    }
    va_end(args);
    return min_val;
}

float average(int count, ...) {
    va_list args;
    int total = 0;
    int i;
    
    va_start(args, count);
    for(i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return (float)total / count;
}
