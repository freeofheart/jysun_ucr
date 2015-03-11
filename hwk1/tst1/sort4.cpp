#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;
#define MAXLINE 2048
#define MAXNUM 256
#define NUM 400
bool cmp_dot(char a[], char b[])
{
	if (strlen(a)<strlen(b))
	{
		return false;
	}
	else
	{
		return true;
	}	
}

bool if_all_dot(char a[])
{
	int j=strlen(a);
	for(int l=0;l<j;l++)
	{
		if(a[l]!='.')return false;
	}
	return true;
}
	
char* convert(char a[])//remain only a~z and 0~9
{
	char*q;
	int j=strlen(a);
	int flag=0;
	for(int l=0;l<j;l++)
	{
		if(a[l]!='.')flag=1;
	}
	
	if(flag==1)
	{
		int i=0;
		int k=0;
		while(k<j)
		{
		
			while((a[k]<'0'||(a[k]>'9'&&a[k]<'A')||(a[k]>'Z'&&a[k]<'a')||a[k]>'z')&&k<j)
			{
				k++;
			}
			while((a[k]>='A'&&a[k]<='Z')&&k<j)
			{
				a[i]=a[k]+'a'-'A';
				k++;
				i++;
			}
			while(((a[k]>='a'&&a[k]<='z')||(a[k]>='0'&&a[k]<='9'))&&k<j)
			{
				a[i]=a[k];
				k++;
				i++;
			}
		}
		a[i]='\0';
	}
	q=&a[0];
	return q;
}

bool compare(char *p1,char *p2)//sort alphabetically
{
	//if(strcmp(p1,'\0')==0){return true;}
	//if(strcmp(p2,'\0')==0){return false;}
	
	char q1[MAXLINE];
	char q2[MAXLINE];
	strcpy(q1,p1);
	strcpy(q2,p2);
	if( (if_all_dot(p1) )&&( if_all_dot(p2) ) )
	{
		return cmp_dot(p1,p2);
	}
	char *q3;
	if (if_all_dot(q1)) return false;	
	q3=convert(q1);

	
	char *q4;
	if(if_all_dot(q2)) return true;
	q4=convert(q2);

	if (strcmp(q3,q4)<0) return false;
	else return true;
}

void mysort(char *list[], int num)
{
	char *tmp;
	for( int j=0;j<num;j++)
	{
		for(int i=0;i<num-j-1;i++)
		{
			if(compare(list[i],list[i+1]))
			{
				tmp=list[i];
				list[i]=list[i+1];
				list[i+1]=tmp;	
			}
		}
	}
}


int main()
{
	char p[100][100];
	strcpy(p[3],"ga");//"Ho1_A2";//][-0re(yOu)";
	strcpy(p[1],"ap1");
	strcpy(p[2],"_ap1");
	strcpy(p[0],"_ga");
	char *q[100];
	/*q=(char**)malloc(NUM*sizeof(char*));
	for (int i=0;i<NUM;i++)
	{
		q[i]=(char*)malloc(MAXNUM*sizeof(char));
	}*/
	q[1]=p[1];
	printf("%s\n",q[1]);
	q[2]=(p[2]);
	printf("%s\n",q[2]);
	q[0]=(p[0]);
	q[3]=p[3];
	//mysort(q,4);
	//printf("q: %s %s %s %s\n",q[0],q[1],q[2],q[3]);
	sort(q,q+4,compare);
	printf("q: %s %s %s %s\n",q[0],q[1],q[2],q[3]);
	
	/*for(int i=0;i<NUM;i++)
	{
		free(q[i] );
	}0
	free (q);*/
	//delete[]q;
	return 0;
}
