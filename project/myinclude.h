#define MAX_CHAT 100 //最大信息数
#define MAX_NUMBER 50//聊天室支持的最大人数
struct data_bag //网络数据包
{
	char name[10];//用户昵称
	char buf[MAX_CHAT];//聊天内容或者临时提示信息
	int flag;//标记(0表示群聊，1表示私聊，2表示登陆信息)
	char targetname[10];//私聊目标用户
	char logname[128];//用户名
	char passwd[128];//密码
	int num;//临时计数
	char online[50][10];//在线用户列表
};

void myerr(char *string,int line)//错误处理
{
	fprintf(stderr,"line:%d",line);
	perror(string);
	exit(1);
}  
void time_get(void)  
{
	time_t now;         //time_t实际为长整形  
	struct tm  *w;          //tm结构体结构化存放时间  

	time(&now);  
	w=localtime(&now);      //获取当前系统时间  

	printf("%04d/%02d/%02d  %02d:%02d:%02d\n",w->tm_year+1900,  w->tm_mon+1,w->tm_mday,w->tm_hour,w->tm_min,w->tm_sec);   
}

void write_time(char string[])
{
	char buf[20];
	strcpy(buf,"date >> ");
	strcat(buf,string);
	system(buf);
}
