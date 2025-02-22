#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	
	double M[3][3];
	
	int i,j;
	
	for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("Vvedite element [%d][%d]: ", i, j);
            scanf("%lf", &M[i][j]);
        }
    }
	printf("Summa glavnoi: %lf", M[0][0] + M[1][1] + M[2][2]);
	printf("Summa pobochnoi: %lf\n", M[0][2] + M[1][1] + M[2][0]);

	int F[2][2];
	int p1, p2;
	for (p1 = 0; p1 < 2; p1++){
		for (p2 = 0; p2 < 2; p2++){
		printf("Vvedite element [%d][%d]:", p1, p2);
		scanf("%d", &F[p1][p2]);
		}
	}
    int s[2][2];
    s[0][0] = F[0][0] * F[0][0] + F[0][1] * F[1][0];
    s[0][1] = F[0][0] * F[0][1] + F[0][1] * F[1][1];
    s[1][0] = F[1][0] * F[0][0] + F[1][1] * F[1][0];
    s[1][1] = F[1][0] * F[0][1] + F[1][1] * F[1][1];
    
    printf("Kvadrat matrix:\n");
    for (p1 = 0; p1 < 2; p1++) {
        for (p2 = 0; p2 < 2; p2++) {
            printf("%d ", s[p1][p2]);
        }
        printf("\n");
    }	
	
		
	
	return 0;
}
