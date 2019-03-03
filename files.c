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
	
	char buf_str[BLOCK_N];
	char ** cp = malloc(sizeof(char*));
	int n = 0;
	int str_len;
	
	while(fgets(buf_str, BLOCK_N, file)) {
		puts("block");
		char *p, *prev_p;
		for(p = buf_str, prev_p = buf_str; *p != '\0'; p++) {
			for(char *p1 = delim; *p1 != '\0'; p1++) {
				if(*p1 == *p) {
					puts("match");
					int len = p - prev_p;
					if(len > 0) {
						char* temp_str = malloc(len + 1);
						printf("*prev_p=%c,*p=%c,temp_str before copy=%s\n", *p, *prev_p, temp_str);
						strncpy(temp_str, prev_p, len);
						temp_str[len] = '\0';
						printf("len=%d\ntemp_str=%s\n", len, temp_str);
						char** cp_tmp = (char**)realloc(cp, ++n * sizeof(char*));
						
						if(!cp_tmp) {
							printf("realloc failed...");
							exit(0);
						}
						cp = cp_tmp;
						cp[n-1] = temp_str;
					}
					prev_p = p+1;
					break;
				}
			}	
		}
//		if(prev_p != p-1)
	}
	
	struct wordlist *list = malloc(sizeof(struct wordlist));
	list->first = cp;
	list->len = n;
	return list;
}

int main() {
	
	struct wordlist *list = fget_str_ps("inputfile.txt", " ");
	printf("size:%d\n", list->len);
	
	for(int i = 0; i < list->len; i++)
		printf("%d\t%s\n", strlen(list->first[i]), list->first[i]);
	
	return 0;
}

