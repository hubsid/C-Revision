#include<stdio.h>
#include<string.h>
#define realloc_size 10000
void main() {
	char *cp = malloc(20);
	int len = 0;
	while(1) {
		len += realloc_size;
		cp = realloc(cp, len);
		if(!cp) {
			printf("realloc failed at %d bytes.\n", len);
			break;
		}
		printf("%d\n", len);
	}
}
