#include <iostream>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#define MAXLINE 256
using namespace std;

int cppio(int argc, char **argv)
{
	std::ofstream outfile (argv[2]);
	char ch;
	char str[MAXLINE];
	int value;

	std::ifstream is(argv[1]);
	char c;
	while(is.get(c))
	{
		ch=c;
		outfile.put(ch);

	}
	is.close();
    return 0;
}

int copen(int argc,char **argv)
{
    int file=open(argv[2],O_WRONLY|O_APPEND);
    if(file<0)
    {
        perror("open %s error",argv[2]);
        exit(1);
    }
    char str[MAXLINE];
    int readsize==read(argv[1],str,1);
    if(readsize<0)
    {
        perror("read %s error!",argv[1]);
        exit(1);
    }
    while(readsize)
    {
        write(argv[2],str,1);
        read(arg
    }
    if(readsize<0)
    {
        perror("read %s error!", argv[1]);
        exit(1);
    }
    if(close(file)<0)
    {
        perror("close %s error",argv[2]);
int main(int argc,char**argv)
{
	if(argc>4||argc<3)
	{
		std::cout<<"Wrong number input!"<<std::endl;
		return 1;
	}

	std::ifstream f(argv[2]);
	if (f.good()) {
		std::cout<<"file exits!"<<std::endl;
	       f.close();
	       return 1;
	} else {
	       f.close();
	}
    cppio(argc,argv);

	return 0;
}

