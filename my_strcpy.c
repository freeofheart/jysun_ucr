/* strcpy example */
#include <stdio.h>
#include <string.h>

void  my_strcpy(char * dst, char *src)
{
	int i=0;
	while (src[i]!='\0')
	{
		dst[i]=src[i];
		i++;
	}
	dst[i]=src[i];
}

void  my_strncpy(char * dst, char *src,int n)
{
	int i=0;
	while (src[i]!='\0'&&i<n)
	{
		dst[i]=src[i];
		i++;
	}
	dst[i]='\0';
}
void my_strcat(char* dst, char*src)
{
	char *p;
	int i=0;
	while (dst[i]!='\0')
	{
		i++;
	}
	int j=0;
	while (src[j]!='\0')
	{
		dst[i++]=src[j++];
	}
	dst[i]='\0';
}
void my_strncat(char* dst, char*src,int n)
{
	char *p;
	int i=0;
	while (dst[i]!='\0')
	{
		i++;
	}
	int j=0;
	while (src[j]!='\0'&&j<n)
	{
		dst[i++]=src[j++];
	}
	dst[i]='\0';
}
int my_strcmp(char *dst,char* src)
{
	int i=0;
	int j=0;
	do
	{
		if(dst[i]<src[i])
		{
			j= -1 ;
			break;
	       	}
		else if (dst[i]>src[i])
		{
			j= 1;
			break;
		}
		i++;
	}while(dst[i]!='\0');
}

char*my_strchr(char*s,char c)
{
	while(*s!='\0'&& *s!=c)
	{
		++s;
	}
	return *s==c?s:NULL;
}
char * my_strstr(char*s,char*c)
{
	int i=0,j=0;
	while (s[i]!='\0')
	{
		while(s[i]!=c[j])
		{
			i++;
		}
		while(c[j]!='\0'&&s[i+j]==c[j])
		{
			j++;
		}
		if (c[j]=='\0')
		{
			return &s[i];
		}
		i=i+1;
	}
	return NULL;
}
int my_strlen(char*s)
{
	int i=0;
	while(*s!='\0')
	{
		i++;
		s++;
	}
	return i;
}

int main ()
{
  char str1[]="Sample string";
  char str2[40];
  char str3[40];
  char str4[40];
  char str5[40];
  strcpy (str2,str1);
  my_strcpy(str3,str1);
  my_strncpy(str4,str1,3);

 // my_strcpy (str3,"copy successful");
  printf ("str1: %s\nstr2: %s\nstr3: %s\nstr4: %s\n",str1,str2,str3,str4);
  printf("strcpy, strncpy done\n");
  strcat(str2,"cat");
  my_strcat(str3,"cat");
  my_strncat(str4,"cat",2);
  printf("str2: %s\nstr3: %s\nstr4 : %s\n",str2,str3,str4);		  
  printf("strcat, strncat done\n");

  int j=my_strcmp(str1,"Sample string");
  printf("strcmp,%d\nmy_strcmp, %d\n",strcmp(str1,"Sample string"),j);
  printf("strcmp ,done\n");
	
  char *k=strchr(str1,'m');
  char *l=my_strchr(str1,'m');
  printf("strchr(str1,'m'): %d\nmy_strchr(str1,'m') %d\n",k-str1+1,l-str1+1);
  printf("my_strchr() done\n");

  char str6[]="zple ";
  k=strstr(str1,str6);
  l=my_strstr(str1,str6);
  printf("strstr(str1,str6), %s\nmy_strstr %s\n",k,l);
  printf("mystrstr done\n");

  j=strlen(str1);
  int i=my_strlen(str1);
  printf("strlen(str1): %d\nmy_strlen(str1) %d\n",j,i);
  printf("mystrlen done\n");
  return 0;
}
