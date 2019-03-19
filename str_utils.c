#include<stdio.h>
#include<string.h>
#include "files.c"

typedef struct Array_struct Array;

struct Array_struct {
	void* data;
	int len;
};

Array* substring(Array input_str, int len) {
	char* str = (char*)input_str.data;
	
	int subs_count = input_str.len - len + 1;
	Array* subs = malloc(sizeof(Array) * subs_count);
	
	for(int i = 0; i < subs_count; i++) {
		char* str1 = malloc(len + 1);
		strncpy(str1, str + i, len);
		str1[len] = '\0';
		
		subs[i].data = str1;
		subs[i].len = len;
	}
	Array* result = malloc(sizeof(Array));
	result->data = subs;
	result->len = subs_count;
}

void add(String s1, char c) {
	
}


