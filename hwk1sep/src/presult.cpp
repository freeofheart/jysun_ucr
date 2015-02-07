#include "ls.h"
/*
int P1Dir_al(char listname0[])//a==1,l==1,R==0
{
	DIR *dirptr = NULL;
	struct dirent *entry;
	struct stat s;
	char listname[MAXLINE];	
	if(stat(listname0,&s)!=0)
	{
		perror("stat goes wrong!\n");
		exit(1);
	}
	if(s.st_mode&S_IFDIR)
	{	int j=strlen(listname0);//guarantee end with /
		for (int k=0;k<j;k++)
		{
			(listname[k])=(listname0[k]);
		}
		if(listname[j-1]!='/')
		{
			listname[j]='/';
			listname[j+1]='\0';
		}
		else
		{
			listname[j]='\0';
		}
	}
	else
	{
		strcpy(listname,listname0);
	}

	if(stat(listname,&s)!=0)
	{
		perror("stat goes wrong!\n");
		exit(1);
	}
	if(s.st_mode&S_IFDIR)
	{
		char tmp_listname[MAXLINE];
		long long sum=s.st_size;
		
		strcpy(tmp_listname,listname);
		struct stat s1;
		for (int i=0; i<2;i++)
		{
			strcat(tmp_listname,".");
			if(stat(tmp_listname,&s1)!=0)
			{
				perror("stat goes wrong!");
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
			memset(newstr,'\0',sizeof(newstr));
			strcat(newstr,listname);
			//strcat(newstr,"/");
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
}*/
#define Pfront 	DIR *dirptr = NULL;	struct dirent *entry;	struct stat s;\
	if(stat(listname,&s)!=0)\
	{\
		perror("stat goes wrong!\n");\
		exit(1);\
	}

int P1Dir_a(char* listname)//a==1,l==0,R==0
{
	/*DIR *dirptr = NULL;
	struct dirent *entry;
	struct stat s;
	if(stat(listname,&s)!=0)
	{
		perror("stat goes wrong!\n");
		exit(1);
	}*/
	Pfront
	if(s.st_mode&S_IFDIR)
	{
		if((dirptr = opendir(listname)) == NULL)//errot check
		{
			perror("open dir error !\n");
			exit (1);
		}
		else//normal display
		{
	 
			while ((entry = readdir(dirptr))==NULL)//error check??
			{ 
				printf("%s\t", entry->d_name);
			}			
			if(closedir(dirptr)!=0)
			{
				perror("closedir error!\n"); 
				exit(1);
			}//error check
		}
	}
	else
	{
		printf("%s\t",listname);
	}
	printf("\n");
	return 0;
}
/*
int P1Dir(char* listname)//a==0,l==0,R==0
{
	Pfront
	if(s.st_mode&S_IFDIR)
	{
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
			if(closedir(dirptr)!=0)
			{
				perror("closedir error!\n"); 
				exit(1);
			}//error check
		}
	}
	else
	{
		if(listname[0]!='.')
		{
			printf("%s\t",listname);
		}
	}
	printf("\n");
	return 0;
}*/
