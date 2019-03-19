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
