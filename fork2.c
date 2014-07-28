/*************************************************************************
    > File Name: fork2.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月21日 星期一 15时33分06秒
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
	char *msg;
	int k;
	pid=fork();
	switch(pid)
	{
		case 0:msg="Child";
			   k=5;
			   break;
		case -1:msg="failed\n";
				break;
		default:msg="Parents";
				k=6;
	
				break;
	}

	while(k>0)
	{
		printf("%s\n",msg);
		sleep(1);
		k--;
	}
	return 0;
}
