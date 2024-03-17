#include <stdio.h>
#include <stdlib.h>

int main(int args, char **argv) {
	printf("Hello World!\n");

	if (args != 4) {
		printf("Usage: bin/crr [expiry] [call strike] [put strike]\n");
		exit(0);
	} 

	int expiry = atoi(argv[1]);
	double call_strike = atof(argv[2]);
	double put_strike = atof(argv[3]);
	
	printf("%d %f %f\n", expiry, call_strike, put_strike);
	
	return 0;
}
