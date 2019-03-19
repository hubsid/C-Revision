#include<stdio.h>
#include<string.h>
#include "stringutil.h"
#include "files.h"

void main(){
	String str = fget_str("sidh.sub");
	char *s = str.str;
	char patt[7] = "\n     ";

	Search_res res = find(str, (String){patt, 6});

	int i, j;
	scanf("%d%d", &i, &j);

	if(j < i) {
		int temp = j;
		j = i;
		i = temp;
	}
	else if(j == i)
		return;

	char *p1_beg, *p1_end, *p2_beg, *p2_end;

	if(i < 1) i = 1;
	p1_beg = (i == 1) ? s : s + res.match[i - 2];
	p1_end = s + res.match[i - 1];

	if(j > res.match_count + 1)
		j = res.match_count + 1;
	p2_beg = s + res.match[j - 2];
	p2_end = (j == res.match_count + 1) ? s + str.n - 1 : s + res.match[j - 1];
		
	int p1_len = p1_end - p1_beg;
	int p2_len = p2_end - p2_beg;
	int p_gap_len = p2_beg - p1_end;

	char *p1 = substr1(p1_beg, p1_end);
	char *p2 = substr1(p2_beg, p2_end);
	char *p_gap = substr1(p1_end, p2_beg);

	strncpy(p1_beg, p2, p2_len);
	p1_end = p1_beg + p2_len;
	strncpy(p1_end, p_gap, p_gap_len);
	p2_beg = p2_end - p1_len;
	strncpy(p2_beg, p1, p1_len);

	FILE *fp = fopen("sidh.sub", "w");
	fputs(s, fp);
	fclose(fp);
}
