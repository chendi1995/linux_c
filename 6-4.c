/*************************************************************************
    > File Name: 6-4.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月14日 星期一 10时52分23秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

void my_err(const char * err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
int main()
{
	int ret;
	int access_mode;
	int fd;

	if((fd=open("e_64",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU))==-1)
		my_err("open",__LINE__);
	if((ret=fcntl(fd,F_GETFL))<0)
		my_err("open",__LINE__);
	access_mode=ret&O_ACCMODE;
	if(access_mode==O_RDONLY)
		printf("read only");
	else if(access_mode==O_WRONLY)
		printf("write only");
	else if(access_mode==O_RDWR)
		printf("read and write");
	if(ret&O_APPEND)
		printf(",append");
	if(ret&O_SYNC)
		printf(",sync");
	printf("\n%x\n%x\n%x\n%x",ret,access_mode,O_APPEND,O_SYNC);
	return 0;
	
}
