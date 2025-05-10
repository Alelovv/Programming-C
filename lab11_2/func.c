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

int min(int count, ...) {
    va_list args;
    int total[count];
    int i, j;
    
    va_start(args, count);
    for(i = 0; i < count; i++) {
        total[i] = va_arg(args, int);
    }
    va_end(args);
    for (i = 0; i < count - 1; i++){
    	for(j = 0; j < count - i - 1; j++){
    		if(total[j] > total[j + 1]){
    			int temp = total[j];
    			total[j] = total[j + 1];
    			total[j+1] = temp;
			}
		}
	}
    return total[0];
}

int max(int count, ...) {
    va_list args;
    int total[count];
    int i, j;
    
    va_start(args, count);
    for(i = 0; i < count; i++) {
        total[i] = va_arg(args, int);
    }
    va_end(args);
    for (i = 0; i < count - 1; i++){
    	for(j = 0; j < count - i - 1; j++){
    		if(total[j] > total[j + 1]){
    			int temp = total[j];
    			total[j] = total[j + 1];
    			total[j+1] = temp;
			}
		}
	}
    return total[count - 1];
}

double ave(int count, ...) {
    va_list args;
    int total = 0;
    int i;
    
    va_start(args, count);
    for(i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total / count;
}


