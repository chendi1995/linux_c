/*************************************************************************
    > File Name: 8-3.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月29日 星期二 15时22分56秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void assisthread(void *arg)
{
	printf("assisthread!\n");
}
int main(void)
{
	pthread_t assistthid;
	int status;
	printf("mainthread!\n");
	pthread_create(&assistthid,NULL,assisthread,NULL);
	//pthread_join(assistthid,&status);
	//printf("assistthid is %d\n",status);
	printf("mainthread!\n");
	sleep(1);
	return 0;
}
