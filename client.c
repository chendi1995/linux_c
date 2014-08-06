/*************************************************************************
    > File Name: client.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年08月04日 星期一 19时48分36秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void myerr(char *string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(string);
	exit(1);
}

int main()
{
	struct sockaddr_in client_addr,serv_addr;
	int sock_fd;
	char name[6];
	char buf[21];
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
		myerr("socket",__LINE__);
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(4507);
	if(inet_aton("222.24.51.133",&serv_addr.sin_addr)<0)
		myerr("inet_aton",__LINE__);
	if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
		myerr("connect",__LINE__);
	printf("已链接上服务器。。。\n");
	printf("请输入昵称:");
	gets(name);
	if(send(sock_fd,(void *)name,sizeof(name),0)<0)
		myerr("send",__LINE__);
	while(1)
	{
		printf("%s:",name);
		gets(buf);
		printf("\n");
		send(sock_fd,(void *)buf,sizeof(buf),0);
	}
	
}
