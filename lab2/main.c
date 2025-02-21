#include <stdio.h>
int main(){
double x1, y1, z1;
double x2, y2, z2;
double x3, y3, z3;

printf("Vvedite 1 stroku: ");
scanf("%lf %lf %lf", &x1, &y1, &z1);

printf("Vvedite 2 stroku: ");
scanf("%lf %lf %lf", &x2, &y2, &z2);

printf("Vvedite 3 stroku: ");
scanf("%lf %lf %lf", &x3, &y3, &z3);

printf("Summa glavnoi: %lf\n", x1 + y2 + z3);
printf("Summa bobochnoi: %lf\n", z1 + y2 + x3);

int c1, c2;
int v1, v2;

printf("Vvedite 1 stroku: ");
scanf("%d %d", &c1, &c2);

printf("Vvedite 2 stroku: ");
scanf("%d %d", &v1, &v2);

int r1 = c1 * c1 + c2 * v1;
int r2 = c1 * c2 + c2 * v2;
int r3 = v1 * c1 + v2 * v1;
int r4 = v1 * c2 + v2 * v2;

printf("Kvadrat matrx:\n");
printf("%d %d\n", r1, r2);
printf("%d %d\n", r3, r4);


return 0;
}
