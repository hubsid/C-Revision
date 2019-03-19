#include<stdio.h>
#include<math.h>

int main(int argc, char const *argv[])
{
<<<<<<< HEAD
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		 printf("%d ", (int)((1 + sin(100 * i)) * 50));
	}

=======
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

>>>>>>> e2285b296bb060b8c62457d7af8c36a49fb249bc
	return 0;
}