/*************************************************************************
    > File Name: studyuid.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月23日 星期三 15时27分50秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

extern int errno;
int main()
{
	int fd;
	printf("uid study:\n ");
	printf("Process's uid =%d,euid=%d\n",getuid(),geteuid());
	if((fd=open("test.c",O_RDWR))==-1)
	{
		printf("Open failure ,errno is %d:%s\n",errno,strerror(errno));
		exit(1);
	}
	else
	{
		printf("Open successfully!\n");
	}
	close(fd);
	exit(0);
}
