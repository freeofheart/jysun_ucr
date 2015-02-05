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

#define print1(x) cout <<((x&S_IFDIR)?"d":"-")<< ((x&S_IRUSR)?"r":"-")<< ((x&S_IWUSR)?"w":"-")<< ((x&S_IXUSR)?"x":"-")\
<< ((x&S_IRGRP)?"r":"-")<< ((x&S_IWGRP)?"w":"-")<< ((x&S_IXGRP)?"x":"-")\
<< ((x&S_IROTH)?"r":"-")<< ((x&S_IWOTH)?"w":"-")<< ((x&S_IXOTH)?"x":"-")
#define print2(x) print1(x.st_mode)<<" "<<x.st_nlink<<" "
int lpreprint(struct stat s)
{
	print2(s);//permission
	struct passwd *passwd;
	passwd = getpwuid (s.st_uid);
	struct group *group;
	group = getgrgid (s.st_gid);
	printf("%s %s %lld\t",passwd->pw_name,group->gr_name, (long long)s.st_size);//user name, group name, size
	char *p=ctime(&s.st_mtime);//time
	for (int i=4;i<17;i++)
	{
		p[i-4]=p[i];
	}
	p[12]='\0';
	printf("%s ",p);
	return 0;
}

int lprint(char listname[])//print in "-l" format
{
	//char listname[]="ex1.cpp";
	struct stat s;
	if(stat(listname,&s)==0)
	{
		lpreprint(s);
		return 0;
	}
	else
	{
		perror("stat wrong!/n");
		exit(1);
	}
}

int P1Dir_al(char* listname)//a==1,l==1,R==0
{
	DIR *dirptr = NULL;
	struct dirent *entry;
	struct stat s;
	if(stat(listname,&s)!=0)
	{
		perror("stat goes wrong!\n");
		exit(1);
	}
	if(s.st_mode&S_IFDIR)
	{
		char tmp_listname[MAXLINE];
		long long sum=s.st_size;
		strcat(tmp_listname,listname);
		struct stat s1;
		for (int i=0; i<2;i++)
		{
			strcat(tmp_listname,".");
			if(stat(tmp_listname,&s1)!=0)
			{
				perror("stat goes wrong!\n");
				exit (1);
			}
			sum=sum+s1.st_size;
		}
		printf("total %lld\n",(long long)sum/1024);
	}
	if((dirptr = opendir(listname)) == NULL)//errot check
	{
		perror("open dir error !\n");
		exit (1);
	}
	else//normal display
	{
 
		while (entry = readdir(dirptr))//error check??
		{ 
			char newstr[MAXLINE];
			strcpy(newstr,"");
			strcat(newstr,listname);
			strcat(newstr,"/");
			strcat(newstr,entry->d_name);
			lprint(newstr);
			printf("%s\n",entry->d_name);
		}
		if(closedir(dirptr)!=0)
		{
			perror("closedir error!\n"); 
			exit(1);
		}//error check
	}
	return 0;
}

int P1Dir_l(char* listname)//a==0,l==1,R==0
{
	DIR *dirptr = NULL;
	struct dirent *entry;
	struct stat s;
	if(stat(listname,&s)!=0)
	{
		perror("stat goes wrong!\n");
		exit(1);
	}
	if(s.st_mode&S_IFDIR)
	{
		printf("total %lld\n",(long long)s.st_size/1024);
	}
	if((dirptr = opendir(listname)) == NULL)//errot check
	{
		perror("open dir error !\n");
		exit (1);
	}
	else//normal display
	{
 
		while (entry = readdir(dirptr))//error check??
		{ 
		 	if(entry->d_name[0]!='.')
			{
				char newstr[MAXLINE];
				strcpy(newstr,"");
				strcat(newstr,listname);
				strcat(newstr,"/");
				strcat(newstr,entry->d_name);
				lprint(newstr);
				printf("%s\n",entry->d_name);
			}
			else
			{
				continue;
			}
		}
		if(closedir(dirptr)!=0)
		{
			perror("closedir error!\n"); 
			exit(1);
		}//error check
	}
	return 0;
}

int P1Dir_a(char* listname)//a==1,l==0,R==0
{
	DIR *dirptr = NULL;
	struct dirent *entry;

	if((dirptr = opendir(listname)) == NULL)//errot check
	{
		perror("open dir error !\n");
		exit (1);
	}
	else//normal display
	{
 
		while (entry = readdir(dirptr))//error check??
		{ 
			printf("%s\t", entry->d_name);
		}
		printf("\n");
		if(closedir(dirptr)!=0)
		{
			perror("closedir error!\n"); 
			exit(1);
		}//error check
	}
	return 0;
}

int P1Dir(char* listname)//a==0,l==0,R==0
{
	DIR *dirptr = NULL;
	struct dirent *entry;

	if((dirptr = opendir(listname)) == NULL)//errot check
	{
		perror("open dir error !\n");
		exit (1);
	}
	else//normal display
	{
 
		while (entry = readdir(dirptr))//error check??
		{ 
		 	if(entry->d_name[0]!='.')
			{
				printf("%s\t", entry->d_name);
			}
			else
			{
				continue;
			}
		}
		printf("\n");
		if(closedir(dirptr)!=0)
		{
			perror("closedir error!\n"); 
			exit(1);
		}//error check
	}
	return 0;
}
	
int main(int argc,char** argv)
{
	allpt(argc,argv);
	
	int k=setaprt(argc,argv);//parameter=argv[k]~[argc-1], name list=argv[1]-argv[k-1]
	allpt(argc,argv);
	printf("%d list names\n",k);

	char *parameter[argc-k];//all the parameter
	for(int i=k;i<argc;i++)
	{
		parameter[i-k]=argv[i];
	}
	allpt(argc-k,parameter);	
	
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
		strcpy(argv[0],".");
		listname[0]=argv[0];
	}
	else
	{
		for(int i=0;i<k-1;i++)
		{
			listname[i]=argv[i+1];
		}
		k=k-1;
	}//k is the number of list names;

	if(R==0)
	{
		if(l==0)
		{
			if(a==1)
			{
				for (int i2=0;i2<k;i2++)
				{
					P1Dir_a(listname[i2]);
				}
				printf("\n");
			}
			else if(a==0)
			{
				for (int i2=0;i2<k;i2++)
				{
					P1Dir(listname[i2]);
				}
				printf("\n");
			}
			else//a!=1&&a!=0, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		else if(l==1)
		{	
			if(a==1)
			{
				for (int i2=0;i2<k;i2++)
				{
					P1Dir_al(listname[i2]);
				}
			}
			else if(a==0)
			{
				for (int i2=0;i2<k;i2++)
				{
					P1Dir_l(listname[i2]);
				}
			}
			else//a!=1&&a!=0, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		
	}

	//else if(R==0
	//PrintOneDirname(listname[0]);
	return 0;
}
