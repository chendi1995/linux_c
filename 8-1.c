/*************************************************************************
    > File Name: 8-1.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月24日 星期四 11时10分22秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *thread(void *arg)
{
	pthread_t newthid;
	newthid=pthread_self();
	printf("this is a new thread,thread ID=%u\n",newthid);
}
int main(void)
{
	pthread_t thid;
	printf("main thread,ID is %u\n",pthread_self());
	if(pthread_create(&thid,NULL,thread,NULL)!=0)
	{
		printf("thread creation failed\n");
		exit(1);
	}
	sleep(1);
	printf("%u",thid);
	exit(0);
	
}
