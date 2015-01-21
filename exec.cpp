#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char **argv)
{
	for (int i=0;i<argc;i++)
	{
		cout<<"argv["<<i<<"]="<<argv[i]<<endl;
	}
	const char *cmd="ls";
	int pid=fork();
	if(pid==-1)
	{
		perror("fork fail");
	}
	else if(pid==0)
	{
		printf("This is in the child process%d\n",getpid());
		printf("cmd%s\n",cmd);
		for (int j=0;j<argc;j++)
			printf("argv%s\n",argv[j]);
		sleep(2);
		if (execvp(cmd,argv)!=0)
		{
			perror("error in execvp");
		}
	}
	else
	{	
		if(-1==wait(0))
			perror("There was an error with wait().");
		cerr<<"Will this print?"<<endl;
	}
	return 0;
}
