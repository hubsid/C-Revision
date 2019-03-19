#include<stdio.h>
#include<math.h>

int main(int argc, char const *argv[])
{
	int n, x, y;
	scanf("%d%d%d", &n, &x, &y);

	int a[n];
	int diff = y - x;
	for(int i = 0; i < n; i++) {
		float f = x + (trn(1000 * i) + 1) / 2 * diff;
		a[i] = f;
	}

	puts("---");
	for(int i = 0; i < n; i++) printf("%d ", a[i]);

	return 0;
}