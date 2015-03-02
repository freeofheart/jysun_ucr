#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char **argv)
{
        if(argc!=3)
        {
                printf("you could only pass exact 3 arguments!\n");
                return 1;
        }
        struct stat s;
        if(stat(argv[2],&s)==-1)
        {
                perror("stat error!");
                exit(1);
        }
        if(s.st_mode&S_IFDIR)
        {
                /*struct dirent *entry;
                DIR *dirptr=NULL;
                if((dirptr=opendir(argv[2]))==NULL)
                {
                        perror("open dir error!");
                        exit(1);
                }*/
                char tmp[100];
                strcpy(tmp,argv[2]);
                strcat(tmp,argv[1]);
                if(link(argv[1],tmp))
                {
                        perror("link error");
                        exit(1);
                }
                if(unlink(argv[1]))
                {
                        perror("unlink error");
                        exit(1);
                }
        }
        else
        {
                if(link(argv[1],argv[2]))
                {
                        perror("link error");
                        exit(1);
                }
                if(unlink(argv[1]))
                {
                        perror("unlink error");
                        exit(1);
                }
        }
        return 0;
}
