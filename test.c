#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE* open;
	char** a;
	char* token;
	const char delim[2] = ":";
	int i = 0;
	char* test;
	int w,x,y,z;
	printf("%s\n", strstr("comicsans.fsf impact.fsf","impact.fsf"));
	char c[256] = "CHARACTERn:320 46 19 40";
	char d[10] = "CHARACTER";
	char* e = "n";
	

	strcat(d, e);
	printf("%s\n",d);
	printf("%s\n",c);
	token = strtok(c,":");
	token = strtok(NULL,":");
	printf("%s\n",token);
	strcpy(c, token);
	sscanf( c, "%d %d %d %d", &w, &x, &y, &z );
	printf("%d %d %d %d\n",w,x,y,z);
	
	/*
	if(test != NULL)
	{
		printf("%s\n", test);
	}
	*/
	
	/*
    open = fopen("confessproject.act", "r");
	
	if (open == 0)
	{
		printf("File not found!\n");
		return -1;
	}
	char c;

	a =(char**) malloc (5*sizeof(char*));
	for(i = 0; i < 5; i++)
	{
		a[i] = (char*) malloc(1000*sizeof(char));
	}
	
	for(i = 0; i < 5; i++)
	{
		fgets(a[i], 1000, open);
		printf("%s\n", a[i]);
	}
	
	
	for(i = 0; i < 5; i++)
	{
		token = strtok(a[i], delim);
		token = strtok(NULL, delim);
		printf("%s\n", token);
		strcpy(a[i], token);
	}

	
	for(i = 0; i <5; i++)
	{
		if(a[i] != NULL)
		{
		printf("a[%d] %s\n",i, a[i]);
	
		}
	}
	
	*/
}
