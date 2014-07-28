/*************************************************************************
    > File Name: myshell.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月25日 星期五 15时44分57秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<dirent.h>

#define normal 0;
#define out_redirect 1;
#define in_redirect 2;
#define have_pipe 3;
void get_input(char *buf)
{
	int len=0;
	int ch;

	ch=getchar();
	while(len<256&&ch!='\n')
	{
		buf[len++]=ch;
		ch=getchar();
	}
	if(len==256)
	{
		printf("command is too long\n");
		exit(-1);
	}
	buf[len]='\n';
	len++;
	buf[len]='\0';
}
void explain_input(char *buf,int *argcount,char arglist[100][256])
{
	char *p=buf;
	char *q=buf;
	int number=0;
	while(1)
	{
		if(p[0]=='\n')
			break;
		if(p[0]==' ')
			p++;
		else
		{
			q=p;
			number=0;
			while( (q[0]!=' ')&&(q[0]!='\n'))
			{
				number++;
				q++;
			}
			strncpy(arglist[*argcount],p,number+1);
			arglist[*argcount][number]='\0';
			*argcount=*argcount +1;
			p=q;
		}
	}
}
void do_cmd(int argcount,char arglist[100][256])
{
	int flag=0;
	int how=0;
	int background=0;
	int status;
	int i;
	int fd;
	char *arg[argcount+1];
	char *argnext[argcount+1];
	char *file;
	pid_t pid;
	for(i=0;i<argcount;i++)
		arg[i]=(char *)arglist[i];
	arg[argcount]=NULL;
	for(i=0;i<argcount;i++)
	{
		if(strncmp(arg[i],"&",1)==0)
		{
			if(i==argcount-1)
			{
				background=1;
				arg[argcount-1]=NULL;
				break;
			}
			else
			{
				printf("command\n");
				return;
			}
		}
	}
	for(i=0;arg[i]!=NULL;i++)
	{
		if(strcmp(arg[i],">")==0)
		{
			flag++;
			how=out_redirect;
			if(arg[i+1]==NULL)
				flag++;
		}
		if(strcmp=(arg[i],"<")==0)
		{
			flag++;
			how=in_redirect;
			if(i==0)
				flag++;
		}
		if(strcmp(arg[i],"|")==0)
		{
			flag++;
			how=have_pipe;
			if(arg[i+1]==NULL)
				flag++;
			if(i==0)
				flag++;
		}
	}
	
	if(flag>1)
	{
		printf("wrong command");
		return;
	}
	if(how==out_redirect)

}


int main(int argc,char **argv)
{
	int i;
	int argcount =0;
	char arglist[100][256];
	char **arg=NULL;
	char *buf=NULL;

	buf=(char *)malloc(256);
	if(buf ==NULL)
	{
		perror("malloc failed");
		exit(-1);
	}
	while(1)
	{
		memset(buf,0,256);
		printf("myshell@");
		get_input(buf);
		if(strcmp(buf,"exit\n")==0)
			break;
		for(i=0;i<100;i++)
			arglist[i][0]='\0';
		argcount=0;
		explain_input(buf,&argcount,arglist);
		do_cmd(argcount,arglist);
	}
	if(buf!=NULL)
	{
		free(buf);
		buf=NULL;
	}
	exit(0);
}
