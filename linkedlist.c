<<<<<<< HEAD
#include<stdio.h>

typedef struct node{
	int key;
	struct node *next;
} Node;

Node *head = NULL;

void add(int key) {
	Node p = malloc(sizeof(Node));
	if(!head) {
		head = p;
	}
	else
}

int main(int argc, char const *argv[])
{
	return 0;
}
=======
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
	for(Node *p = last; p; p = p->prev);
		printf("%d ", p->key);
	putchar('\n');
}

int main() {


	return 0;
}
>>>>>>> e2285b296bb060b8c62457d7af8c36a49fb249bc
