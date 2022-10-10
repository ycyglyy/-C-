#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include <conio.h>
#include<time.h>
struct snack
{
	int x;
	int y;
	struct snack* next;
};
snack* head;
int food=0,foodx,foody;//ȫ�ֱ���
// ���¹��λ�� 
void gotoxy(int x, int y) 
{
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//��þ��
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);//�ƶ���� 
    // ���ع�� 
    CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = 0;//1Ϊ��ʾ��꣬0����    
	cursor.dwSize = sizeof(cursor);//���ô�С
	SetConsoleCursorInfo(hOutput, &cursor);
}
// ����ͬ���Ļ������ʹ��ڴ�С��������ֹ�����
void Setsize() 
{
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
   	COORD pos = {170,45};
   	SMALL_RECT rc = {0, 0, 170-1, 45-1};
   	SetConsoleWindowInfo(hOut, true, &rc);
   	SetConsoleScreenBufferSize(hOut, pos);
}
//��ָ�������ӡ'*' 
void goprint(int x,int y)
{
	gotoxy(x,y);
	printf("*");
}
//��ָ�������ӡ' '�����൱��ɾ���ַ� 
void godele(int x,int y)
{
	gotoxy(x,y);
	printf(" ");
}
//������ͼ 
void map()
{
	for(int i=0;i<=40;i++)
	{
		goprint(0,i);
		goprint(120,i);
	}
	for(i=0;i<=120;i=i+2)
	{
		goprint(i,0);
		goprint(i,40);
	}
}

void start()
{
	char c;
	gotoxy(140,25);
	printf("��1��ʼ");//��ʼ����
	while(1)//�ж��Ƿ�ʼ
	{
		if(_kbhit())
		{
			c=_getch();
			if(c=='1')
			break;
		}
	}
	gotoxy(140,25);
	printf("         ");
}
//�������� 
void creatbody()
{
	head=(snack*)malloc(sizeof(snack));
	snack *body1=(snack*)malloc(sizeof(snack));
	snack *body2=(snack*)malloc(sizeof(snack));
	snack *body3=(snack*)malloc(sizeof(snack));//����4�ڿռ� 
	head->x=8;head->y=4;head->next=body1;
	body1->x=6;body1->y=4;body1->next=body2;
	body2->x=4;body2->y=4;body2->next=body3;
	body3->x=2;body3->y=4;body3->next=NULL;
	goprint(head->x,head->y);
	goprint(body1->x,body1->y);
	goprint(body2->x,body2->y);
	goprint(body3->x,body3->y);//��ӡ���� 
}
//�ƶ����� 
void movebody(int dx,int dy)
{
	snack *p,*q;
	p=head;
	q=head;
	while(p->next!=NULL)
		p=p->next;
	godele(p->x,p->y); //ɾ��β�� 
	p->x=head->x+dx;
	p->y=head->y+dy;
	while(q->next->next!=NULL)
		q=q->next;
	q->next=NULL;
	p->next=head;
	head=p;
	/* 
	p=head;
	while(p->next->next!=NULL)
		p=p->next;
	free(p->next);//ɾ�����ͷ�β���ڴ� 
	p->next=NULL;
	snack *q=(snack*)malloc(sizeof(snack));
	q->x=head->x+dx;
	q->y=head->y+dy;
	q->next=head;
	head=q;
	*/
	goprint(head->x,head->y);//��ӡ��ͷ 
}
//�ж�ͷ�Ƿ����߽�������� 
int judge()
{
	if(head->x==0||head->y==0)//�߽��ж�
		return 1;
	if(head->x==120||head->y==40) 
		return 1;
	snack *p=head;//�����ж� 
	while(p->next!=NULL)
		{
			p=p->next;
			if(head->x==p->x&&head->y==p->y)
			return 1;
		 }
	return 0;
}
//�������ʳ�� 
void creatfood()
{
	int m=1;
	snack *p=head;
	while(1)
	{
		foodx=rand()%120;
		foody=rand()%40;
		if(foodx==0||foody==0)
			continue;
		if(foodx%2)
			continue;
		if(foodx==120||foody==40)
			continue;
		while(p)
		{
			if(foodx==p->x&&foody==p->y)
			{
				m=0;
				p=head;
				break;
			}
			p=p->next;
		}
		if(m)
			break;
	}
	goprint(foodx,foody);
	food=1;
}
//��ʳ�� 
int eat(int dx,int dy)
{
	if(food==0)
	creatfood();
	if(head->x==foodx&&head->y==foody)
		{
			snack *p=(snack*)malloc(sizeof(snack));
			snack *q=head;
			while(q->next!=NULL)
				q=q->next;
			q->next=p;
			p->next=NULL;
			p->x=q->x-dx;
			p->y=q->y-dy;
			goprint(p->x,p->y);
			food=0;
			creatfood();
			return 1;
		}
	return 0;
}
//���̿��� 
int clickcon()
{
	int dx=2,dy=0,sp=200,sorce=0,so;
	char c,pa=0;
	srand((unsigned)time(NULL));//�������ʼ������ 
	gotoxy(140,35);
	printf("����");
	gotoxy(140,37);
	printf("%d",sorce);
	while(1)
	{
		if(_kbhit())//������� 
		{
			c=_getch();
			switch(c)
			{
			case 'w':dx=0;dy=-1;break;
			case 's':dx=0;dy=1;break;
			case 'a':dx=-2;dy=0;break;
			case 'd':dx=2;dy=0;break;
			case ' ':while(1)
					{
					if(_kbhit())
					{
						c=_getch();
						if(c==' ')
						break;	
					}
					};break; 
			}
		}
		movebody(dx,dy);
		if(judge())
			return sorce;
		so=eat(dx,dy);
		if(so)
		{
			sorce++;
			if(sp>=40)
			sp=sp-4;
			gotoxy(140,37);
			printf("%d",sorce);
		}
		Sleep(sp);
	}	
	return sorce;
}
//�ͷ���������ռ�ڴ� 
void freesnack()
{
	snack *p=head;
	while(head)
	{
		godele(head->x,head->y);
		head=head->next;
		free(p);
		p=head;
	}	
}
//���ļ���ȡ��ʷ��߷� 
int readfile()
{
	FILE *fp;
	int read;
	fp=fopen("history.txt","r+");
	if(fp==NULL)
	{
		fp=fopen("history.txt","w+");
		fprintf(fp,"0");
		fclose(fp);
		return 0;
	}
	else
	{
		fscanf(fp,"%d",&read);
		fclose(fp);
		return read;
	}
}
//д����߷� 
void writefile(int a)
{
	FILE *fp;
	fp=fopen("history.txt","w+");
	fprintf(fp,"%d",a);
	fclose(fp);
}
int main()
{
	char a; 
	int sorce,high;
	Setsize();
	map();
	creatbody();
	high=readfile();
	gotoxy(135,32);
	printf("��ʷ��߷֣�");
	printf("%d",high);
	start();
	while(1)
	{
		map();
		creatbody();
		high=readfile();
		sorce=clickcon();
		if(sorce>high)
		{
			writefile(sorce);
			gotoxy(147,32);
			printf("%d",sorce);
		}
		freesnack();
		gotoxy(46,20);
		printf("game over");
		gotoxy(40,23);
		printf("��1���¿�ʼ���������˳�����"); 
		while(!_kbhit());
		a=_getch();
		if(a=='1')
		{
			gotoxy(140,37);
			printf("    ");
			gotoxy(46,20);
			printf("             ");
			gotoxy(40,23);
			printf("                               ");
			continue;
		}
		break;
	}
	return 0;
}