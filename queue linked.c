#include <stdio.h>
#include "linkedlist.h"

void main() {
	int op;
	int val;

	while(1) {
		scanf("%d", &op);
		if(op == 1) {
			scanf("%d", &val);
			append(val);
			puts("queued");
		}
		else if(op == 2) {
			if(head) {
				int key = head->key;
				delete(head);
				printf("dequeued value: %d\n", key);
			}
			else
				puts("emqty queue.");
		}
		else if(op == 3) {
			print_f();
		}
		else
			break;
	}
}