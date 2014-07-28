/*************************************************************************
    > File Name: fork.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月21日 星期一 10时47分28秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(void)
{
	pid_t pid;
	pid=fork();
	switch(pid)
	{
		case 0:printf("Child,Childpid is %d,Parentpid is %d\n%d\n",pid,getppid(),getpid());break;
		case -1:printf("faild");break;
		default:printf("Parent,Childpid is %d,Parentpid is %d\n%d\n",pid,getpid(),getppid());break;
		
	}
}
