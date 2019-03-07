#include<stdio.h>
#include<string.h>
#include "stringutil.h"

void main(){

	char str[1];
	str[0] = '\0';
	
	char str1[1];
	str1[0] = '\0';
	
	puts(strcat(strcat(str, "im fine ."), str1));
}

