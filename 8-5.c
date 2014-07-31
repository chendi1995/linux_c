/*************************************************************************
    > File Name: 8-5.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月30日 星期三 16时00分46秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t cond;

void * thread1(void *arg)
{            
	pthread_cleanup_push(pthread_mutex_unlock,&mutex);
	while(1)
	{
		printf("thread1 is runnning!\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("thread1 applied the condition\n");
		pthread_mutex_unlock(&mutex);
		sleep(4);
	}
	pthread_cleanup_pop(0);
}
void * thread2(void *arg)
{            
	while(1)
	{
		printf("thread2 is runnning!\n");
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond,&mutex);
		printf("thread2 applied the condition\n");
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main(void)
{
	pthread_t tid1,tid2;
	printf("condition variable study!\n");
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);
	pthread_create(&tid1,NULL,(void *)thread1,NULL);
	pthread_create(&tid2,NULL,(void *)thread2,NULL);
	do
	{
		pthread_cond_signal(&cond);

	}while(1);
	sleep(50);
	pthread_exit(0);
}
