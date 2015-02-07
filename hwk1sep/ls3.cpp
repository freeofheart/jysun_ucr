#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#define MAXLINE 2048

using namespace std;

int setaprt(int argc,char**argv)//need to work to separate name list and parameters: put them in the order:name in the front, p in the rear; use last position to store name numbers.
{
	int i=0,j=0;
	char *p;
	while(i<argc-j)
	{
		if(argv[i][0]=='-')//initiate with'-'
		{
			while(argv[argc-1-j][0]=='-'&&(argc-1-j)>i)//find the last one not initiate with'-'
			{
				j++;
			}
			if((argc-1-j)<=i)//all initiate without '-'
			{
				break;
			}
			p=argv[i];//swap
			argv[i]=argv[argc-1-j];
			argv[argc-1-j]=p;
			j++;
		}
		i++;
	}
	return i;//i listnames
}

void allpt(int argc,char **argv)
{
	printf("%d in total\n",argc);//show the input
	for(int i=0;i<argc;i++)
	{
		printf("[%d]= %s\n",i,argv[i]);

	}
}
int sp_dir(int argc,char**argv)//need to work to separate dir list and documents: put them in the order:documents in the front, dirs in the rear; use return valve to document number. dit at least 1
{
	int i=0,j=0;
	char *p;
	while(i<argc-j)
	{
		struct stat s;
		if(stat(argv[i],&s)!=0)//error check
		{
			perror("stat error in sp_dir");
			exit(1);
		}
		if(s.st_mode&S_IFDIR)//dir
		{
			struct stat s1;
			if (stat(argv[argc-1-j],&s1)!=0)
			{
				perror("stat error in sp_dir2");
			}
			while((s1.st_mode&S_IFDIR)&&(argc-1-j)>i)//find the last one not dir
			{
				j++;
				if (stat(argv[argc-1-j],&s1)!=0)
				{
					perror("stat error in sp_dir2");
				}
			}
			if((argc-1-j)<=i)//all are dir
			{
				break;
			}
			p=argv[i];//swap
			argv[i]=argv[argc-1-j];
			argv[argc-1-j]=p;
			j++;
		}
		i++;
	}
	return i;//i documents
}

	
int main(int argc,char** argv)
{
	
	
	int k=setaprt(argc,argv);//parameter=argv[k]~[argc-1], name list=argv[1]-argv[k-1]
	
	char *parameter[argc-k];//all the parameter
	for(int i=k;i<argc;i++)
	{
		parameter[i-k]=argv[i];
	}
	
	
	int a=0,l=0,R=0;//mark if there exists a "-a", "-l" or "-R"
	for (int i1=0;i1<argc-k;i1++ )
	{
		int j=1;
		while(parameter[i1][j]!='\0')
		{
			if(parameter[i1][j]=='a')
			{
				a=1;
			}
			if(parameter[i1][j]=='l')
			{
				l=1;
			}
			if(parameter[i1][j]=='R')
			{
				R=1;
			}
			j++;
		}
	}
	//printf("whether it is -a: %d\n",a);

	char *listname[k];//all the listname
	if(k<=1)//no list name, it should be the current
	{
		char buf[MAXLINE];
		//strcpy(argv[0],".");
		listname[0]=getcwd(buf,MAXLINE);
	}
	else
	{
		for(int i=0;i<k-1;i++)
		{
			listname[i]=argv[i+1];
		}
		k=k-1;
	}//k is the number of list names;
	printf("listname: ");
	allpt(k,listname);

	int n1=sp_dir(k,listname);
	char *doc_name[n1];
	for(int i=0;i<n1;i++)
	{
		doc_name[i]=listname[i];
	}
	printf("document name: ");
	allpt(n1, doc_name);

	char *dir_name[k-n1];//all the parameter
	for(int i=n1;i<k;i++)
	{
		dir_name[i-n1]=listname[i];
	}
	printf("directory name: ");
	allpt(k-n1,dir_name);


	return 0;
}
