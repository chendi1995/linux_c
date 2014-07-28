/*************************************************************************
    > File Name: wait.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月23日 星期三 11时30分01秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	pid_t pid;
	char *msg;
	int k;
	int exit_code;

	printf("Study how to get exit code\n");
	pid=fork();
	switch(pid)
	{
		case 0:msg="Child process is running";
			   k=5;
			   exit_code=37;
			   break;
		case -1:
			   perror("Process creation failed\n");
			   exit(1);
		default:
			   exit_code=0;
			   break;
	}
	if(pid!=0)
	{
		int stat_val;
		pid_t child_pid;
		child_pid=wait(&stat_val);
		printf("Child process has exited,pid =%d\n",child_pid);
		if(WIFEXITED(stat_val))
			printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
		else
			printf("Child exited abnormally\n");
	}

	else
		while(k-->0)
		{
			puts(msg);
			sleep(1);
		}
	exit(exit_code);
}
