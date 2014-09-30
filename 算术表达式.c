/*************************************************************************
    > File Name: 算术表达式.c
    > Author: chendi
    > Mail: chendi1995@sohu.com 
    > The compiler environment:vim + gcc
    > Created Time: 2014年09月29日 星期一 19时10分42秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct Stacknode
{
	int data; //数值
	char mark; //符号
	struct Stacknode *next;
}slStacktype;

struct marklist
{
	char markname; //符号
	int order; //优先级
};
void init_mark(struct marklist mark[])//符号表初始化
{
	mark[0].markname='#';
	mark[0].order=0;
	mark[1].markname='(';
	mark[1].order=1;
	mark[2].markname=')';
	mark[2].order=1;
	mark[3].markname='+';
	mark[3].order=2;
	mark[4].markname='-';
	mark[4].order=2;
	mark[5].markname='*';
	mark[5].order=3;
	mark[6].markname='/';
	mark[6].order=3;

}
slStacktype *create(void)
{
	slStacktype *top;
	top=(slStacktype *)malloc(sizeof(slStacktype));
	top->next=NULL;
	return *top;
}
void pushstack1(slStacktype *top,int data)//数值压栈
{
	slStacktype *p;
	p=(slStacktype *)malloc(sizeof(slStacktype));
	p->data=data;
	p->next=top->next;
	top->next=p;
}

void pushstack2(slStacktype *top,char mark)//符号压栈
{
	slStacktype *p;
	p=(slStacktype *)malloc(sizeof(slStacktype));
	p->mark=mark;
	p->next=top->next;
	top->next=p;
}

int main()
{
	struct marklist mark[7];
	char formula[30];   //存储公式的字符串
	char ch;			//待操作的字符
	init_mark(mark);
	slStacktype *top1,*top2;
	top1=create();
	top2=create();
	pushstack2(top2,'#');
	printf("please input the formula:\n");
	scanf("%s",formula);


		

}

