#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	char str[81] = "";
	printf("Vvedite text:");
	scanf("%80s", str);
	int t = 0;
	while (t < strlen(str)) {
		if (str[t] == 'a'){
			str[t] = 'A';
		}
		if (str[t] == 'b'){
			str[t] = 'B';
		}
		t++;
	}
	printf("Result: %s", str);
	

	
	return 0;
}
