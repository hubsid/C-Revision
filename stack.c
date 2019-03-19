#include<stdio.h>
#define MAX_SIZE 10
#define EMPTY_STACK -36726

int stack[MAX_SIZE];
int head = -1;

int push(int key) {
	if(head < MAX_SIZE - 1) {
		stack[++head] = key;
		return 1;
	}
	else
		return 0;
}

int pop() {
	if(head < 0)
		return EMPTY_STACK;
	else
		return stack[head--];
}

void print() {
	puts("---");
	for(int i = 0; i <= head; i++) printf("%d ", stack[i]);
	puts("\n");
}

int main() {

	int op = 1;
	int key;
	while(op) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d", &key);

			int res = push(key);
			if(!res) puts("cannot push further !");
			else	puts("pushed.");
		}
		else if(op == 2) {
			int res = pop();
			if(res == EMPTY_STACK) puts("empty stack");
			else printf("%d is popped", res);
		}
		else if(op == 3) print();
	}
	return 0;
}
