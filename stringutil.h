#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef STRINGUTIL_HEADER
#define STRINGUTIL_HEADER

typedef struct {
	char* str;
	int n;
} String;

typedef struct {
	int* match;
	int match_count;
}Search_res;

String null_str() {
	String s;
	s.n = 0;
	s.str = malloc(1);
	s.str[0] = '\0';
	return s;
}
String str(char* s) {
	String st;
	st.n = strlen(s);
	st.str = s;
	return st;
}
//TODO: create functions for adding chanracter & string to another string


String substr(String str_in, int m, int n) {
	
	if(m < 0 || n < 0 || m > n || m >= str_in.n || n >= str_in.n) {
		return null_str();
	}
	int len = n - m;
	char* str_out = malloc(len + 1);
	str_out[len] = '\0';
	strncpy(str_out, str_in.str + m, len);
	
	String s;
	s.n = len;
	s.str = str_out;
	
	return s;
}

char* substr1(char* s, char* t) {
	int len = t - s;
	char *str = malloc(len);
	strncpy(str, s, len);

	return str;
}

String insert(String source, int pos, String ins) {
	pos = pos < 0 ? 0 : pos > source.n ? source.n : pos;
	String result;
	result.n = source.n + ins.n;
	result.str = malloc(result.n + 1);
	result.str[result.n] = '\0';
	
	String sub1 = substr(source, 0, pos);
	String sub2 = substr(source, pos, source.n);
	
	strncpy(result.str, source.str, pos);
	strncpy(result.str + pos, ins.str, ins.n);
	strncpy(result.str + pos + ins.n, source.str + pos, source.n - pos);
	
	free(sub1.str);
	free(sub2.str);
	
	return result;
}

Search_res find(String str, String patt) {
	if(! (str.n > 0 && patt.n > 0 && str.n >= patt.n))
		return (Search_res) {NULL, 0};
	int word_len = str.n - patt.n + 1;
	
	char substr[patt.n + 1];
	substr[patt.n] = '\0';
		
	int *patt_index = malloc(word_len * sizeof(int));
	int match_len = 0;
	for(int i = 0; i < word_len;) {
		int j = 0;
		while(j < patt.n && str.str[i + j] == patt.str[j]) j++;
		if(j == patt.n) {
			patt_index[match_len++] = i;
			i += patt.n;
		}
		else {
			if(j) i += j;
			else i++;
		}
	}
	patt_index = realloc(patt_index, match_len * sizeof(int));
	return (Search_res){patt_index, match_len};
}

#endif