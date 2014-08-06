/*************************************************************************
    > File Name: 11-2.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年08月01日 星期五 16时08分57秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<time.h>

void display_time(const char *string)
{
	int seconds;
	seconds=time((time_t *)NULL);
	printf("%s,%d\n",string,seconds);
}
int main(void)
{
	fd_set readfds;
	struct timeval timeout;
	int ret;
	FD_ZERO(&readfds);
	FD_SET(0,&readfds);

	while(1)
	{	
		timeout.tv_sec=10;
		timeout.tv_usec=0;

		display_time("before select");
		ret=select(1,&readfds,NULL,NULL,&timeout);
		display_time("after select");
		switch(ret)
		{
			case 0:printf("there are no data!\n");
				   exit(1);
				   break;
			case -1:perror("select");
					exit(1);
					break;
			default:getchar();
					printf("Data is available now.\n");

		}
	}
	return 0;
}
