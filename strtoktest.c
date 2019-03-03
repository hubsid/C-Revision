#include<stdio.h>
#include<string.h>

void main(){
	char *delim = "a";
	char *source = "I came to the alter after the asterik was abated";
	char *result = strtok(source, delim);
	printf("lengthof result=%d", strlen(result));
}

