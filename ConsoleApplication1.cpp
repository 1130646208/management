#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <direct.h>
using namespace std;

typedef struct student
{
	int i_num;
	char s_name[20];
	float f_math;
	struct student *next;
}STUDENT;
static int node = 0;
STUDENT *HEAD;

void input(STUDENT *p)
{
	char *ch = p->s_name; //不这样不行啊！！
	cout << "输入学号：" << endl;
	cin >> p->i_num;
	cout << "输入姓名：" << endl;
	cin >> ch;           //不这样不行啊！！
	cout << "输入成绩：" << endl;
	cin >> p->f_math;
}
STUDENT * create()
{
	STUDENT *p;
	if (node == 0)
	{
		HEAD = (STUDENT *)malloc(sizeof(STUDENT));//创建头节点
		node++;
		p = HEAD;
		input(p);
		p->next = NULL;
		p = NULL;
	}
	else if (node >= 1) //如果已经有了头节点
	{
		p = HEAD;//从头开始
		while (p->next != NULL)
		{
			p = p->next; //p指向了链表尾部
		}
		p->next = (STUDENT *)malloc(sizeof(STUDENT)); node++; //尾部加节点，节点数加一
		p = p->next; //再指向新的尾巴
		p->next = NULL;
		input(p);
		p = NULL;
	}
	return HEAD;
}
void display(STUDENT *head)
{
	
	STUDENT *p;
	p = head;
	if (node == 0)
	{
		cout << "没有学生信息。"<<endl;
	}
	else if (node == 1)
	{
		system("cls");
		cout << "学号\t" << "姓名\t" << "分数\t"<<endl;
		cout << p->i_num<<"\t";
		cout <<p->s_name<<"\t";
		cout <<p->f_math<<"\t" <<endl;
	}
	else 
	{
		system("cls");
		cout << "学号\t" << "姓名\t" << "分数\t"<<endl;
		while (p->next != NULL)
		{
			cout << p->i_num<<"\t";
			cout <<p->s_name<<"\t";
			cout <<p->f_math<<"\t" <<endl;
			p = p->next;
		}
		p->next = NULL;
		cout << p->i_num<<"\t";
		cout << p->s_name<<"\t";
		cout << p->f_math<<"\t"<< endl;
	}
}
void delitem(STUDENT *head)
{	
	int number;
	STUDENT *p1, *p2;
	STUDENT *find=head;
	p1 = p2 = head;	
	cout << "请输入要删除的学生学号：" << endl;
	cin >> number;
	while (find->i_num != number) find = find->next;//寻觅指针找到目标
	p2 = find;//p2指向目标
	//开始判断目标属性
	if (p2 == head && p2->next!=NULL)//是头不是尾
	{
		HEAD = HEAD->next;//头结点后移  注意 不能写成 head=head->next；
						  /*因为后者只是改变了head指向的位置，并未改变HEAD指向的位置，
						  free（p1）会将HEAD存放的next变成未知，display时就会出错*/
		free(p1);//删除目标
		node--;
		p1 = p2 = find = NULL;
		cout << "删除完成。" << endl;
	}
	else if (p2 == head && p2->next == NULL)//是头是尾
	{
		head = NULL;
		free(p2);
		node--;
		find = p1 = p2 = NULL;
	}
	else if (p2!=head && p2->next != NULL) //不是头不是尾
	{
		while (p1->next != p2) p1 = p1->next;//p1指向目标的前一个
		p1->next = p2->next;//p1与p2（目标）之后的结点相连
		free(p2);
		node--;
		p2 = NULL;
		cout << "删除完成。" << endl;
	}
	else if (p2->next == NULL)//是尾巴
	{
		while (p1->next != p2) p1 = p1->next; //p1指向p2之前的结点
		p1->next = NULL;
		free(p2);
		node--;
		p2 = NULL;
		cout << "删除完成。" << endl;
	}
	else cout << "出错了。" << endl;
}
void saveInfo(STUDENT *head)
{
	if (node == 0)
	{
		cout << "没有学生信息。" << endl;
		return;
	}
	STUDENT *p=head;
	FILE *fp;
	_mkdir("F:\\code\\学生信息");
	char flname[26]="F:\\code\\学生信息\\info.dat";
	if ((fp = fopen(flname,"ab")) == NULL)
	{
		cout << "访问失败，请重试。" << endl;
	}
	else
	{
		fp = fopen(flname, "ab+");
		while (p->next != NULL)
		{
			memcpy(fp,p,sizeof(STUDENT));
	//		fwrite(dst, sizeof(STUDENT),1,fp);
			p = p->next;
		}	
	}
	fclose(fp);
	fp = NULL;
//	dst = NULL;
	p = NULL;
	cout << "存储成功！" << endl;
	system("pause");
}
void choose()
{
	short int c;
	cout << "1:添加\t" << "2:删除\t" << "3:显示所有\t" << "4:退出\t"<<"5:存储信息"<<endl;
	cout << "请输入你的选择:" << endl;
	cin >> c;
	switch (c)
	{
	case 1: create();break;
	case 2: delitem(HEAD);break;
	case 3: display(HEAD);break;
	case 4: exit(0);break;
	case 5: saveInfo(HEAD); break;
	}
}


int main()
{
    while(1) choose();
	system("pause");
	return 0;
}