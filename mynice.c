/*************************************************************************
    > File Name: mynice.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月23日 星期三 17时06分28秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void)
{
	pid_t pid;
	int stat_val=0;
	int oldpri,newpri;
	printf("nice study\n");
	pid=fork();
	switch(pid)
	{
		case 0:
			printf("Child is running,CurPid is %d,ParentPid is %d\n",pid,getppid());
			oldpri=getpriority(PRIO_PROCESS,0);
			printf("Old priority=%d\n",oldpri);
			newpri=nice(2);
			printf("New priority =%d\n",newpri);
			exit(0);
		case -1:
			perror("Process creation failed\n");
			break;
		default:
			printf("Parent is running,ChildPid is %d,ParentPid is %d\n",pid,getpid());
			break;
	}
	wait(&stat_val);
	exit(0);

}
