#include<stdio.h>
struct Booleans {
	unsigned char male:6;
	unsigned char trans:3;
};
void main() {
	struct Booleans new_bool;
	new_bool.male = 15;
	new_bool.trans = 19;
	
	printf("%d,%d,%d", new_bool.male, new_bool.trans, sizeof(new_bool));
	
}
