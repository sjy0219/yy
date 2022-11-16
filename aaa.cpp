#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef int QElemType;
typedef int Status;
typedef struct QNode{
	QElemType data;  //���˵ı�� 
	struct QNode *next; //��һ�����˱�ŵĵ�ַ 
}QNode,*Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;

//����һ���ն��� 
Status InitQueue(LinkQueue &q)   
{
	q.front=q.rear=(Queueptr)malloc(sizeof(QNode));
	if(q.front==NULL)
	{
		exit(OVERFLOW);
	}
	q.front->next=NULL;
	return OK;
}

//����Ԫ��e��Ϊ�µĶ�βԪ�� 
Status EnQueue(LinkQueue &q,QElemType e) 
{
	Queueptr p;
	p=(Queueptr)malloc(sizeof(QNode));
	if(!p)
	{
		exit(OVERFLOW);
	}
	p->data=e;
	q.rear->next=p;
	q.rear=p;
	return OK;
}

Status DeQueue(LinkQueue &q,QElemType &e)
{
	Queueptr p;
	if(q.rear==q.front)
	{
		return ERROR;
	}
	p=q.front->next;
	e=p->data;
	q.front->next=p->next;
	if(q.rear==p)
	{
		q.rear=q.front;
	}
	free(p);
	return e;
}

Status EmptyQueue(LinkQueue &q)
{
	int r=0;
	if(q.front==q.rear)
	{
		r=0;
	}
	else
	{
		r=1;
	}
	return r;
}

void MyEnQueue(LinkQueue &q1,LinkQueue &q2,QElemType e,int priority)
{
	//ȷ�����ĸ����ȼ��Ĳ��˲�������Ӧ�Ķ���
	if(priority==1)
	{
		EnQueue(q1,e);
	}
	else
	{
		EnQueue(q2,e);
	}

}

Status MyDeQueue(LinkQueue &q1,LinkQueue &q2)
{
	//����
	QElemType e;
	if(EmptyQueue(q1))
	{
		e=DeQueue(q1,e);
	}
	else if(EmptyQueue(q2))
	{
		e=DeQueue(q2,e);
	}
	else
	{
		e=-1;
	}
	return e;
}


struct PT{
	char name[20];
	int age;
	char sex;
	char xueli[10];  //ѧ��
	char address[70];//סַ
	int telephone;      //�绰����
	char department[70];     //����
	int priority;
};

