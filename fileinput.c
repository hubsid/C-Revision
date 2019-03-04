#include<stdio.h>
#define MAX_SIZE_WORD 20

struct node {
	char *char_ptr;
	struct node *next;
};

struct node* add(char *p) {
	static struct node* prev = NULL;
	struct node* curr = (struct node*) malloc(sizeof(struct node));
	
	curr->char_ptr = p;
	curr->next = prev;
	prev = curr;
	
	return curr;
}

void main(){
	FILE *file = NULL;
	
	file = fopen("inputfile.txt", "r");
	
	if(!file) {
		file = fopen("inputfile.txt", "w");
		fclose(file);
		file = fopen("inputfile.txt", "r");
		if(!file) {
			printf("no such file or file cannot be opened.");
			return;
		}
	}
	
	int word = 0;
	char c;
	int len = 0;
	char temp_word[MAX_SIZE_WORD];
	char *word_p;
	struct node* words = NULL;
	while((c = fgetc(file)) != EOF) {
		if(! (c == '\n' || c == ' ' || c == '\t')) {
			if(!word) {
				//initialize new word
				len = 0;
				word = 1;
			}
			if(len < MAX_SIZE_WORD) {
				len++;
				temp_word[len] = c;
			}
		}
		else {
			if(word) {
				//finish created word
				
				word = 0;
			}
		}
	}
	fclose(file);	
}

