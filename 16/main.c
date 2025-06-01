#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	typedef unsigned char      u8;
	typedef unsigned short int u16;
	typedef unsigned int       u32;
	typedef unsigned long long u64;
	
	u8 CountOnes1 (u8 n) {
	 	u8 res = 0;
		while (n) {
			res ++;
		    n &= n-1;  // Забираем младшую единичку.
		}
		return res;
		}
		
	u8 CountOnes2_FF (u32 n) {
    u8 *p = (u8*)&n;
    n = BitsSetTableFF[p[0]]
      + BitsSetTableFF[p[1]]
      + BitsSetTableFF[p[2]]
      + BitsSetTableFF[p[3]];
    return n;
  }
	return 0;
}
