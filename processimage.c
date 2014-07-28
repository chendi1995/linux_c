/*************************************************************************
    > File Name: processimage.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月22日 星期二 17时04分35秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[],char ** environ)
{
	int i;
	printf("I am a process image!\n");
	printf("My pid =%d,parentpid=%d\n",getpid(),getppid());
	printf("uid=%d,gid=%d\n",getuid(),getgid());
	for(i=0;i<argc;i++)
		printf("argv[%d]:%s\n",i,argv[i]);

}

