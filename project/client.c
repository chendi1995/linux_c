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
#include<assert.h>
#include<termios.h>
#include"myinclude.h"
int getch()
{
	int c=0;
	struct termios org_opts, new_opts;
	int res=0;
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c=getchar();
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	return c;
}

void write_chat1(struct data_bag bag)//群聊聊天信息记录
{
	int fd;
	if((fd=open("group_chat",O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
		myerr("open",__LINE__);
	write_time("group_chat");
	write(fd,bag.name,strlen(bag.name)+1);
	write(fd,"说:",4);
	write(fd,bag.buf,strlen(bag.buf)+1);
	write(fd,"\n",2);
	close(fd);
}
void write_chat2(struct data_bag bag)//私聊聊天信息记录1
{
	int fd;
	if((fd=open(bag.targetname,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
		myerr("open",__LINE__);
	write_time(bag.targetname);
	write(fd,bag.name,strlen(bag.name)+1);
	write(fd,"悄悄地对你说:",20);
	write(fd,bag.buf,strlen(bag.buf)+1);
	write(fd,"\n",2);
	close(fd);
}
void write_chat3(struct data_bag bag)//私聊聊天信息记录2
{
	int fd;
	if((fd=open(bag.name,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR))==-1)
		myerr("open",__LINE__);
	write_time(bag.name);
	write(fd,"你悄悄地对",16);
	write(fd,bag.targetname,strlen(bag.targetname)+1);
	write(fd,"说:",4);
	write(fd,bag.buf,strlen(bag.buf)+1);
	write(fd,"\n",2);
	close(fd);
}

void read_chat(struct data_bag bag)	
{
	char buf[20];
	strcpy(buf,"cat ");
	strcat(buf,bag.name);
	system(buf);

}



void usr_create(int sock_fd)
{
	struct data_bag bag;
	int i;
 	char pd[128],pd1[128];
 	char a;
	bag.flag=2;
	while(1)
	{
		printf("**********************\n\n");
		printf("       注册界面\n\n");
		printf("**********************\n");
		printf("用户名:");
		scanf("%s",bag.logname);
		getchar();
		printf("\n");
		printf("密码：");
		while(1)
		{
			for(i=0;;i++)
			{
				pd[i]=getch();
				if(pd[i]=='\n')
				{
					pd[i]='\0';
					break;
				}
				if(pd[i]==127)
				{
					printf("\b \b");
					i=i-2;
				}
				else
					printf("*");
				if(i<0)
					pd[0]='\0';
			}

			printf("\n再次输入密码：");

			for(i=0;;i++)
			{
				pd1[i]=getch();
				if(pd1[i]=='\n')
				{
					pd1[i]='\0';
					break;
				}
				if(pd1[i]==127)
				{
					printf("\b \b");
					i=i-2;
				}

				else
					printf("*");
				if(i<0)
					pd1[0]='\0';
			}
			if(strcmp(pd,pd1)==0)

				break;
			else
			{
				printf("\n两次输入的密码不一致，请重新输入：\n");
				printf("密码：");
			}
		}
		strcpy(bag.passwd,pd);
		printf("\n昵称: ");
		scanf("%s",bag.name);
		send(sock_fd,(void *)&bag,sizeof(bag),0);
		recv(sock_fd,(void *)&bag,sizeof(bag),0);
		if(strcmp(bag.buf,"该用户名已经被注册，请更换用户名！")==0)
			printf("%s\n",bag.buf);
		else
			break;
	}
	printf("%s\n",bag.buf);
	printf("等待5秒系统自动返回登陆界面!\n");
	sleep(5);
	
}
struct data_bag usr_login(int sock_fd)
{
	struct data_bag bag;
	int i;
 	char pd[128];

	bag.flag=3;
	printf("**********************\n\n");

	printf("       登录界面\n\n");
	printf("**********************\n");
	while(1)
	{
		printf("用户名:");
		scanf("%s",bag.logname);
		getchar();
		printf("\n");
		printf("密码：");
		for(i=0;;i++)
		{
			pd[i]=getch();
			if(pd[i]=='\n')
			{
				pd[i]='\0';

				break;
			}
			if(pd[i]==127)
			{
				printf("\b \b");
				i=i-2;
			}
			else
				printf("*");
			if(i<0)
				pd[0]='\0';
		}
		strcpy(bag.passwd,pd);
		send(sock_fd,(void *)&bag,sizeof(bag),0);
		recv(sock_fd,(void *)&bag,sizeof(bag),0);
		printf("\n");
		printf("%s\n",bag.buf);
		if(strcmp(bag.buf,"登录成功！")==0)
			break;
	}
	return bag;

}
struct data_bag screen(int sock_fd)
{
	int choice;
	struct data_bag bag;
loop:printf("**********************\n\n");
	printf("    1.新用户注册\n\n");
	printf("    2.老用户登录\n\n");
	printf("**********************\n");
	printf("请选择：1或者2\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: usr_create(sock_fd);
		case 2: bag=usr_login(sock_fd) ;return bag;
		default: printf("输入选项无效！\n");goto loop;
	}
}

void *rec(void *arg)
{
	struct data_bag bag;
	int conn_fd=*(int *)arg;
	int m;
	int i;
	while(1)
	{
		memset(&bag,0,sizeof(bag));
		m=recv(conn_fd,(void *)&bag,sizeof(bag),0);
		if(m==0)
		{
			printf("服务器异常关闭，聊天结束!\n");
			close(conn_fd);
			exit(2);
		}
		if(bag.flag==0)
	
		{
			time_get();
			printf("%s说:%s\n",bag.name,bag.buf);
			
		}
		if(bag.flag==1)
		{
			if(strcmp(bag.buf,"此用户不在线或者不存在该用户")==0)
				printf("此用户不在线或者不存在该用户！\n");
			else
			{
				time_get();
				printf("%s悄悄地对你说:%s\n",bag.name,bag.buf);
				write_chat2(bag);
				write_chat3(bag);
			}
		}
		if(bag.flag==4)
		{
			printf("在线用户列表:\n");
			for(i=0;i<bag.num;i++)
			{
				printf("%s\n",bag.online[i]);
			}
			fflush(stdin);
			printf("总计人数:%d\n",bag.num);
		}

	}
}

int main(int argc,char *argv[])
{
	struct data_bag bag;
	struct sockaddr_in client_addr,serv_addr;
	int sock_fd;
	char name[6];
	char buf[MAX_CHAT];
	int i;
	pthread_t thid;
	if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
		myerr("socket",__LINE__);
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(4507);
	if(inet_aton(argv[1],&serv_addr.sin_addr)<0)
		myerr("inet_aton",__LINE__);
	if(connect(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in))<0)
		myerr("connect",__LINE__);
	time_get();
	printf("已链接上服务器。。。\n");
//	printf("请输入昵称:");
//	fflush(stdin);
//	scanf("%s",bag.name);
//	getchar();
	bag=screen(sock_fd);
	sleep(1);
	printf("登陆成功，开始聊天！\n");
	printf("tips:默认进入群聊模式，私聊输入“-昵称:内容”\n");
	printf("输入“lc”可查看该用户的私聊聊天记录\n");
	printf("输入“l”可查看群聊聊天记录");
	printf("输入“lo”可查看当前在线用户列表\n");
	printf("输入“exit”可退出客户端\n");
	if(pthread_create(&thid,NULL,(void *)rec,(void *)&sock_fd)!=0)
		myerr("pthread_create",__LINE__);
	while(1)
	{
		fflush(stdin);
		scanf("%s",bag.buf);
		if(bag.buf[0]=='-')
		{
			bag.flag=1;
			for(i=0;i<100;i++)
				if(bag.buf[i]==':')
					break;
			if(i!=100)
				send(sock_fd,(void *)&bag,sizeof(bag),0);
			else
				printf("输入不符合规范\n");
				

		}
		else if(strcmp(bag.buf,"lc")==0)
		{
			read_chat(bag);
		}
		else if(strcmp(bag.buf,"l")==0)
		{
			system("cat group_chat");
		}
		else if(strcmp(bag.buf,"lo")==0)
		{
			bag.flag=4;
			send(sock_fd,(void *)&bag,sizeof(bag),0);
			sleep(1);
		}
		else if(strcmp(bag.buf,"exit")==0)
		{
			printf("已成功退出聊天！\n");
			exit(0);
		}
		else if((strcmp(bag.buf,"\0")!=0)&&(strlen(bag.buf)<=MAX_CHAT))
		{
			bag.flag=0;
			send(sock_fd,(void *)&bag,sizeof(bag),0);
			write_chat1(bag);
		}
		else if(strlen(bag.buf)>MAX_CHAT)
			printf("字数过长，请分次输入！\n");
		else
			printf("不能输入空消息\n");
	}
	return 0;
}
