/*************************************************************************
    > File Name: daemon.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月21日 星期一 19时11分58秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include<sys/param.h>
#include<syslog.h>

int init_daemon(void)
{
	int pid;
	int i;
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);

	pid=fork();
	if(pid>0)
		exit(0);
	else if(pid<0)
		return -1;
	setsid();
	pid=fork();
	if(pid>0)
		exit(0);
	else if(pid<0)
		return -1;
	for(i=0;i<NOFILE;close(i++));
	chdir("/");
	umask(0);
	signal(SIGCHLD,SIG_IGN);
	return 0;
}
int main()
{
	time_t now;
	init_daemon();
	syslog(LOG_USER|LOG_INFO,"测试守护进程!\n");
	while(1)
	{
		sleep(8);
		time(&now);
		syslog(LOG_USER|LOG_INFO,"系统时间：\t%s\t\t\n",ctime(&now));

	}
}
