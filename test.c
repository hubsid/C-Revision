#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "files.c"

int main() {
	char* str = "thethe some are really the jewels of the the  ";
	str = "";
	
	char* patt = "the";
	int patt_len = strlen(patt);
	
	char *c = str;
	int* match = malloc(sizeof(int));
	int word_count = 0;
	int match_count = 0;
	while(*c != '\0') {
		if(*c != ' ') {
			char *c1 = patt;
			while(*c != '\0' && *c1 != '\0' && *c != ' ' && *c == *c1)
				c++, c1++;			
			
			if(*c == '\0') {
				if(*c1 == '\0') {
					match = (int*)realloc(match, ++match_count * sizeof(int));
					match[match_count -1] = ++word_count;
				}
				break;
			}
			else if(*c == ' ') {
				if(*c1 == '\0') {
					match = (int*)realloc(match, ++match_count * sizeof(int));
					match[match_count -1] = word_count;
				}
				word_count++;
			}						
		}
		c++;
	}
	
	printf("word_count: %d\nmatch count: %d\n",word_count,  match_count);
	
	return 0;
}
