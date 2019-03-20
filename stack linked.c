#include<stdio.h>
#include "linkedlist.h"

int push(int);
int pop();

void main() {
	int op;
	int val;

	while(1) {
		scanf("%d%d", &op, &val);
		if(op == 1) {
			prepend(val);
			puts("pushed.");
		}
		else if(op == 2) {
			if(head) {
				int key = head->key;
				delete(head);
				printf("popped value %d", key);
			}
			else
				puts("empty stack");
		}
		else if(op == 3) {
			print_f();
		}
		else
			break;
	}
}