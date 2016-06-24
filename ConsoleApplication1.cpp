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
	char *ch = p->s_name; //���������а�����
	cout << "����ѧ�ţ�" << endl;
	cin >> p->i_num;
	cout << "����������" << endl;
	cin >> ch;           //���������а�����
	cout << "����ɼ���" << endl;
	cin >> p->f_math;
}
STUDENT * create()
{
	STUDENT *p;
	if (node == 0)
	{
		HEAD = (STUDENT *)malloc(sizeof(STUDENT));//����ͷ�ڵ�
		node++;
		p = HEAD;
		input(p);
		p->next = NULL;
		p = NULL;
	}
	else if (node >= 1) //����Ѿ�����ͷ�ڵ�
	{
		p = HEAD;//��ͷ��ʼ
		while (p->next != NULL)
		{
			p = p->next; //pָ��������β��
		}
		p->next = (STUDENT *)malloc(sizeof(STUDENT)); node++; //β���ӽڵ㣬�ڵ�����һ
		p = p->next; //��ָ���µ�β��
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
		cout << "û��ѧ����Ϣ��"<<endl;
	}
	else if (node == 1)
	{
		system("cls");
		cout << "ѧ��\t" << "����\t" << "����\t"<<endl;
		cout << p->i_num<<"\t";
		cout <<p->s_name<<"\t";
		cout <<p->f_math<<"\t" <<endl;
	}
	else 
	{
		system("cls");
		cout << "ѧ��\t" << "����\t" << "����\t"<<endl;
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
	cout << "������Ҫɾ����ѧ��ѧ�ţ�" << endl;
	cin >> number;
	while (find->i_num != number) find = find->next;//Ѱ��ָ���ҵ�Ŀ��
	p2 = find;//p2ָ��Ŀ��
	//��ʼ�ж�Ŀ������
	if (p2 == head && p2->next!=NULL)//��ͷ����β
	{
		HEAD = HEAD->next;//ͷ������  ע�� ����д�� head=head->next��
						  /*��Ϊ����ֻ�Ǹı���headָ���λ�ã���δ�ı�HEADָ���λ�ã�
						  free��p1���ὫHEAD��ŵ�next���δ֪��displayʱ�ͻ����*/
		free(p1);//ɾ��Ŀ��
		node--;
		p1 = p2 = find = NULL;
		cout << "ɾ����ɡ�" << endl;
	}
	else if (p2 == head && p2->next == NULL)//��ͷ��β
	{
		head = NULL;
		free(p2);
		node--;
		find = p1 = p2 = NULL;
	}
	else if (p2!=head && p2->next != NULL) //����ͷ����β
	{
		while (p1->next != p2) p1 = p1->next;//p1ָ��Ŀ���ǰһ��
		p1->next = p2->next;//p1��p2��Ŀ�֮꣩��Ľ������
		free(p2);
		node--;
		p2 = NULL;
		cout << "ɾ����ɡ�" << endl;
	}
	else if (p2->next == NULL)//��β��
	{
		while (p1->next != p2) p1 = p1->next; //p1ָ��p2֮ǰ�Ľ��
		p1->next = NULL;
		free(p2);
		node--;
		p2 = NULL;
		cout << "ɾ����ɡ�" << endl;
	}
	else cout << "�����ˡ�" << endl;
}
void saveInfo(STUDENT *head)
{
	if (node == 0)
	{
		cout << "û��ѧ����Ϣ��" << endl;
		return;
	}
	STUDENT *p=head;
	FILE *fp;
	_mkdir("F:\\code\\ѧ����Ϣ");
	char flname[26]="F:\\code\\ѧ����Ϣ\\info.dat";
	if ((fp = fopen(flname,"ab")) == NULL)
	{
		cout << "����ʧ�ܣ������ԡ�" << endl;
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
	cout << "�洢�ɹ���" << endl;
	system("pause");
}
void choose()
{
	short int c;
	cout << "1:���\t" << "2:ɾ��\t" << "3:��ʾ����\t" << "4:�˳�\t"<<"5:�洢��Ϣ"<<endl;
	cout << "���������ѡ��:" << endl;
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