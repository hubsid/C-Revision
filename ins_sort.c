#include<stdio.h>
#include "files.h"

void merge(int[], int, int, int);
void mergesort(int[], int, int);

int main() {
	int n;

	scanf("%d", &n);

	int a[n];
	for(int i = 0; i < n; i++)
		scanf("%d", a + i);

	mergesort(a, 0, n - 1);

	puts("-------");
	for(int i = 0; i < n; i++)
		printf("%d ", a[i]);

	return 0;
}

void mergesort(int a[], int p, int r) {
	if(p < r) {
		int q = (p + r)/2;
		mergesort(a, p, q);
		mergesort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

void merge(int a[], int p, int q, int r) {
	int n = r - p + 1;
	int b[n];

	int i = p, j = q + 1, k = 0;
	while(i <= q && j <= r) {
		if(a[i] <= a[j]) {
			b[k++] = a[i];
			i++;
		}
		else {
			b[k++] = a[j];
			j++;
		}
	}
	for(int start = (i == q + 1) ? j : i; k < n; k++, start++)
		b[k] = a[start];

	for(i = p, k = 0; k < n; k++, i++)
		a[i] = b[k];
}