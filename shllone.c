#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#define MAXLINE 80

void setup(char inputBuffer[],char *argv[])
{
	int i,j;
	char *p;
	i=0;
	for (p=inputBuffer; ;p++)
	{
		argv[i++]=p;
		while (*p!=' '&&*p!='\0')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
	}
	argv[i]=NULL;
	execvp(argv[0],argv);
}

int main()
{
	char inputBuffer[MAXLINE];
	char *argv[MAXLINE/2-1];

	while (1)
	{
		printf ("COMMAND->");
		getline(inputBuffer,MAXLINE);
		printf("Show");
	}
	return 0;
}
