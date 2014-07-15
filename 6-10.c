/*************************************************************************
    > File Name: 6-10.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月14日 星期一 20时25分29秒
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
	int fd;
	char buf[32];

	if(fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU)<0)
		my_err("open",__LINE__);
	if(unlink("temp")<0)
		my_err("unlink",__LINE__);
	printf("file has been unlinked!\n");

	if(write(fd,"temp",5)<0)
		my_err("write",__LINE__);
	if(lseek(fd,0,SEEK_SET)==-1)
		my_err("lseek",__LINE__);
	if(read(fd,buf,5)<0)
		my_err("read",__LINE__);
	printf("%s\n",buf);
	return 0;
		
}
