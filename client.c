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
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#define MAX_CHAT 20 //最大聊天字数
struct data_bag //网络数据包
{
	char name[6];//用户昵称
	char buf[MAX_CHAT];//聊天内容
}bag;
void myerr(char *string,int line)//错误处理
{
	fprintf(stderr,"line:%d",line);
	perror(string);
	exit(1);
}
	
void *rec(void *arg)
{
	int conn_fd=*(int *)arg;
	while(1)
	{
		memset(bag.buf,0,sizeof(bag.buf));
		recv(conn_fd,(void *)&bag,sizeof(bag),0);
		printf("%s说:%s\n",bag.name,bag.buf);
	}
}
int main()
{
	struct sockaddr_in client_addr,serv_addr;
	int sock_fd;
	char name[6];
	char buf[MAX_CHAT];
	pthread_t thid;
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
	fflush(stdin);
	gets(bag.name);
	sleep(1);
	printf("昵称验证通过，开始聊天！\n");
	if(pthread_create(&thid,NULL,(void *)rec,(void *)&sock_fd)!=0)
		myerr("pthread_create",__LINE__);
	while(1)
	{
		gets(bag.buf);
		send(sock_fd,(void *)&bag,sizeof(bag),0);
	}
	
}
