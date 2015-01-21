#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

const int max_name_len=256;
const int max_path_len=1024;

void type_prompt(char *prompt)
{
	extern struct passwd *pwd;
	char hostname[max_name_len];
	char pathname[max_path_len];
	int length;
	pwd = getpwuid(getuid());
	getcwd(pathname,max_path_len);
	if(gethostname(hostname,max_name_len)==0)
		sprintf(prompt,"[rshell]%s@%s:",pwd->pw_name,hostname);
	else
		sprintf(prompt,"[rshell]%s@unkown:",pwd->

