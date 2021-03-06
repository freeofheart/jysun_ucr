#include "ls.h"	
	
int main(int argc,char** argv)
{
	
	
	int k=setaprt(argc,argv);//parameter=argv[k]~[argc-1], name list=argv[1]-argv[k-1]
	
	char *parameter[MAXNUM];//[argc-k]all the parameter
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

	char *listname[MAXNUM];//[k]all the listname
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


	const int n1=sp_dir(k,listname);
	char *doc_name[MAXNUM];//n1 documents
	for(int i=0;i<n1;i++)
	{
		doc_name[i]=listname[i];
	}
	printf("document name: ");
	allpt(n1, doc_name);

	char *dir_name[MAXNUM];//[k-n1]all the parameter
	for(int i=n1;i<k;i++)
	{
		dir_name[i-n1]=listname[i];
	}
	printf("directory name: ");
	allpt(k-n1,dir_name);

	if(R==0)
	{
		if(l==0)
		{
			if(a==1)
			{
				sort(doc_name,doc_name+n1,compare);
				allpt(n1,doc_name);
				for (int i2=0;i2<n1;i2++)	
				{
						printf("%s\t",doc_name[i2]);
				}
				if(n1)//end of doc
				{
					printf("\n");//all doc display finishes
				}

				
				sort(dir_name,dir_name+k-n1,compare);
				allpt(k-n1,dir_name);
				for (int i2=0;i2<k-n1;i2++)
				{
					//P1Dir_a(listname[i2]);
					DIR *dirptr = NULL;
					struct dirent *entry;
					struct stat s;	
					char *sort_dir[MAXNUM];

					if(stat(dir_name[i2],&s)!=0)
					{
						perror("stat goes wrong!\n");
						exit(1);
					}
					
					if((dirptr = opendir(dir_name[i2])) == NULL)//errot check
					{
						perror("open dir error !\n");
						exit (1);
					}
					else//normal display
					{
						int i3=0;
						while ((entry = readdir(dirptr))!=NULL)//error check??
						{								
							sort_dir[i3]=entry->d_name;
							i3++;
							//printf("%s\t", entry->d_name);
						}
						if((i3)&&(n1))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
						}
						if(k>=2)
						{
							printf("%s:\n",dir_name[i2]);
						}
						sort(sort_dir,sort_dir+i3,compare);
						for(int i4=0;i4<i3;i4++)
						{
							printf("%s\t",sort_dir[i4]);
						}
						if(i2<k-n1-1)
						{
							printf("\n\n");
						}
						else
						{
							printf("\n");
						}
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				}				
			}
			else if(a==0)
			{sort(doc_name,doc_name+n1,compare);
				allpt(n1,doc_name);
				int if_doc=0;//if doc is display
				for (int i2=0;i2<n1;i2++)	
				{
					if(doc_name[i2][0]!='.')
					{
						printf("%s\t", doc_name[i2]);
						if_doc++;
					}
					else
					{
						continue;
					}
				}

				if(if_doc)//end of doc
				{
					printf("\n");//all doc display finishes
				}

				

				sort(dir_name,dir_name+k-n1,compare);
				allpt(k-n1,dir_name);
				for (int i2=0;i2<k-n1;i2++)
				{
					//P1Dir_a(listname[i2]);
					DIR *dirptr = NULL;
					struct dirent *entry;
					struct stat s;	
					char *sort_dir[MAXNUM];

					if(stat(dir_name[i2],&s)!=0)
					{
						perror("stat goes wrong!\n");
						exit(1);
					}
					
					if((dirptr = opendir(dir_name[i2])) == NULL)//errot check
					{
						perror("open dir error !\n");
						exit (1);
					}
					else//normal display
					{
						int i3=0;
						while ((entry = readdir(dirptr))!=NULL)//error check??
						{								
							if(entry->d_name[0]!='.')
							{
								sort_dir[i3]=entry->d_name;
								i3++;
							}							
							//printf("%s\t", entry->d_name);
						}
						sort(sort_dir,sort_dir+i3,compare);

						if((i3)&&(if_doc))//newline between dor and dir
						{
							printf("\n");//all doc display finishes
						}
						if(k>=2)
						{
							printf("%s:\n",dir_name[i2]);
						}
						for(int i4=0;i4<i3;i4++)
						{
							printf("%s\t",sort_dir[i4]);
						}
						if(i2<k-n1-1)
						{
							printf("\n\n");
						}
						else
						{
							printf("\n");
						}
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				/*sort(doc_name,doc_name+n1,compare);
				allpt(n1,doc_name);
				int if_doc=0;//if any documents are displayed
				for (int i2=0;i2<n1;i2++)	
				{
					if(doc_name[i2]!='.')
					{
						printf("%s\t", doc_name[i2]);
						if_doc++;
					}
					else
					{
						continue;
					}
					printf("%s\t",listname[i2]);
				}
				if(if_doc)
				{
					printf("\n\n");//all doc display finishes
				}

				sort(dir_name,dir_name+k-n1,compare);
				allpt(k-n1,dir_name);
				for (int i2=0;i2<k-n1;i2++)
				{
					//P1Dir_a(listname[i2]);
					DIR *dirptr = NULL;
					struct dirent *entry;
					struct stat s;	
					char *sort_dir[MAXNUM];

					if(stat(dir_name[i2],&s)!=0)
					{
						perror("stat goes wrong!\n");
						exit(1);
					}
					if(k>=2)
					{
						printf("%s:\n",dir_name[i2]);
					}
					if((dirptr = opendir(dir_name[i2])) == NULL)//errot check
					{
						perror("open dir error !\n");
						exit (1);
					}
					else//normal display
					{
						int i3=0;
						while ((entry = readdir(dirptr))!=NULL)//error check??
						{								
							sort_dir[i3]=entry->d_name;
							i3++;
							//printf("%s\t", entry->d_name);
						}
						sort(sort_dir,sort_dir+i3,compare);
						for(int i4=0;i4<i3;i4++)
						{
							printf("%s\t",sort_dir[i4]);
						}
						if(i2<k-n1-1)
						{
							printf("\n\n");
						}
						else
						{
							printf("\n");
						}
						if(closedir(dirptr)!=0)
						{
							perror("closedir error!\n"); 
							exit(1);
						}//error check
					}
				for (int i2=0;i2<k;i2++)
				{
					P1Dir(listname[i2]);
				}*/
					
				}
			}
			else//a!=1&&a!=0, should not exist
			{
				printf("-a error!\n");
				exit(1);
			}
		}
		/*else if(l==1)
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
		}*/
		
	}
	//printf("\n");
	//else if(R==0
	//PrintOneDirname(listname[0]);
	return 0;
}
