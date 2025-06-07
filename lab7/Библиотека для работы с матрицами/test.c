#include <stdio.h>
#include "matrix.h"
int main()
{
 MATRIX A,B,C,D,E;
A=_mat_creat(4,4);
B=_mat_creat(4,4);
C=_mat_creat(4,4);
D=_mat_creat(4,4);
mat_fill_x(A,0.123);
mat_fill_y(B,0.23);
mat_fill_z(C,0.3);
mat_fill_t(D,2.0,3.0,4.0);
mat_dump(A);
printf("\n");
mat_dump(B);
printf("\n");
mat_dump(C);
printf("\n");
mat_dump(D);
printf("\n");
return 0;
}
