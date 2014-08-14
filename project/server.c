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
#include<pthread.h>
#include<time.h>
#include"myinclude.h"

int member[MAX_NUMBER];
char mem[100][10];//套接字昵称连接数组
int n=0;//实际人数；
int read_file(struct data_bag bag[])//用户信息读出文件函数
{
	int fd;
	int i=0;
	int m;
	if((fd=open("usermessage",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
	myerr("open",__LINE__);
	do
	{
		m=read(fd,bag[i].logname,sizeof(bag[i].logname));
		read(fd,bag[i].passwd,sizeof(bag[i].passwd));
		read(fd,bag[i].name,sizeof(bag[i].name));
		i++;
	}while(m!=0);
	return i;
}
void write_file(struct data_bag bag)//用户信息写入文件函数
{
	int fd;
    if((fd=open("usermessage",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
		myerr("open",__LINE__);
	write(fd,bag.logname,sizeof(bag.logname));
	write(fd,bag.passwd,sizeof(bag.passwd));
	write(fd,bag.name,sizeof(bag.name));
	close(fd);
}
void analyze(struct data_bag *bag)//私聊包参数解析
{
	char *p=(bag->buf);
	int i;
	i=0;
	p++;
	while((*p)!=':')
	{
		bag->targetname[i]=(*p);
		i++;
		p++;
	}
	bag->targetname[i]='\0';
	p++;
	i=0;
	while((*p)!='\0')
	{
		bag->buf[i]=(*p);
		i++;
		p++;
	}
	bag->buf[i]='\0';

}
void *communicate(void *arg)
{
	int conn_fd=*(int *)arg;
	int i;
	int m;//获取recv的返回值
	int num;
	struct data_bag bag;
	struct data_bag bag0[50];
	FILE *fp;
	time_get();
	printf("有用户连接上了服务器。。。\n");
	write_time("date.log");
	fp=fopen("date.log","a+");
	fprintf(fp,"有用户连接上了服务器。。。\n");
	fclose(fp);
	while(1)
	{
		memset(&bag,0,sizeof(bag));
		m=recv(conn_fd,(void *)&bag,sizeof(bag),0);
		if(bag.flag==0)
		{
			if(m==0)
			{
				printf("%s退出了聊天！\n",mem[conn_fd]);
				write_time("date.log");
				fp=fopen("date.log","a+");
				fprintf(fp,"%s退出了聊天！\n",mem[conn_fd]);
				fclose(fp);
				close(conn_fd);
				n--;
				memset(mem[conn_fd],0,sizeof(mem[conn_fd]));
				return NULL;
			}
			time_get();
			printf("%s:%s\n",bag.name,bag.buf);
			for(i=0;i<n;i++)
			{
				send(member[i],(void *)&bag,sizeof(bag),0);
			}
		}
		if(bag.flag==1)
		{
			if(m==0)
			{
				printf("%s退出了聊天！\n",mem[conn_fd]);
				write_time("date.log");
				fp=fopen("date.log","a+");
				fprintf(fp,"%s退出了聊天！\n",mem[conn_fd]);
				close(conn_fd);
				fclose(fp);
				n--;
				memset(mem[conn_fd],0,sizeof(mem[conn_fd]));
				return NULL;
			}
			analyze(&bag);
			time_get();
			printf("%s私聊%s:%s\n",bag.name,bag.targetname,bag.buf);
			write_time("date.log");
			fp=fopen("date.log","a+");
			fprintf(fp,"%s私聊%s:%s\n",bag.name,bag.targetname,bag.buf);
			fclose(fp);
			for(i=0;i<100;i++)
			{
				if(strcmp(mem[i],"\0")==0)
					continue;
				else if(strcmp(mem[i],bag.targetname)==0)
				{
					send(i,(void *)&bag,sizeof(bag),0);
					break;
				}
			}
			if(i==100)
			{
				strcpy(bag.buf,"此用户不在线或者不存在该用户");
				send(conn_fd,(void *)&bag,sizeof(bag),0);
			}
		}
		if(bag.flag==2)
		{
			time_get();
			printf("收到了注册信息包!\n");
			write_time("date.log");
			fp=fopen("date.log","a+");
			fprintf(fp,"收到了注册信息包!\n");
			fclose(fp);
			num=read_file(bag0);
			for(i=0;i<num;i++)
				if(strcmp(bag.logname,bag0[i].logname)==0)
				{
					strcpy(bag.buf,"该用户名已经被注册，请更换用户名！");
					send(conn_fd,(void *)&bag,sizeof(bag),0);
					break;
				}
			if(i==num)
			{
				write_file(bag);	
				strcpy(bag.buf,"注册信息已被服务器验证，注册成功！");
				send(conn_fd,(void *)&bag,sizeof(bag),0);
			}
		}
		if(bag.flag==3)
		{
			time_get();
			printf("收到了登录信息包\n");
			write_time("date.log");
			fp=fopen("date.log","a+");
			fprintf(fp,"收到了登录信息包!\n");
			fclose(fp);
			num=read_file(bag0);
			for(i=0;i<num;i++)
				if((strcmp(bag.logname,bag0[i].logname)==0)&&(strcmp(bag.passwd,bag0[i].passwd)==0))
				{
					strcpy(bag.name,bag0[i].name);
					strcpy(mem[conn_fd],bag.name);
					strcpy(bag.buf,"登录成功！");
					send(conn_fd,(void *)&bag,sizeof(bag),0);
					break;
				}
			if(i==num)
			{
				strcpy(bag.buf,"用户名或者密码有误，请重新输入");
				send(conn_fd,(void *)&bag,sizeof(bag),0);
			}
		}
		if(bag.flag==4)
		{
			num=0;
			memset(bag.online,0,sizeof(bag.online));
			for(i=0;i<100;i++)
			{
				if(strcmp(mem[i],"\0")!=0)
				{
					strcpy(bag.online[num],mem[i]);
					num++;
				}
			}
			bag.num=num;
			send(conn_fd,(void *)&bag,sizeof(bag),0);
		}
	}
}

int main()
{
	int sock_fd,conn_fd;
	struct sockaddr_in client_addr,serv_addr;
	int option_value=1;
	int client_len;
	FILE *fp;
	fp=fopen("date.log","a+");
	pthread_t thid;
	time_get();
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
		myerr("socket",__LINE__);
	printf("套接字接口已建立。。。\n");
	write_time("date.log");
	fprintf(fp,"套接字接口已建立。。。\n");
	fclose(fp);
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR|SO_KEEPALIVE,(void *)&option_value,sizeof(int))<0)
		myerr("setsockopt",__LINE__);
	//初始化
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(4507);
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	printf("服务器正在初始化。。。\n");
	write_time("date.log");
	fp=fopen("date.log","a+");
	fprintf(fp,"服务器正在初始化。。。\n");
	fclose(fp);
	if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
		myerr("bind",__LINE__);
	if(listen(sock_fd,12)<0)
		myerr("listen",__LINE__);
	printf("初始化成功，等待链接。。。\n");
	write_time("date.log");
	fp=fopen("date.log","a+");
	fprintf(fp,"初始化成功，等待链接\n");
	fclose(fp);
	while(1)
	{
		client_len=sizeof(struct sockaddr_in);
		conn_fd=accept(sock_fd,(struct sockaddr *)&client_addr,&client_len);
		
		if(conn_fd<0)
		{
			myerr("accept",__LINE__);
		}
		member[n]=conn_fd;
		n++;
		if(pthread_create(&thid,NULL,(void *)&communicate,(void *)&conn_fd)!=0)
		{
			myerr("pthread_create",__LINE__);
		}
	}
	close(sock_fd);
	
}
