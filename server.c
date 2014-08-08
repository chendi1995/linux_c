/*************************************************************************
    > File Name: server.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年08月02日 星期六 11时23分39秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<errno.h>

#define MAX_NUMBER 50  //聊天室最大人数
#define MAX_CHAT 20 //最多聊天字数
struct data_bag //网络数据包
{
	char name[6];//用户昵称
	char buf[MAX_CHAT];//聊天内容
}bag;
int member[MAX_NUMBER];
int n=0;//实际人数；
void myerr(char *string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(string);
	exit(1);
}

void *communicate(void *arg)
{
	int conn_fd=*(int *)arg;
	int i;
		printf("有用户加入了聊天。。。\n");
		while(1)
		{
			memset(bag.buf,0,sizeof(bag.buf));
			recv(conn_fd,(void *)&bag,sizeof(bag),0);
			printf("%s:%s\n",bag.name,bag.buf);
			for(i=0;i<n;i++)
			{
				send(member[i],(void *)&bag,sizeof(bag),0);
			}
		}
}

int main()
{
	int sock_fd,conn_fd;
	struct sockaddr_in client_addr,serv_addr;
	int option_value=1;
	int client_len;
	pthread_t thid;
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
		myerr("socket",__LINE__);
	printf("套接字接口已建立。。。\n");
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR|SO_KEEPALIVE,(void *)&option_value,sizeof(int))<0)
		myerr("setsockopt",__LINE__);
	//初始化
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(4507);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	printf("服务器正在初始化。。。\n");
	if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
		myerr("bind",__LINE__);
	if(listen(sock_fd,12)<0)
		myerr("listen",__LINE__);
	printf("初始化成功，等待链接。。。\n");
	while(1)
	{
		client_len=sizeof(struct sockaddr_in);
		conn_fd=accept(sock_fd,(struct sockaddr *)&client_addr,&client_len);
		
		if(conn_fd<0)
			myerr("accept",__LINE__);
		member[n]=conn_fd;
		n++;
		if(pthread_create(&thid,NULL,(void *)&communicate,(void *)&conn_fd)!=0)
			myerr("pthread_create",__LINE__);
	}

}
