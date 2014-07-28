/*************************************************************************
    > File Name: env.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月21日 星期一 20时15分39秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
extern char **environ;

int main(int argc,char * argv[])
{
	int i;
	printf("Environment:\n");
	for(i=0;environ[i]!=NULL;i++)
		printf("%s\n",environ[i]);
	return 0;
}
