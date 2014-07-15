/*************************************************************************
    > File Name: 6-9.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月14日 星期一 20时02分19秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char ** argv)
{
	if(argc<3)
	{
		printf("my_mv <old file> <new file>\n");
		exit(0);
	}
	if(rename(argv[1],argv[2])<0)
	{
		perror("rename");
		exit(1);
	}
	return 0;
}
