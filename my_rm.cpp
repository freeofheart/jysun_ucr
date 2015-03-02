#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define MAXNUM 100
using namespace std;

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
int rm(int argc ,char *listname[MAXNUM], int r)
{
        int k=argc;
        const int n1=sp_dir(k,listname);
        char *doc_name[MAXNUM];//n1 documents
        for(int i=0;i<n1;i++)
        {
                doc_name[i]=listname[i];
        }
        //printf("document name: ");
        //allpt(n1, doc_name);
        char *dir_name[MAXNUM];//[k-n1]all the parameter
        for(int i=n1;i<k;i++)
        {
                dir_name[i-n1]=listname[i];
        }
        ////printf("directory name: ");
        //allpt(k-n1,dir_name)
        for(int i=0;i<n1;i++)
        {
                if(unlink(doc_name[i])==-1)
                {
                        perror("unlink error!");
                        exit (1);
                }
        }
        if(r==1)
        {
                for(int i=1;i<k-n1;i++)
                {
                        DIR *dirptr = NULL;
                        struct dirent *entry;
                        struct stat s;
                        char *sort_dir[MAXNUM];
                        if(stat(dir_name[i],&s)!=0)
                        {
                                perror("stat dir goes wrong!\n");
                                exit(1);
                        }
                        if((dirptr = opendir(dir_name[i])) == NULL)//errot check
                        {
                                perror("open dir error !\n");
                                exit (1);
                        }
                        else//normal display
                        {
                                int i1=0;
                                char listname0[MAXNUM][MAXNUM];
                                char *listname0_ptr[MAXNUM];
                                while ((entry = readdir(dirptr))!=NULL)//error check??
                                {
                                        strcpy(listname[i1],entry->d_name);
                                        listname0_ptr[i1]=listname0[i1];
                                        i1++;
                                }
                                rm(k-n1,listname0_ptr,r);
                        }
                }
        }
        return 0;
}
int main(int argc ,char **argv)
{
        int r=0;
        int i0;
        for(int i=0;i<argc;i++)
        {
                if(strcmp(argv[i],"-r")==0)
                {
                    r=1;
                }
                else
                {
                        argv[i0]=argv[i];
                        i0++;
                }
        }
        int k=i0;
        const int n1=sp_dir(k,argv);
        char *doc_name[MAXNUM];//n1 documents
        for(int i=0;i<n1;i++)
        {
                doc_name[i]=argv[i];
        }
        //printf("document name: ");
        //allpt(n1, doc_name);
        char *dir_name[MAXNUM];//[k-n1]all the parameter
        for(int i=n1;i<k;i++)
        {
                dir_name[i-n1]=argv[i];
        }
        ////printf("directory name: ");
        //allpt(k-n1,dir_name)
        for(int i=0;i<n1;i++)
        {
                if(unlink(doc_name[i])==-1)
                {
                        perror("unlink error!");
                        exit (1);
                }
        }
        if(r==1)
        {
                for(int i=1;i<k-n1;i++)
                {
                        DIR *dirptr = NULL;
                        struct dirent *entry;
                        struct stat s;
                        char *sort_dir[MAXNUM];
                        if(stat(dir_name[i],&s)!=0)
                        {
                                perror("stat dir goes wrong!\n");
                                exit(1);
                        }
                        if((dirptr = opendir(dir_name[i])) == NULL)//errot check
                        {
                                perror("open dir error !\n");
                                exit (1);
                        }
                        else//normal display
                        {
                                int i1=0;
                                char listname[MAXNUM][MAXNUM];
                                while ((entry = readdir(dirptr))!=NULL)//error check??
                                {
                                        listname[i1]=entry->d_name;
                                        i1++;
                                }
                                rm(k-n1,listname,r);
                        }
                }
        }
        return 0;
}


