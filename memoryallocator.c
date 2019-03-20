#include<stdio.h>
#define MAX_MEM 100;

int fp = 0;

int alloc(int size) {
	if(MAX_MEM - fp < size)
		return 0;
	else {
		fp += size;
		return 1;
	}
}

void main() {

	int op;
	int size;
	int ix;

	while(1) {
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &size);

			int res = alloc(size);
			if(!res)
				puts("not possible");
			else
				printf("allocated memory at index:%d", res);
		}
		else if(op == 2) {
			scanf("%d%d", &size, &ix);
			dlloc(ix, size);
		}
		else if(op == 3) {
			print_mem();
		}
		else
			break;
	}
}