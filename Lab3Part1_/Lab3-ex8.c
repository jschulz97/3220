#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main(void)
{
	char *s, *dyn_s;
	int ln;
	printf("Enter the input string\n");
	scanf("%s",s);
	ln = strlen(s);
	dyn_s = malloc(ln+1);
	strcpy(dyn_s,s);
	dyn_s[ln]='\0';
	printf("%s",dyn_s);
	return 0;
}

