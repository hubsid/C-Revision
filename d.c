#include<stdio.h>

void main(){
	int arr[][4] = {{11, 22, 33, 44}, {12, 13, 14, 15}};
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 4; j++)
			printf("%d,", *(*(arr+i) +j));
	}
}
