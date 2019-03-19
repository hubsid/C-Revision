#include <stdio.h>

int main()
{
	int n;
	int k;
	scanf("%d%d", &n, &k);
	int a[n];
	for(int i = 0; i < n; i++) scanf("%d", a + i);

	int tmp[k];
	for(int i = 0; i < k; i++) tmp[i] = 0;

	for(int i = 0; i < n; i++) tmp[a[i] - 1]++;

	for(int i = 1; i < k; i++) tmp[i] += tmp[i - 1];

	int res[n];
	for(int i = 0; i < n; i++) {
		res[tmp[a[i] - 1] - 1] = a[i];
		tmp[a[i] - 1]--;
	}

	puts("----");
	for(int i = 0; i < n; i++)	printf("%d ", res[i]);

	return 0;
}