int main()  //������ 
{
	LinkQueue q1,q2;  //�ֱ��ʾ�ͼ��͸߼��Ĳ��˶��� 
	QElemType idi=1,ido=-1;  //�ֱ��ʾ��Ӻͳ��ӵĲ��˵�id 
	int menu=0; //�ֱ�Ϊ�û�ѡ��Ĳ˵���źͲ��˿��������ȼ���

	InitQueue(q1);
	InitQueue(q2); 
	struct PT pt[100];
	
	printf("\n\n"); 
	printf("       ---------------------------------------------------------------------------------\n\n");
	printf("       *********************************************************************************\n\n");
	printf("\n");
	printf("       **                      ��ӭʹ�á���ҽԺ�Ŷ�ϵͳ                               **\n");
	printf("\n");  
	printf("       **                      1. �µĲ��˼�����к���                                **\n");
	printf("\n");
	printf("       **                      2. ҽ���������ȼ���Ϊ���˽�������                      **\n");
	printf("\n");
	printf("       **                      3. ��ӡ���˵�Ŀ¼(ֻ�й���Ա�ſ���Ŷ)                  **\n");
	printf("\n");
	printf("       **                      4. �˳�ϵͳ                                            **\n");
	printf("\n");
	printf("       *********************************************************************************\n\n");
	printf("       ---------------------------------------------------------------------------------\n\n");
	
	int i,k=0;  //i����֮��ѭ����Ĵ���  k����ѭ���������������У����󳬹����Σ����˳�ϵͳ��
	char users[50],mima[30];  //�����û��������� ��
	

	while(1)
	{
		printf("       ---------------------------------------------------------------------------------\n\n");
		printf("           �밴���ѡ����Ӧ�Ĳ�����\n");
		printf("           "); 
		scanf("%d",&menu);
		
		switch(menu)
		{
			case 1:{
				printf("           �²��˼���������\n");
				printf("\n\n");
				printf("           ��Ǽǲ��˵Ļ������:\n\n\n");
				printf("           ����  �Ա���mŮf��  ���� ѧ�� סַ �绰���� ���� ���˵����ȼ�\n");
			
				printf("           ����: ");
				scanf("%s",&pt[idi].name);
//				fflush(stdin);     (�������������)
				getchar(); 
				printf("           �Ա�:(m/f)");
				scanf("%c",&pt[idi].sex);
				printf("           ���䣺 ");
				scanf("%d",&pt[idi].age);
				printf("           ѧ��(��ʿ/�о���/����/��ר/����/����/Сѧ)�� ");
				scanf("%s",pt[idi].xueli);
				printf("           ��ͥ��ַ: ");
				scanf("%s",pt[idi].address);
				printf("           �绰����: ");
				scanf("%d",&pt[idi].telephone);
				printf("           �ҺŲ���: ");
				scanf("%s",pt[idi].department);
				printf("           ���������ԣ��ǳ�����������1����������2���� ");
				scanf("%d",&pt[idi].priority); 
				printf("\n");
				printf("           лл������ϡ��Һųɹ����������ĵȴ���\n"); 
				printf("           �ò��˵�ID�ǣ�%d\n",idi);
				MyEnQueue(q1,q2,idi,pt[idi].priority);
				idi++;
				break;
			}
			
			case 2:{
				ido=MyDeQueue(q1,q2);
				if(ido!=-1)
				{
					printf("           ��ǰ�����εĲ��˵�id�ǣ�%d\n",ido);
				}
				else
				{
					printf("           �����β��ˣ�����Ϊ�գ�");
				}
				break;
			} 
				
			case 3:{
				int i=1;
					for(i=0;i<3;i++)
	
					{
						getchar(); 
						printf("\n           ���ȵ�¼��ֻ�й���Ա�ſ��Դ�ӡ������ϢŶ��");
						printf("\n\n           �������û���:"); 
						gets(users);
						
						printf("\n           ����������:");
						
						gets(mima);
						
						if((strcmp(users,"123")==0)&&(strcmp(mima,"123")==0))
						{
							printf("\n           ���Ѿ��ɹ���¼");
							printf("\n           ���Ե�");
							for(i=0;i<20;i++)
							{
								printf(".");
								Sleep(100);
							}
							printf("\n\n\n");				
							break;        
						}						
						k++;
						if(k<3)
						{
							printf("\n       �û�����������Ч ����������:\n");
						}
						
						if(k==3)
						{
							printf("\n       �����������3�� ���˳�����\n");
							Sleep(2000);
							exit(0);
						}
					}
					
					
				printf("           ��ӡ��ǰ���˵�Ŀ¼��\n\n\n");
				printf("       ---------------------------------------------------------------------------------\n\n");
					printf("        ���    ����   �Ա�   ����    ѧ��    סַ    �绰����     �ҺŲ���    �������ȼ�   \n\n");
				for(i=1;i<idi;i++)
				{
					printf("           %d    %s    %c     %d     %s    %s     %d    %s    %d   \n\n",i,pt[i].name,pt[i].sex,pt[i].age,pt[i].xueli,pt[i].address,pt[i].telephone,pt[i].department,pt[i].priority);
				}
				printf("       ---------------------------------------------------------------------------------\n\n");
				break;
			}
			
			case 4:{
				printf("\n           ллʹ�ã��ټ���\n");
	
				break;
			}
			
			default:{
				printf("           ���������밴�˵�������롣\n");
			}		
		}	
	}
}




