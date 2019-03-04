#include<stdio.h>
#include<string.h>
void main(){

char * temp = malloc(3);
temp[0] = 'a';
temp[1] = 'b';
temp[2] = 'c';

char s[] = "xyzrs";

strncpy(temp, s, 2);

printf("%c,%c,%c,", temp[0], temp[1], temp[2]);
}

