/*************************************************************************
    > File Name: error.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月28日 星期一 14时47分38秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int i;
	for(i=0;i<128;i++)
	{
		errno=i;
		printf("%d\n",errno);
		perror("");
	}
	for(i=0;i<128;i++)
	{
		printf("%d\n",errno);
		perror("");
	}
}
