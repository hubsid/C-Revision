#include<stdio.h>

int divide(int a[], int p, int r) {
	int x = a[r];
	int i = p - 1;
	for(int j = p; j < r; j++) {
		if(a[j] < x) {
			i++;
			int tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}
	}
	i++;
	a[r] = a[i];
	a[i] = x;

	return i;
}

void quicksort(int a[], int p, int r) {
	if(p < r) {
		printf("%d-%d\n", p, r);
		int q = divide(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++) scanf("%d", a + i);

	quicksort(a, 0, n - 1);
	// int piv = divide(a, 0, n - 1);

	puts("---");
	// printf("%d\n", piv);
	for(int i = 0; i < n; i++) printf("%d ", a[i]);
		
	return 0;
}
