#include <stdio.h>

int main() {
	FILE *f;
	int randomNumber;

	f = fopen("/dev/RndNum", "r");
	fread(&randomNumber, sizeof(int), 1, f);
  	printf("The random number: %d\n",randomNumber);
	fclose(f);
	return 0;
};
