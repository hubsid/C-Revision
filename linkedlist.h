#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	struct node *prev;
	struct node *next;
	int key;
} Node;

Node *head = NULL;
Node *last = NULL;

void append(int key) {
	Node *p = malloc(sizeof(Node));
	p->key = key;
	p->next = NULL;

	if(head == NULL) {
		head = last = p;
		p->prev = NULL;
	}
	else {
		last->next = p;
		p->prev = last;
		last = p;
	}
}
void prepend(int key) {
	Node *p = malloc(sizeof(Node));
	p->key = key;
	p->prev = NULL;
	if(last == NULL) {
		last = head = p;
		p->next = NULL;
	}
	else {
		head->prev = p;
		p->next = head;
		head = p;
	}
}

Node search(int key) {
	Node *p = head;
	int i = 0;
	while(p && p->key != key)
		p = p-> next, i++;
	if(!p)
		return (Node){NULL, NULL, -1};
	return (Node){p, p, i};
}

void delete(Node *p) {
	if(p->prev)
		p->prev->next = p->next;
	else
		head = p->next;
	if(p->next)
		p->next->prev = p->prev;
	else
		last = p->prev;
	free(p);
}

void print_f() {
	puts("---");
	for(Node *p = head; p; p = p->next)
		printf("%d ", p->key);
	putchar('\n');
}

void print_r() {
	puts("---");
	for(Node *p = last; p; p = p->prev)
		printf("%d ", p->key);
	putchar('\n');
}

int main() {

	while(1) {
		int op;
		scanf("%d", &op);
		int val;
		if(op == 1) {
			scanf("%d", &val);
			append(val);
			puts("appended");
		}
		else if(op == 2) {
			scanf("%d", &val);
			prepend(val);
			puts("prepended");
		}
		else if(op == 3) {
			scanf("%d", &val);
			Node res = search(val);
			printf("index:%d\n", res.key);
		}
		else if(op == 4) {
			scanf("%d", &val);
			Node res = search(val);
			if(res.next) {
				delete(res.next);
				puts("deleted.");
			}
			else {
				puts("node doesn't exist");
			}
		}
		else if(op == 5) {
			print_f();
		}
		else if(op == 6) {
			print_r();
		}
		else
			break;
	}
	return 0;
}
