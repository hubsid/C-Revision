#include<stdio.h>
#include<math.h>

int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		 printf("%d ", (int)((1 + sin(100 * i)) * 50));
	}

	return 0;
}