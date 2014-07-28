/*************************************************************************
    > File Name: diffork.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月21日 星期一 16时08分53秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int globvar=5;
int main(void)
{
	pid_t pid;
	int var=1,i;
	pid=fork();
	switch(pid)
	{
		case 0:
			i=3;
			while(i-->0)
			{
				printf("Child process is running\n");
				globvar++;
				var++;
				sleep(1);
			}
		printf("Child's globvar =%d,var=%d\n",globvar,var);
		break;
		case -1:
		perror("Process creation failed\n");
		break;
		default:
		i=5;
		while(i-->0)
		{
			printf("Parent process is running\n");
			globvar++;
			var++;
			sleep(1);
		}
		printf("Parent's globvar =%d,var=%d\n",globvar,var);
		
	}
}
