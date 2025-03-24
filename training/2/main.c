#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main(int argc, char *argv[]) {
    int i;
    printf("Input grade:\n");
    scanf("%d", &i);
    
    switch(i) {
        case 2: 
            printf("Fail");
            break;
        case 3: 
            printf("Middle");
            break;
        case 4: 
            printf("Good");
            break;
        case 5: 
            printf("Excellent!");
            break;
        default:  
            printf("ERROR");
    }
    
    return 0;
}
