#include <stdio.h>
#include <setjmp.h>

jmp_buf env;
double j = 0;

void fibonaci(unsigned long long count, unsigned long long *sum, unsigned long long curr, unsigned long long next) {
    if (count <= 0) {
        longjmp(env, 1); 
    }

    *sum += curr;
    j +=1;
    printf("%llu\n", curr);
    if (j == 100){
    	printf("Limit: %lf \n", j);
    	longjmp(env, 1);
	}
    fibonaci(count - 1, sum, next, curr + next);
}

int main() {
	unsigned long long result = 0;
    unsigned long long count;
    printf("Input count: \n");
    scanf("%llu", &count);


    if (setjmp(env) == 0) {
        fibonaci(count, &result, 1, 1);
    } else {
        printf("Result: %llu\n", result);
    }
    return 0;
}

//longjmp() восстанавливает среду, сохраненную последним запросом setjmp()
//с передачей параметра __jmpb. По завершении longjmp(), выполнение программы 
//продолжается как будто соответствующий запрос setjmp () всего лишь возвратил 
//значение
