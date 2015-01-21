#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	char*buffer;
	if ((buffer=getcwd(NULL,0))==NULL)
		perror("_getcwderror");
	else
	{
		printf("%s\nLength:%lu\n",buffer,sizeof(buffer));
		free (buffer);
	}
	return 0;
}
