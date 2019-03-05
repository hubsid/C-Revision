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

struct wordlist* fget_words(char* file_name, char* delim) {
	FILE* file = fopen(file_name, "r");
	if(!file) {
		printf("file cannot be opened.");
		return NULL;
	}
	
	char buf_str[BLOCK_N];
	char *overflow = NULL;
	int of_len = 0;
	char ** cp = malloc(sizeof(char*));
	int n = 0;
	
	while(fgets(buf_str, BLOCK_N, file)) {
		puts("block");
		char* p = buf_str, *prev_p = buf_str;
		if(overflow) {
			for(; *p != '\0'; p++) {
				for(char *p1 = delim; *p1 != '\0'; p1++) {
					if(*p1 == *p) {
						int len = p - prev_p;
						if(len > 0) {
							char* temp_str = malloc(len);
							strncpy(temp_str, prev_p, len);
							char* overflow1 = realloc(overflow, len + of_len + 1);
							if(!overflow1) {
								puts("overflow1's realloc failed...'");
								exit(0);
							}
							overflow = overflow1;
							strncpy(overflow + of_len, temp_str, len);
							overflow[of_len + len] = '\0';
							free(temp_str);
							
							char* tmp = overflow;
							overflow = NULL;
							of_len = 0;
							char** cp_tmp = realloc(cp, ++n * sizeof(char*));
							if(!cp_tmp) {
								puts("cp's 'realloc failed...");
								exit(0);
							}
							cp = cp_tmp;
							cp[n-1] = tmp;
							prev_p = p+1;
							goto exit_lbl;							
						}
						
					}
				}
			}
		}
		exit_lbl:
		for(; *p != '\0'; p++) {
			for(char *p1 = delim; *p1 != '\0'; p1++) {
				if(*p1 == *p) {
//					puts("match");
					int len = p - prev_p;
					if(len > 0) {
						char* temp_str = malloc(len + 1);
//						printf("*prev_p=%c,*p=%c,temp_str before copy=%s\n", *p, *prev_p, temp_str);
						strncpy(temp_str, prev_p, len);
						temp_str[len] = '\0';
//						printf("len=%d\ntemp_str=%s\n", len, temp_str);
						char** cp_tmp = (char**)realloc(cp, ++n * sizeof(char*));
						
						if(!cp_tmp) {
//							printf("realloc failed...");
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
		if(prev_p != p) {
			int len = p - prev_p;
			if(overflow)
				overflow = realloc(overflow, of_len + len);
			else
				overflow = malloc(len);
			strncpy(overflow + of_len, prev_p, len);
			of_len += len;			
		}
	}
	printf("offset length=%dn\n", of_len);
	if(overflow) {
		overflow = realloc(overflow, of_len + 1);
		overflow[of_len] = '\0';
		cp = realloc(cp, ++n *sizeof(char*));
		
		cp[n-1] = overflow;
	}
	
	struct wordlist *list = malloc(sizeof(struct wordlist));
	list->first = cp;
	list->len = n;
	return list;
}

int main() {
	
	struct wordlist *list = fget_words("sidh.sub", "\n ");
	printf("size:%d\n", list->len);
	
	for(int i = 0; i < list->len; i++)
		printf("%d\t%s\n", strlen(list->first[i]), list->first[i]);
	
	return 0;
}
