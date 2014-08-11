#define MAX_CHAT 50 //最大聊天字数
#define MAX_NUMBER 50//聊天室支持的最大人数
struct data_bag //网络数据包
{
	char name[6];//用户昵称
	char buf[MAX_CHAT];//聊天内容
	int flag;//群私聊标记
	char targetname[6];//私聊目标用户
};

void myerr(char *string,int line)//错误处理
{
	fprintf(stderr,"line:%d",line);
	perror(string);
	exit(1);
}
	
