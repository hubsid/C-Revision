#include<stdio.h>
#include<string.h>

#define BLOCK_N 20

struct wordlist {
	char **first;
	int len;
};

char* fget_str(char* file_name){
	FILE* file = fopen(file_name, "r");
	if(!file) {
		printf("file cannot be opened.");
		return NULL;
	}
	
	char str[BLOCK_N];
	int n = 1;
	int len;
	char *cp = malloc(1);
	
	while(fgets(str, BLOCK_N, file)) {
		len = strlen(str);
		char *cp1 = (char*)realloc(cp, n+len);
		if(!cp1) {
			printf("Problems  reallocating memory...");
			break;
		}
		cp = cp1;
		strcpy(cp + n-1, str);
		n += len;
	}
	fclose(file);
	return cp;
}

struct wordlist* fget_str_ps(char* file_name, char* delim) {
	FILE* file = fopen(file_name, "r");
	if(!file) {
		printf("file cannot be opened.");
		return NULL;
	}
	
	char str[BLOCK_N];
	char ** cp = malloc(sizeof(char*));
	int n = 0;
	int str_len;
	
	while(fgets(str, BLOCK_N, file)) {
		str_len = strlen(str);
		for(int i = 0; i < str_len; i++) {
			
		}
	}
	
	struct wordlist *list = malloc(sizeof(struct wordlist));
	list->first = cp;
	list->len = n;
	return list;
}

