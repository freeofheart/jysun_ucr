#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <iostream>
#include <stdlib.h>
#define MAXLINE 80
using namespace std;

int and_or(char* inputBuffer);

int setup(char inputBuffer[])
{
	int i,j;
	char *argv[MAXLINE/2-1];
	char *p;//=(char*)malloc(MAXLINE*sizeof(char));
	i=0;
	for (p=inputBuffer; ;p++)
	{
		while(*p==' '||*p=='\t')
		{
			p++;
		}
		if(*p=='\0')
			break;
		//argv[i]=(char*)malloc((MAXLINE/2-1)*sizeof(char));
		argv[i++]=p;
		while (*p!=' '&&*p!='\0'&&*p!='\t')
			p++;
		if(*p=='\0')
			break;
		*p='\0';
		p++;
		while(*p==' '||*p=='\t')
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

int smcln(char inputBuffer[])
{
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int i=0;
	for (p=inputBuffer; ;p++)
	{
		if(*p=='\0')
		{
			break;
		}
		// not malloc(MAXLINE*sizeof(char));
		input[i]=p;
		char*q;//not malloc(MAXLINE*sizeof(char));
		for(q=p;;q++)
		{
			if(*q!=';'&&*q!='\0'&&*q!='#')
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
				p--;//as p++ forloop, guarantee exit
				break;
			}
			else if(*q=='#')
			{
				*q='\0';
				p=q;
				p--;
				break;//as p++ forloop, guarantee exit
			}
		}
		i++;
	}//i argv[]from 0 to i-1
	printf("%d segements by semicolon\n",i);
	int result;
	for (int j=0;j<i;j++)
	{
		and_or(input[j]);
	}
	return 0;
}

int and_or(char* inputBuffer)
{
	char *p;//not malloc(MAXLINE*sizeof(char));
	char *input[MAXLINE];
	int i=0;
	char flag[MAXLINE/2];
	for (p=inputBuffer; ;p++)
	{
		if(*p=='\0')
		{
			break;
		}
		// not malloc(MAXLINE*sizeof(char));
		input[i]=p;
		char*q;//not malloc(MAXLINE*sizeof(char));
		for(q=p;;q++)
		{
			if(*q!='&'&&*q!='\0'&&*q!='|')
			{
				continue;
			}
			else if(*q=='&')
			{
				if(*(++q)=='&')
				{
					flag[i]=0;
					*q=' ';
					*(--q)='\0';
					p=q;
					break;
				}
				else
				{
					flag[i];
					--q;
					*q='\0';
					p=q;
					break;
				}
			}
			else if(*q=='|')
			{
				if(*(++q)=='|')
				{
					flag[i]=1;
					*q=' ';
					*(--q)='\0';
					p=q;
					break;
				}
				else
				{
					flag[i];
					--q;
					*q='\0';
					p=q;
					break;
				}
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
	printf("%d segements ands\n",i) ;
	int result;
	int mark=0;//true, need to continue
	for (int j=0;(j<i)&&(mark==0);j++)
	{
		result=setup(input[j]);
		if (flag[j]==0)
		{
			mark=result+mark;
		}
		else if(flag[j]==1)
		{
			mark=(result==0);
		}
		printf("execvp status%d\n",result);
	}
	return 0;
}

int main()
{
	char inputBuffer[MAXLINE];

	while (1)
	{
		printf ("COMMAND->");
		cin.getline(inputBuffer,MAXLINE);
		int result;
		if ((strcmp(inputBuffer, "exit") == 0))
		{
			exit(1);
		}
		else
		{
			smcln(inputBuffer);
		}
	}
	return 0;
}
