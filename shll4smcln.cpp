#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#define MAXLINE 80
using namespace std;

int setup(char inputBuffer[],char *argv[])
{
	int i,j;
	char *p;//=(char*)malloc(MAXLINE*sizeof(char));
	i=0;
	for (p=inputBuffer; ;p++)
	{
		while(*p==' ')
		{
			p++;
		}
		if(*p=='\0')
			break;
		//argv[i]=(char*)malloc((MAXLINE/2-1)*sizeof(char));
		argv[i++]=p;
		while (*p!=' '&&*p!='\0')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
		p++;
		while(*p==' ')
		{
			p++;
		}
		p--;
	}
	//free (p);
	argv[i]=NULL;
	pid_t pid;
	pid=fork();
	if (pid==0)
	{
		if(execvp(argv[0],argv)!=0)//else is no used, even if succeed, 
		{
			perror("execvp fail");
			exit(1);
		}
	}
	else
		if(pid>0)
		{
			int status;
			if(-1==waitpid(pid,&status,0))
			{
				perror("wait failure");
				exit(1);
			}
			else
			{
				return status;
			}
		}
		else if(pid<0)
		{
			perror("fork error\n");
			exit(1);
		}
}



int main()
{
	char inputBuffer[MAXLINE];
	char *argv[MAXLINE/2-1];

	while (1)
	{
		printf ("COMMAND->");
		cin.getline(inputBuffer,MAXLINE);
		printf("Show\n");
		int result;
		if ((strcmp(inputBuffer, "exit") == 0))
		{
			exit(1);
		}
		else
		{
			char *p;//=(char*)malloc(MAXLINE*sizeof(char));
			char *input[MAXLINE];
			int i=0;
			for (p=inputBuffer; ;p++)
			{
				if(*p=='\0')
				{
					break;
				}
				//input[i]=(char*)malloc(MAXLINE*sizeof(char));
				input[i]=p;
				char*q;//=(char*)malloc(MAXLINE*sizeof(char));
				for(q=p;;q++)
				{
					if(*q!=';'&&*q!='\0')
					{
						continue;
					}
					else if(*q==';')
					{
						*q='\0';
						p=q;
						break;
					}
					else if(*q=='\0')
					{
						p=q;
						p--;//as p++ forloop
						break;
					}
				}
				i++;
			}//i argv[]from 0 to i-1
			cout<<i<<endl;

			for (int j=0;j<i;j++)
			{
				result=setup(input[j],argv);
				printf("execvp status%d\n",result);
			}
		}
	}
	return 0;
}
