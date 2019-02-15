#include<stdio.h>
#include<string.h>

struct Family {
	char* father;
	char* mother;
	char* child[5];
};
void main(){
	struct Family myfam;
	
	myfam.father = "Ramesh";
	myfam.mother = "Chithra";
	myfam.child[0] = "Me";
	
	struct Family* p_fam = &myfam;
	
	printf("Family details:\nFather:%s\nMother:%s\nChild:%s", p_fam->father, p_fam->mother, p_fam->child[0]);
	printf("\n%d,%d", sizeof(myfam), sizeof(p_fam));
}
