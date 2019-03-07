#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void main() {
	struct X
	{
		int a;
	};
	struct X x;
	x.a = 89;

	struct timespec* ts = malloc(sizeof(struct timespec));
	int res = timespec_get(ts, 0);
	printf("%d\n", ts->tv_nsec);
	printf("%d\n", x.a);
	printf("%s\n", "sidharth from mingw gcc compiler");
}