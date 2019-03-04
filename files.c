<<<<<<< HEAD
=======
#include<stdio.h>
#include<string.h>

void main(){
	FILE* file = fopen("sidh.txt", "a");
	
	int prev_s[50];
	strcpy(prev_s, "000");
	char s[50];
	strcpy(s, "000");
	
	gets(s);
	puts("-");
	puts(s);
	puts("-");
	return;
		
	do {
		gets(s);
		
	}while(1);
	fclose(file);
}
>>>>>>> parent of b7fb4d5... jhgu

