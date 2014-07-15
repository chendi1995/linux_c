/*************************************************************************
    > File Name: my_chmod.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月14日 星期一 16时38分43秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int main(int argc,char *argv[])
{
	struct stat buf;
	if(argc!=2)
	{
		printf("error!");
		exit(0);
	}
	if(stat(argv[1],&buf)==-1)
	{
		perror("");
		exit(1);
	}
	printf("device is:%d\n",buf.st_dev);
	printf("inode is:%d\n",buf.st_ino);
	printf("mode is:%o\n",buf.st_mode);
	printf("number of hard links is:%d\n",buf.st_nlink);
	printf("user ID of owner is:%d\n",buf.st_uid);
	printf("group ID is:%d\n",buf.st_gid);

}
