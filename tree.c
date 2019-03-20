#include <stdio.h>
#include <stdlib.h>
#include<math.h>

typedef struct node {
	int key;
	struct node *par;
	struct node *left;
	struct node *right;
} Node;


Node* combine(Node* l_tree, int key, Node* r_tree) {
	Node* mid_node = malloc(sizeof(Node));
	mid_node->key = key;
	mid_node->left = l_tree;
	mid_node->right = r_tree;

	if(l_tree)
		l_tree->par = mid_node;
	if(r_tree)
		r_tree->par = mid_node;
	mid_node->par = NULL;
	return mid_node;
}

Node* make_tree(int a[], int p, int r) {
	// printf("inside make_tree, p = %d, r = %d\n", p, r);
	if(p + 1 < r) {
		int q = (p + r)/2;
		Node *l_tree = make_tree(a, p, q - 1);
		Node *r_tree = make_tree(a, q + 1, r);

		return combine(l_tree, a[q], r_tree);
	}
	else if(p < r)
		return combine(combine(NULL, a[p], NULL), a[r], NULL);
	else if(p == r)
		return combine(NULL, a[p], NULL);
	return NULL;
}

int count_tree = 0;

void print_tree(Node *root) {
	if(root) {
		char* s = "root";
		if(root->par) {
			if(root->par->left == root)
				s = "left";
			else
				s = "right";
		}
		printf("%d\t%s\t%d\n", root->key, s, root->par ? root->par->key : -1);
		print_tree(root->left);
		print_tree(root->right);
	}
}

void print_tree_non_rec(Node *node) {
	Node *stack[7];
	int top = -1;
	int dir = 0; //0 - for down, 1 - up

	while(1) {
		if(!dir) {
			if(node->right)
				stack[++top] = node;
			if(node->left)
				node = node->left;
			else
				dir = 1;
		}
		else {
			if(top >= 0) {
				node = stack[top--] -> right;
				dir = 0;
			}
			else
				break;
		}
	}
}

void print_tree_non_rec_no_temp_storage1(Node *node) {
	int dir = 1; //1 - leftdown, 2- leftup, 3 - rightdown, 4 - rightup

	while(1) {
		printf("dir=%d\n", dir);
		if(dir == 1) {
			printf("%d\n", node->key);
			count_tree++;

			if(node->left)
				node = node->left;
			else
				dir = 3;
		}
		else if(dir == 3) {
			if(node->right) {
				node = node->right;
				dir = 1;
			}
			else
				dir = 4;
		}
		else if(dir == 4) {
			printf("node value = %d\n", node->key);
			if(node->par) {
				if(node->par->left == node)
					dir = 2;
				else
					node = node->par;
			}
			else
				break;
		}
		else {
			node = node->par;
			dir = 3;
		}
	}
}

Node* left_most(Node *node) {
	while(1) {
		printf("%d\n", node->key);
		count_tree++;
		if(node->left)
			node = node->left;
		else
			break;
	}
	return node;
}

void print_tree_non_rec_no_temp_storage2(Node *node) {
	while(1) {
		node = left_most(node);

		if(node->right)
			node = node->right;
		else {
			int found = 0;
			while(node->par) {
				if(node->par->right && node->par->right != node) {
					node = node->par;
					found = 1;
					break;
				}
				node = node->par;
			}
			if(found)
				node = node->right;
			else
				break;
		}
	}
}

void main() {
	const int max = 100;
	int a[max];

	for(int i = 0; i < max; i++)
		a[i] = i + 1;

	Node *root = make_tree(a, 0, max - 1);

	// print_tree(root);

	print_tree_non_rec_no_temp_storage2(root);

	printf("\n---\nelement count:%d\n", count_tree);
}
