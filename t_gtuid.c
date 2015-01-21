#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

int main()
{
	uid_t uid;
	uid = getuid();
	printf("User IDs: uid=%d\n",uid);
	exit(0);
}
