/*************************************************************************
    > File Name: ls.c
    > Author: chendi
    > Mail: chendi1995425@gmail.com 
    > Created Time: 2014年07月17日 星期四 09时16分20秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<time.h>
#include<string.h>
#include<limits.h>
#include<dirent.h>
#include<grp.h>

#define MAXLINE 100//一行最多字符数
int maxlen=0;
//错误处理
void myerr(const char *err_string,int line)
{
	fprintf(stderr,"line:%d",line);
	perror(err_string);
	exit(1);
}
//文件查找并排序
void seek_sort(const char *path,char filename[][100],int *num)
{
	DIR *dir;
	struct dirent *msg;
	int i,j;
	char temp[100];
	if((dir=opendir(path))==NULL)
		myerr("opendir",__LINE__);
	while((msg=readdir(dir))!=NULL)
	{
		if(maxlen<strlen(msg->d_name))
			maxlen=strlen(msg->d_name);
		(*num)++;
	}
	closedir(dir);
	dir=opendir(path);	
	for(i=0;i<(*num);i++)
	{
		msg=readdir(dir);
		strcpy(filename[i],msg->d_name);
	}
	closedir(dir);
	for(i=0;i<(*num);i++)
		for(j=0;j<(*num)-i-1;j++)
		if(strcmp(filename[j],filename[j+1])>0)
		{
			strcpy(temp,filename[j]);
			strcpy(filename[j],filename[j+1]);
			strcpy(filename[j+1],temp);
		}	
}
//带-a参数的输出
void display_a(const char *path)
{
	int i;
	int num=0;
	struct stat buf;
	char filename[256][100];
	char path0[100];
	char pathname[256][100];
	seek_sort(path,filename,&num);
	strcat(path,"/");
	strcpy(path0,path);
	for(i=0;i<num;i++)
	{
		strcpy(path,path0);
		strcpy(pathname[i],strcat(path,filename[i]));
		if(stat(pathname[i],&buf)==-1)
			myerr("stat",__LINE__);
		else if(S_ISDIR(buf.st_mode))
		{
			printf("\033[0;33m%-20s     \033[0m",filename[i]);
		}
		else
		printf("%-20s     ",filename[i]);
		if((i+1)%6==0)
			printf("\n");
	}
}
//单个文件信息获取
void msg_get(struct stat buf,char *name)
{
	char buf_time[32];
	struct passwd *sd;
	struct group *gp;
	if(stat(name,&buf)==-1)
		myerr("stat",__LINE__);
	else if(S_ISLNK(buf.st_mode))
		printf("l");
	else if(S_ISREG(buf.st_mode))
		printf("-");
	else if(S_ISDIR(buf.st_mode))
		printf("d");
	else if(S_ISCHR(buf.st_mode))
		printf("c");
	else if(S_ISBLK(buf.st_mode))
		printf("b");
	else if(S_ISFIFO(buf.st_mode))
		printf("f");
	else if(S_ISSOCK(buf.st_mode))
		printf("s");
	if(buf.st_mode&S_IRUSR)
		printf("r");
	else
		printf("-");
	if(buf.st_mode&S_IWUSR)
		printf("w");
	else
		printf("-");
	if(buf.st_mode&S_IXUSR)
		printf("x");
	else
		printf("-");
	if(buf.st_mode&S_IRGRP)
		printf("r");
	else
		printf("-"):
	if(buf.st_mode&S_IWGRP)
		printf("w");
	else
		printf("-");
	if(buf.st_mode&S_IXGRP)
		printf("x");
	else
		printf("-");	
	if(buf.st_mode&S_IROTH)
		printf("r");
	else
		printf("-");
	if(buf.st_mode&S_IWOTH)
		printf("w");
	else
		printf("-");
	if(buf.st_mode&S_IXOTH)
		printf("x");
	else
		printf("-");
	printf("    ");
	sd=getpwuid(buf.st_uid);
	gp=getgrgid(buf.st_gid);
	printf("%4d  ",buf.st_nlink);
	printf("%-8s",sd->pw_name);
	printf("%-8s",gp->gr_name);
	printf("%6d",buf.st_size);
	printf("  %s",ctime(&buf.st_mtime));
	
}
//带-al参数的输出
void display_al(const char path[])
{
	struct stat buf;
	char path0[100];
	int num=0;
	int i,j;
	char filename[256][100];
	char pathname[256][100];
	char temp[100];
	seek_sort(path,filename,&num);
	strcat(path,"/");
	strcpy(path0,path);
	for(i=0;i<num;i++)
	{
		strcpy(path,path0);
		strcpy(pathname[i],strcat(path,filename[i]));
		msg_get(buf,pathname[i]);
		if(S_ISDIR(buf.st_mode))
		{
			printf("\033[0;33m  %s\n\033[0m",filename[i]);
		}
		else
		printf("  %s\n",filename[i]);
	}
	
}
//带-l参数的输出
void display_l(const char path[])
{
	int i;
	struct stat buf;
	char path0[100];
	int num=0;
	char filename[256][100];
	char pathname[256][100];
	seek_sort(path,filename,&num);
	strcat(path,"/");
	strcpy(path0,path);
	for(i=0;i<num;i++)
	{if(filename[i][0]!='.')
		{
		strcpy(path,path0);
		strcpy(pathname[i],strcat(path,filename[i]));
		msg_get(buf,pathname[i]);
		if(S_ISDIR(buf.st_mode))
		{
			printf("\033[0;33m  %s\n\033[0m",filename[i]);
		}
		else
		printf("  %s\n",filename[i]);
		}
	}
	
}
//不带任何参数的输出
void display(const char *path)
{
	int i;
	int n=0;
	int num=0;
	struct stat buf;
	char filename[256][100];
	char path0[100];
	char pathname[256][100];
	seek_sort(path,filename,&num);
	strcat(path,"/");
	strcpy(path0,path);
	for(i=0;i<num;i++)
	{
		if(filename[i][0]!='.')
		{
			strcpy(path,path0);
			strcpy(pathname[i],strcat(path,filename[i]));
			if(stat(pathname[i],&buf)==-1)
				myerr("stat",__LINE__);
			else if(S_ISDIR(buf.st_mode))
				printf("\033[0;33m%-20s     \033[0m",filename[i]);
			else
				printf("%-20s     ",filename[i]);
			n++;
		}
		if((n%6==0)&&(n!=0))
			printf("\n");
	}
	
}
void display_R(const char path[])
{
	struct stat buf;
	char path0[100];
	int num=0;
	int i,n=0;
	char filename[256][100];
	char pathname[256][100];
	seek_sort(path,filename,&num);
	printf("\n%s:\n",path);
	strcat(path,"/");
	strcpy(path0,path);
	for(i=0;i<num;i++)
	{
		strcpy(path,path0);
		strcpy(pathname[i],strcat(path,filename[i]));
		if(stat(pathname[i],&buf)==-1)
			myerr("stat",__LINE__);
		else if(S_ISDIR(buf.st_mode))
		{
			printf("\033[0;33m%-20s     \033[0m",filename[i]);
		}
		else
		printf("%-20s     ",filename[i]);
		if((i+1)%6==0)
			printf("\n");
	}
	
	for(i=0;i<num;i++)
	{
		if(filename[i][0]=='.')
			continue;
		strcpy(path,path0);
		strcpy(pathname[i],strcat(path,filename[i]));
		if(stat(pathname[i],&buf)==-1)
			myerr("stat",__LINE__);
		else if(S_ISDIR(buf.st_mode))
		{
			display_R(path);
		}
	}
	printf("\n");
	
}

int main(int argc,char *argv[])
{
	char *pre_path;//当前路径名
	pre_path=(char *)malloc(MAXLINE);
	getcwd(pre_path,MAXLINE);
	if(argc==3)
	{
		if(strcmp(argv[1],"-a\0")==0)
		display_a(argv[2]);
		else if(strcmp(argv[1],"-al\0")==0)
		display_al(argv[2]);
		else if(strcmp(argv[1],"-l\0")==0)
		display_l(argv[2]);
		else if(strcmp(argv[1],"-R\0")==0)
		display_R(argv[2]);
		
		else
		printf("invalid input!");
	}
	else if(argc==2)
	{
		if(strcmp(argv[1],"-a\0")==0)
			display_a(pre_path);
		else if(strcmp(argv[1],"-al\0")==0)
			display_al(pre_path);
		else if(strcmp(argv[1],"-l\0")==0)
			display_l(pre_path);
		else if(strcmp(argv[1],"-R\0")==0)
			display_R(pre_path);
		
		else
			display(argv[1]);
		
	}
	else if(argc==1)
		display(pre_path);
	else
		printf("there are more than three parameters!");
	printf("\n");
	return 0;
}
