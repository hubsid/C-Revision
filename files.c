#include<stdio.h>
#include<string.h>

void main(){
	FILE* file = fopen("sidh.txt", "r");
	if(!file) {
		puts("the file pointer is null");
		return;
	}
	char s[100];
	
	char* strs = malloc(1);
	*strs = '\0';
	char* cp = strs;
	int len;
	int size = 0;
	while(fgets(s, 100, file) != NULL) {
		len = strlen(s);
		printf("len=%d, size=%d\n", len, size);
		size += len;
		strs = realloc(strs, size+1);
		if(!strs) {
			puts("not able to allocate memory, when trying to copy the string :");
			puts(s);
			break;
		}
		strcpy(cp, s);
		printf("+len=%d, size=%d\n", len, size);
		cp += len;
		
		printf("allocation size:%d bytes\n", size);
	}
	puts("the file is :");
	puts(strs);
	fclose(file);
}

