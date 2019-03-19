#include<stdio.h>

typedef struct {
	int beg;
	int end;
	int sum;
} Sub;

Sub mid_cross(int a[], int beg, int mid, int end) {
	int left_sum = -1000;
	int max_left = mid;
	int sum = 0;
	for(int i = mid; i >= beg; i--) {
		sum += a[i];
		if(sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = -1000;
	int max_right = mid < end ? mid + 1 : mid;
	sum = 0;
	for(int i = mid + 1; i <= end; i++) {
		sum += a[i];
		if(sum > right_sum) {
			right_sum = sum;
			max_right = i;
		}
	}

	return (Sub) {max_left, max_right, left_sum + right_sum};
}

Sub max_subarray(int a[], int beg, int end) {
	if(beg == end)
		return (Sub) {beg, end, a[beg]};
	int mid = (beg + end)/2;
	printf("\nsubarray of :[%d,%d]", beg, end);

	Sub left_sub = max_subarray(a, beg, mid);
	Sub right_sub = max_subarray(a, mid + 1, end);
	Sub mid_sub = mid_cross(a, beg, mid, end);

	if(left_sub.sum > right_sub.sum) {
		if(left_sub.sum > mid_sub.sum)
			return left_sub;
		else
			return mid_sub;
	}
	else {
		if(right_sub.sum > mid_sub.sum)
			return right_sub;
		else
			return mid_sub;
	}
}

int main() {
	int n;
	scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++) scanf("%d", a + i);

	Sub msa = max_subarray(a, 0, n - 1);
	
	printf("\nres:[%d,%d,%d]", msa.beg, msa.end, msa.sum);
	return 0;
}
