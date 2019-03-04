#include<stdio.h>
#include<string.h>

void main(){
	
	char *str = "Iam fine";
	
	char str_dest[12];
	strcpy(str_dest, "12345678901\0");
	strcpy(str_dest, str);
	printf("%d\n%s", strlen(str), str_dest);
	
	int i;
	for(i = 0; i < 12; i++)
		printf("\n%c", str_dest[i]);
}

