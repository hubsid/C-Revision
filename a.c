#include<stdio.h>

void main() {
	union Labr {
		int i;
		double f;
		char* name;
	};
	
	union Labr labr_kl;
	
	printf("%d", sizeof(labr_kl));
}
