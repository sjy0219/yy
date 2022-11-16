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
	QElemType data;  //病人的编号 
	struct QNode *next; //下一个病人编号的地址 
}QNode,*Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;

//创建一个空队列 
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

//插入元素e作为新的队尾元素 
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
	//确定是哪个优先级的病人并且入相应的队列
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
	//出队
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
	char xueli[10];  //学历
	char address[70];//住址
	int telephone;      //电话号码
	char department[70];     //部门
	int priority;
};

int main()  //主函数 
{
	LinkQueue q1,q2;  //分别表示低级和高级的病人队列 
	QElemType idi=1,ido=-1;  //分别表示入队和出队的病人的id 
	int menu=0; //分别为用户选择的菜单编号和病人看病的优先级别

	InitQueue(q1);
	InitQueue(q2); 
	struct PT pt[100];
	
	printf("\n\n"); 
	printf("       ---------------------------------------------------------------------------------\n\n");
	printf("       *********************************************************************************\n\n");
	printf("\n");
	printf("       **                      欢迎使用××医院排队系统                               **\n");
	printf("\n");  
	printf("       **                      1. 新的病人加入队列候诊                                **\n");
	printf("\n");
	printf("       **                      2. 医生根据优先级别为病人进行诊治                      **\n");
	printf("\n");
	printf("       **                      3. 打印病人的目录(只有管理员才可以哦)                  **\n");
	printf("\n");
	printf("       **                      4. 退出系统                                            **\n");
	printf("\n");
	printf("       *********************************************************************************\n\n");
	printf("       ---------------------------------------------------------------------------------\n\n");
	
	int i,k=0;  //i代表之后循环点的次数  k代表循环次数，本程序中，错误超过三次，会退出系统。
	char users[50],mima[30];  //定义用户名，密码 。
	

	while(1)
	{
		printf("       ---------------------------------------------------------------------------------\n\n");
		printf("           请按编号选择相应的操作：\n");
		printf("           "); 
		scanf("%d",&menu);
		
		switch(menu)
		{
			case 1:{
				printf("           新病人加入候诊队列\n");
				printf("\n\n");
				printf("           请登记病人的基本情况:\n\n\n");
				printf("           姓名  性别（男m女f）  年龄 学历 住址 电话号码 部门 病人的优先级\n");
			
				printf("           姓名: ");
				scanf("%s",&pt[idi].name);
//				fflush(stdin);     (功能是清除缓存)
				getchar(); 
				printf("           性别:(m/f)");
				scanf("%c",&pt[idi].sex);
				printf("           年龄： ");
				scanf("%d",&pt[idi].age);
				printf("           学历(博士/研究生/本科/大专/高中/初中/小学)： ");
				scanf("%s",pt[idi].xueli);
				printf("           家庭地址: ");
				scanf("%s",pt[idi].address);
				printf("           电话号码: ");
				scanf("%d",&pt[idi].telephone);
				printf("           挂号部门: ");
				scanf("%s",pt[idi].department);
				printf("           病情严重性（非常严重请输入1，否则输入2）： ");
				scanf("%d",&pt[idi].priority); 
				printf("\n");
				printf("           谢谢您的配合。挂号成功！请您耐心等待！\n"); 
				printf("           该病人的ID是：%d\n",idi);
				MyEnQueue(q1,q2,idi,pt[idi].priority);
				idi++;
				break;
			}
			
			case 2:{
				ido=MyDeQueue(q1,q2);
				if(ido!=-1)
				{
					printf("           当前被诊治的病人的id是：%d\n",ido);
				}
				else
				{
					printf("           无诊治病人，队列为空！");
				}
				break;
			} 
				
			case 3:{
				int i=1;
					for(i=0;i<3;i++)
	
					{
						getchar(); 
						printf("\n           请先登录，只有管理员才可以打印病人信息哦！");
						printf("\n\n           请输入用户名:"); 
						gets(users);
						
						printf("\n           请输入密码:");
						
						gets(mima);
						
						if((strcmp(users,"123")==0)&&(strcmp(mima,"123")==0))
						{
							printf("\n           您已经成功登录");
							printf("\n           请稍等");
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
							printf("\n       用户名或密码无效 请重新输入:\n");
						}
						
						if(k==3)
						{
							printf("\n       连续输入错误3次 将退出程序\n");
							Sleep(2000);
							exit(0);
						}
					}
					
					
				printf("           打印当前病人的目录：\n\n\n");
				printf("       ---------------------------------------------------------------------------------\n\n");
					printf("        序号    姓名   性别   年龄    学历    住址    电话号码     挂号部门    病情优先级   \n\n");
				for(i=1;i<idi;i++)
				{
					printf("           %d    %s    %c     %d     %s    %s     %d    %s    %d   \n\n",i,pt[i].name,pt[i].sex,pt[i].age,pt[i].xueli,pt[i].address,pt[i].telephone,pt[i].department,pt[i].priority);
				}
				printf("       ---------------------------------------------------------------------------------\n\n");
				break;
			}
			
			case 4:{
				printf("\n           谢谢使用，再见！\n");
	
				break;
			}
			
			default:{
				printf("           输入有误，请按菜单编号输入。\n");
			}		
		}	
	}
}




