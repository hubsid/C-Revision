#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void heapify(int[], int, int);
void build(int[], int);
int verify(int[], int, int);
void heapsort(int[], int);

void main() {
	int n;
	scanf("%d", &n);

	int a[n];
	for(int i = 1; i <= n; i++) scanf("%d", a + i);

	build(a, n);
	int check_res = verify(a, 1, n);

	printf("\nresult=%d\n", check_res);
	
	heapsort(a, n);

	puts("---");
	for(int i = 1; i <= n; i++)
		printf("%d ", a[i]);
}

void heapify(int a[], int root, int n) {
	int l = 2 * root;
	int r = l + 1;
	int lar;
	if(l <= n && a[l] > a[root]) lar = l;
	else lar = root;
	if(r <= n && a[r] > a[lar]) lar = r;

	if(lar != root) {
		int temp = a[root];
		a[root] = a[lar];
		a[lar] = temp;
		heapify(a, lar, n);
	}
}

void build(int a[], int n) {
	int mid = n/2;

	for(int i = mid; i > 0; i--)
		heapify(a, i, n);
}

int verify(int a[], int root, int n) {
	int l = 2 * root;
	int r = l + 1;

	int left;
	if(l <= n) {
		if(a[l] > a[root]) return 0;
		else left = verify(a, l, n);
	}
	if(!left)
		return 0;

	if(r <= n) {
		if(a[r] > a[root]) return 0;
		else  verify(a, r, n);
	}
	return 1;
}

void heapsort(int a[], int n) {
	for(int i = n; i > 0; i--) {
		int temp = a[i];
		a[i] = a[1];
		a[1] = temp;

		heapify(a, 1, i - 1);
	}
}
