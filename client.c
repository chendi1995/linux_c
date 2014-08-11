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
#include"myinclude.h"
void *rec(void *arg)
{
	struct data_bag bag;
	int conn_fd=*(int *)arg;
	while(1)
	{
		memset(&bag,0,sizeof(bag));
		recv(conn_fd,(void *)&bag,sizeof(bag),0);
		if(bag.flag==0)
			printf("%s说:%s\n",bag.name,bag.buf);
		if(bag.flag==1)
		{
			if(strcmp(bag.buf,"此用户不在线或者不存在该用户")==0)
				printf("此用户不在线或者不存在该用户！\n");
			else
			printf("%s悄悄地对你说:%s\n",bag.name,bag.buf);
		}
	}
}

int main()
{
	struct data_bag bag;
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
	scanf("%s",bag.name);
	getchar();
	sleep(1);
	printf("昵称验证通过，开始聊天！\n");
	printf("备注:默认进入群聊模式，私聊输入“-昵称:内容”\n");
	if(pthread_create(&thid,NULL,(void *)rec,(void *)&sock_fd)!=0)
		myerr("pthread_create",__LINE__);
	while(1)
	{
		fflush(stdin);
		gets(bag.buf);
		if(bag.buf[0]=='-')
		{
			bag.flag=1;
			send(sock_fd,(void *)&bag,sizeof(bag),0);
			

		}
		else if((strcmp(bag.buf,"\0")!=0)&&(strlen(bag.buf)<=MAX_CHAT))
		{
			bag.flag=0;
			send(sock_fd,(void *)&bag,sizeof(bag),0);
		}
		else if(strlen(bag.buf)>MAX_CHAT)
			printf("字数过长，请分次输入！\n");
		else
			printf("不能输入空消息\n");
	}
	
}
