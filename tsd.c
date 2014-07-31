/*************************************************************************
    > File Name: tsd.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月29日 星期二 19时01分23秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

pthread_key_t key;
void * thread2(void *arg)
{
	int tsd=5;
	printf("thread %d is running\n",pthread_self());
	pthread_setspecific(key,tsd);
	printf("thread %d returns %d\n",pthread_self(),pthread_getspecific(key));
}

void * thread1(void *arg)
{
	int tsd=0;
	pthread_t thid2;
	printf("thread %d is running\n",pthread_self());
	pthread_setspecific(key,tsd);
	pthread_create(&thid2,NULL,thread2,NULL);
	sleep(5);
	printf("thread %d returns %d\n",pthread_self(),pthread_getspecific(key));
}

int main(void)
{
	pthread_t thid1;
	printf("main thread begins runnning\n");
	pthread_key_create(&key,NULL);
	pthread_create(&thid1,NULL,thread1,NULL);
	sleep(6);
	pthread_key_delete(key);
	printf("main thread exit!\n");
	return 0;
}
