#include<stdio.h>
#include<time.h>
#include<sys/time.h>

void main() {
	struct timespec t1;
	char c;
	while((c = getchar()) != 'x') {
		tspec_get(&t1, 0);
		
		printf("%d,%d", t1.tv_nsec, t1.tv_sec);
	}
}
