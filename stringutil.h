#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char* str;
	int n;
} String;

String null_str() {
	String s;
	s.n = 0;
	s.str = malloc(1);
	s.str[0] = '\0';
	return s;
}

String substr(String str_in, int m, int n) {
	
	if(m < 0 || n < 0 || m > n || m >= str_in.n || n >= str_in.n) {
		return null_str();
	}
	int len = n - m;
	char* str_out = (char*)malloc(len + 1);
	str_out[len] = '\0';
	strncpy(str_out, str_in.str + m, len);
	
	String s;
	s.n = len;
	s.str = str_out;
	
	return s;
}

String insert(String source, int pos, String ins) {
	String result;
	result.n = source.n + ins.n;
	if(pos <= 0) {
		
	}
	
}
