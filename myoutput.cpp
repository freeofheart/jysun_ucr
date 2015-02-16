#include <iostream>
#include <stdio.h>
#include <stdlib.h>
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

int copen1(int argc,char **argv)
{
	int file2=open(argv[2],O_WRONLY|O_CREAT);
	if(file2<0)
	{
		perror("open file2 error");
		exit(1);
	}
	int file1=open(argv[1],O_RDONLY);
	if(file1<0)
	{
		perror("open file1  error");
		exit(1);
	}
	char str[MAXLINE];
	ssize_t readsize=read(file1,str,1);
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	while(readsize)
	{
		if(-1==write(file2,str,1))
		{
			perror("write error!");
			exit(1);
		}
		readsize=read(file1,str,1);
	}
	if(readsize<0)
	{
		perror("read error!");
		exit(1);
	}
	if(close(file1)<0)
	{
		perror("close 1 error");
		exit(1);
	}	
	if(close(file2)<0)
	{
		perror("close 2 error");
		exit(1);
	}
	return 0;
}

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
	//cppio(argc,argv);
	copen1(argc,argv);
	return 0;
}
