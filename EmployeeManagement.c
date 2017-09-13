//企业员工管理系统
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee//定义结构体
{
	int num;
	char duty[10];
	char name[15];
	char sex[10];
	int age;
	char edu[10];
	int salary;
	char tel_office[13];
	char tel_home[13];
	char mobile[13];
	char qq[12];
	char address[31];
	struct employee *next;
}EMP;

char password[9];//定义全局变量
EMP *emp_first,*emp_end;
char gsave,gfirst;

void addemp();//声明子函数
void findemp();
void listemp();
void modifyemp();
void summaryemp();
void delemp();
void resetpwd();
void resdata();
void savedata();
int modi_age(int age);
int modi_salary(int salary);
char *modi_filed(char *field,char *content,int len);
EMP *findname(char *name);
EMP *findnum(int num);
EMP *findtelephone(char *name);
EMP *findqq(char *name);
void displayemp(EMP *emp,char *field,char *name);
void checkfirst();
void bound(char ch,int n);
void login();
void menu();


void addemp()//添加员工信息
{
	FILE *fp;
	EMP *emp1;
	int i=0;
	char choice='y';
	if((fp=fopen("employee.txt","ab"))==NULL)
	{
		printf("打开文件employee.txt出错!\n");
		getch();
		return;
	}
	do
	{
		i++;
		emp1=(EMP*)malloc(sizeof(EMP));
		if(emp1==NULL)
		{
			printf("内存分配失败,请按任意键退出!\n");
			getch();
			return;
		}
		printf("\n\t请输入第%d各员工的信息\n",i);
		bound('_',40);
		printf("工号:  ");
		scanf("%d",&emp1->num);
		printf("职务:  ");
		scanf("%s",&emp1->duty);
		printf("姓名:  ");
		scanf("%s",&emp1->name);
		printf("性别:  ");
		scanf("%s",&emp1->sex);
		printf("年龄:  ");
		scanf("%d",&emp1->age);
		printf("文化程度:  ");
		scanf("%s",&emp1->edu);
		printf("工资:  ");
		scanf("%d",&emp1->salary);
		printf("办公电话:  ");
		scanf("%s",&emp1->tel_office);
		printf("家庭电话:  ");
		scanf("%s",&emp1->tel_home);
		printf("手机号码:  ");
		scanf("%s",&emp1->mobile);
		printf("QQ号码:  ");
		scanf("%s",&emp1->qq);
		printf("家庭地址:  ");
		scanf("%s",&emp1->address);
		emp1->next=NULL;
		if(emp_first==NULL)
		{
			emp_first=emp1;
			emp_end=emp1;
		}
		else
		{
			emp_end->next=emp1;
			emp_end=emp1;
		}
		fwrite(emp_end,sizeof(EMP),1,fp);
		gfirst=0;
		printf("\n");
		bound('_',40);
		printf("\n是否继续输入?(y/n)  ");
		fflush(stdin);
		choice=getchar();
		if(toupper(choice)!='Y')
		{
			fclose(fp);
			printf("\n输入完毕，请按任意键返回!\n");
			getch();
			return;
		}
		system("cls");
	}while(1);
}

void bound(char ch,int n)
{
    while(n--)
		putch(ch);
	printf("\n");
	return;
}

void checkfirst()//首次使用，进行用户信息初始化
{
	FILE *fp,*fp1;
	char pwd[9],pwd1[9],pwd2[9];
	int i;
	char strt='8';
	if((fp=fopen("employee.txt","rb"))==NULL)
	{
		printf("\n\t新系统，请进行相应的初始化操作!\n");  
		bound('_',50);
		getch();
		do
		{
			printf("\n设置密码，请不要超过8位:  ");
			for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
				putch('*');
			printf("\n请再确认一次密码:  ");
			for(i=0;i<8&&(pwd1[i]=getch())!=13;i++)
				putch('*');
			pwd[i]='\0';
			pwd1[i]='\0';
			if(strcmp(pwd,pwd1)!=0)
				printf("\n\n两次密码输入不一致，请重新输入: \n");
			else 
				break;
		}while(1);
		if((fp1=fopen("employee.txt","wb"))==NULL)
		{
			printf("\n系统创建失败，请按任意键退出!\n");
			getch();
			exit(1);
		}
		i=0;
		while(pwd[i])
		{
			pwd2[i]=(pwd[i]^strt);
			putw(pwd2[i],fp1);//将数组元素送入文件流中
			i++;
		}
		fclose(fp1);//关闭文件流
		printf("\n系统初始化成功，请按任意键退出后，再重新进入!\n");
		getch();
		exit(1);
	}
	else 
	{
		i=0;
		while(!feof(fp)&&i<8)//判断是否读完密码文件
			pwd[i++]=getw(fp)^strt;//从文件流中读出字符赋给数组
		pwd[i]='\0';
		if(i>=8)
			i--;
		while(pwd[i]!=-1&&i>=0)
			i--;
		pwd[i]='\0';
		strcpy(password,pwd);
	}
}

void delemp()//删除员工信息
{
	int findok=0;
    EMP *emp1,*emp2;
	char name[10],choice;
	system("cls");
	printf("\n请输入要删除的员工的姓名:  ");
	scanf("%s",name);
	emp1=emp_first;
	emp2=emp1;
	while(emp1)
	{
		if(strcmp(emp1->name,name)==0)
		{
			findok=1;
			system("cls");
			printf("\n员工 %s 的信息如下: \n  ",emp1->name);
			bound('_',40);
			printf("工号: %d \n",emp1->num);
		    printf("职务: %s \n",emp1->duty);
		    printf("姓名: %s \n",emp1->name);
		    printf("性别: %s \n",emp1->sex);
		    printf("年龄: %d \n",emp1->age);
	     	printf("文化程度: %s \n",emp1->edu);
		    printf("工资: %d\n",emp1->salary);
		    printf("办公电话: %s \n",emp1->tel_office);
		    printf("家庭电话: %s \n",emp1->tel_home);
		    printf("手机号码: %s \n",emp1->mobile);
		    printf("QQ号码: %s \n",emp1->qq);
		    printf("家庭地址: %s \n",emp1->address);
			bound('_',40);
			printf("\n确定要删除该员工信息?(y/n)  ");
			fflush(stdin);
			choice=getchar();
			if(choice!='y'&&choice!='Y')
				return;
			if(emp1==emp_first)
				emp_first=emp1->next;
			else 
				emp2->next=emp1->next;
			free(emp1);
			gsave=1;
			savedata();
			return;
		}
		else
		{
			emp2=emp1;
			emp1=emp1->next;
		}
	}
		if(!findok)
		{
			bound('_',40);
			printf("\n没有找到姓名是: %s 的信息!\n",name);
			getch();
		}
		return;
}

void displayemp(EMP *emp,char *filed,char *name)//显示员工信息
{
	if(emp)
	{
		bound('_',40);
		printf("\n  %s : %s    信息如下: \n",filed,name);
		bound('_',40);
		printf("工号: %d \n",emp->num);
		printf("职务: %s \n",emp->duty);
		printf("姓名: %s \n",emp->name);
		printf("性别: %s \n",emp->sex);
		printf("年龄: %d \n",emp->age);
		printf("文化程度: %s \n",emp->edu);
		printf("工资: %d \n",emp->salary);
		printf("办公电话: %s \n",emp->tel_office);
		printf("家庭电话: %s \n",emp->tel_home);
		printf("手机号码: %s \n",emp->mobile);
		printf("QQ号码: %s \n",emp->qq);
		printf("家庭地址: %s \n",emp->address);
		bound('_',40);
	}
	else
	{
	   bound('_',40);
	   printf("\n资料库中没有%s为: %s的员工,请重新确认!\n",filed,name);
	}
	return;
}
 
EMP *findname(char *name)//按姓名查找员工信息
{
	EMP *emp1;
	emp1=emp_first;
	while(emp1)
	{
		if(strcmp(name,emp1->name)==0)//比较输入的名字和链表中记载的名字是否相同
			return emp1;
		emp1=emp1->next;
	}
	return NULL;
}

EMP *findnum(int num)//按工号查询
{
	EMP *emp1;
	emp1=emp_first;
	while(emp1)
	{
		if(num==emp1->num)
			return emp1;
		emp1=emp1->next;
	}
	return NULL;
}

EMP *findtelephone(char *name)//按电话号码查询员工信息
{
	EMP *emp1;
	emp1=emp_first;
	while(emp1)
	{
		if(strcmp(name,emp1->tel_office)==0||strcmp(name,emp1->tel_home)==0||strcmp(name,emp1->mobile)==0)
			return emp1;
		emp1=emp1->next;
	}
    return NULL;
}

EMP *findqq(char *name)//按QQ号码查询员工信息
{
	EMP *emp1;
	emp1=emp_first;
	while(emp1)
	{
		if(strcmp(name,emp1->qq)==0)
			return emp1;
		emp1=emp1->next;
	}
    return NULL;
}

void findemp()//查找员工信息
{
	int choice,ret=0,num;
	char str[13];
	EMP *emp1;
	system("cls");
	do{
		printf("\n\t查询员工信息:\n");
	    bound('_',30);
	    printf("\t1.按姓名查询\n");
	    printf("\t2.按工号查询\n");
	    printf("\t3.按电话查询\n");
	    printf("\t4.按QQ号查询\n");
	    printf("\t0.返回主菜单\n");
	    bound('_',30);
	    printf("\n请选择(0-4):  ");
 	    do
		{
		    fflush(stdin);
		    choice=getchar();
		    system("cls");
		    switch(choice)
			{
		        case '1':
			       printf("\n请输入要查询员工的姓名:  ");
			       scanf("%s",str);
			       emp1=findname(str);
			       displayemp(emp1,"姓名",str);
			       getch();
			       break;
		        case '2':
			       printf("\n请输入要查询员工的工号:  ");
			       scanf("%d",&num);
			       emp1=findnum(num);//调用子函数
			       itoa(num,str,10);
			       displayemp(emp1,"工号",str);
				   getch();
			       break;
		        case '3':
		        	printf("\n请输入要查询员工的电话:  ");
			        scanf("%s",str);
			        emp1=findtelephone(str);
			        displayemp(emp1,"电话",str);
		        	getch();
		        	break;
		        case '4':
			        printf("\n请输入要查询员工的QQ号:  ");
			        scanf("%s",str);
		         	emp1=findqq(str);
			        displayemp(emp1,"QQ号码",str);
			        getch();
		        	break;
		        case '0':
		        	ret=1;
			        break;
			}
		}while(choice<'0'||choice>'4');
    	system("cls");
    	if(ret)
		     break;
	}while(1);
}

void listemp()
{
	EMP *emp1;
	printf("\n\t资料库中的员工信息列表\n");
	bound('_',40);
	emp1=emp_first;
	while(emp1)
	{
		bound('_',40);
		printf("工号: %d\n",emp1->num);
		printf("职务: %s\n",emp1->duty);
		printf("姓名: %s\n",emp1->name);
		printf("性别: %s\n",emp1->sex);
		printf("年龄: %d\n",emp1->age);
		printf("文化程度: %s\n",emp1->edu);
		printf("工资: %d\n",emp1->salary);
		printf("办公电话: %s\n",emp1->tel_office);
		printf("家庭电话: %s\n",emp1->tel_home);
		printf("手机号码: %s\n",emp1->mobile);
		printf("QQ号码: %s\n",emp1->qq);
		printf("家庭地址: %s\n",emp1->address);
		bound('_',40);
		emp1=emp1->next;
	}
	printf("\n员工信息显示完毕,按任意键退出!\n");
	return;
}

void login()//检测登陆密码
{
	int i,n=3;
	char pwd[9];
	do
	{
		printf("请输入登陆密码:  ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		pwd[i]='\0';
	    if(strcmp(pwd,password))
		{
	    	printf("\n密码错误,请重新输入!\n");
		    system("cls");//调用清屏命令
		    n--;
		}
	    else 
		   break;
	}while(n>0);
	if(!n)
	{
		printf("密码输入3次错误，请退出!\n");
		getch();
		exit(1);
	}
}

void menu()
{
	char choice;
	system("cls");
	do
	{ 
		printf("\n\n\n\n   *************************************************************\n");
        printf("   *                 欢迎进入企业员工管理系统                  *\n"); 
	    printf("   *************************************************************\n");
	    printf("   *\t                 1.输入员工信息                        *\n");
    	printf("   *\t                 2.查询员工信息                        *\n"); 
		printf("   *\t                 3.显示员工信息                        *\n");
		printf("   *\t                 4.修改员工信息                        *\n"); 
		printf("   *\t                 5.删除员工信息                        *\n");
		printf("   *\t                 6.统计员工信息                        *\n");
		printf("   *\t                 7.重置系统密码                        *\n");
		printf("   *\t                 0.退出系统                            *\n");
		printf("   *************************************************************\n");
		printf("\n  请选择您需要的操作(0-7):   ");
		do{
			 fflush(stdin);
			 choice=getchar();
			 system("cls");
			 switch(choice)
			 {
			    case '1':
					addemp();
					getch();
					break;
                 case '2':
					 if(gfirst)
					 {
						 printf("\n系统信息中无员工信息，请先添加员工信息!\n");
						 getch();
                         break;
					 }
                   findemp();
				   getch();
				   break;
				case '3':
					if(gfirst)
					{
						printf("\n系统信息中无员工信息，请先添加员工信息!\n");
						getch();
						break;
					}
					listemp();
					getch();
					break; 
				case '4':
					if(gfirst)
					{
						printf("\n系统信息中无员工信息，请先添加员工信息！\n");
						getch();
						break;
					}
					modifyemp();
					getch();
					break;
				case '5':
					if(gfirst)
					{
						printf("\n系统信息中无员工信息，请先添加员工信息！\n");
						getch();
						break;
					}
					delemp();
					getch();
					break;
				case '6':
					if(gfirst)
					{
						printf("\n系统信息中无员工信息，请先添加员工信息！\n");
						getch();
						break;
					}
					summaryemp();
					getch();
					break;
				case '7':
					resetpwd();
					getch();
					break;
				case '0':
					savedata();
					exit(1);
			 }
		}while(choice<'0'||choice>'7');
		system("cls");
	}while(1);
}


int modi_salary(int salary)//修改工资
{
	int newsalary;
	printf("原来的工资数为:  %d\n",salary);
	printf("新的工资数:  ");
	scanf("%d",&newsalary);
	return newsalary;
}

int modi_age(int age)//修改年龄
{
	int newage;
	printf("原来的年龄为: %d\n",age);
	printf("现在年龄:  ");
	scanf("%d",&newage);
	return newage;
}

char *modi_field(char *field,char *content,int len)
{
	char *str;
	str=malloc(sizeof(char)*len);
	if(str==NULL)
	{
		printf("\n内存分配失败，按任意键退出!\n");
		getch();
		return 0;
	}
	printf("原来%s为:%s\n",field,content);
	printf("修改为(内容不超过%d个字符):  ",len);
	scanf("%s",str);
	return str;
}

void modifyemp()//修改员工信息
{
	EMP *emp1;
	char name[10],*newcontent;
	int choice;
	printf("\n请输入要修改信息员工的姓名:  ");
    scanf("%s",&name);
	emp1=findname(name);
	displayemp(emp1,"姓名",name);
	if(emp1)
	{
		printf("\t1.修改职务          2.修改年龄\n");
		printf("\t3.修改文化程度      4.修改工资\n");
		printf("\t5.修改办公室电话    6.修改家庭电话\n");
		printf("\t7.修改手机号码      8.修改QQ号码\n");
		printf("\t9.修改家庭住址      0.返回\n");
		bound('_',40);
		printf("请输入你要修改的信息选项:  \n");
		do
		{			
			fflush(stdin);
			choice=getchar();
			switch(choice)
			{
			case '1':
				newcontent=modi_field("职务",emp1->duty,10);
				if(newcontent!=NULL)
				{
					strcpy(emp1->duty,newcontent);
					free(newcontent);
				}
				break;
			case '2':
				emp1->age=modi_age(emp1->age);
				break;
			case '3':
				newcontent=modi_field("文化程度",emp1->edu,10);
				if(newcontent!=NULL)
				{
					strcpy(emp1->edu,newcontent);
					free(newcontent);
				}
				break;
			case '4':
				emp1->salary=modi_salary(emp1->salary);
				break;
			case '5':
				newcontent=modi_field("办公室电话",emp1->tel_office,13);
				if(newcontent!=NULL)
				{
					strcpy(emp1->tel_office,newcontent);
					free(newcontent);
				}
				break;
			case '6':
				newcontent=modi_field("家庭电话",emp1->tel_home,13);
				if(newcontent!=NULL)
				{
					strcpy(emp1->tel_home,newcontent);
					free(newcontent);
				}
				break;
			case '7':
				newcontent=modi_field("手机号码",emp1->mobile,12);
				if(newcontent!=NULL)
				{
					strcpy(emp1->mobile,newcontent);
					free(newcontent);
				}
				break;
			case '8':
				newcontent=modi_field("QQ号码",emp1->qq,10);
				if(newcontent!=NULL)
				{
					strcpy(emp1->qq,newcontent);
					free(newcontent);
				}
				break;
			case '9':
				newcontent=modi_field("家庭住址",emp1->address,30);
				if(newcontent!=NULL)
				{
					strcpy(emp1->address,newcontent);
					free(newcontent);
				}
				break;
			case '0':
				getch();
				return;
			}
		}while(choice<'0'||choice>'9');
		gsave=1;
		savedata();
		printf("\n信息修改完毕,按任意键退出!\n");
		}
    	return;
}

void readdata()//读取数据
{
	FILE *fp;
	EMP *emp1;
	if((fp=fopen("employee.txt","rb"))==NULL)
	{
		gfirst=1;
		return;
	}
	while(!feof(fp))
	{
		emp1=(EMP *)malloc(sizeof(EMP));
		if(emp1==NULL)
		{
			printf("内存非配失败,按任意键退出!\n");
			getch();
			return;
		}
		fread(emp1,sizeof(EMP),1,fp);
		if(feof(fp))
			break;
		if(emp_first==NULL)
		{
			emp_first=emp1;
			emp_end=emp1;
		}
		else
		{
			emp_end->next=emp1;
			emp_end=emp1;
		}
		emp_end->next=NULL;
	}
	gfirst=0;
	fclose(fp);
}

void resetpwd()//重新设置密码
{
	char pwd[9],pwd1[9];
	int i;
	FILE *fp1;
	system("cls");
	printf("\n请输入旧密码: \n");
	for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
		putch('*');
	pwd[i]='\0';
	if(strcmp(password,pwd)!=0)
	{
		printf("\n密码错误，请按任意键退出!\n");
		getch();
		return;
	}
	do
	{
		printf("\n设置密码，请不要超过8位:  ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		printf("\n请再确认一次密码:   ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		pwd[i]='\0';
		pwd1[i]='\0';
		if(strcmp(pwd,pwd1)!=0)
			printf("\n两次密码输入不一致，请重新输入!  \n\n");
		else 
			break;
	}while(1);
	if((fp1=fopen("employee.txt","wb"))==NULL)
	{
		printf("\n系统创建失败，请按任意键退出!\n");
		getch();
		exit(1);
	}
	i=0;
	while(pwd[i])
	{
		putw(pwd[i],fp1);
    	i++;
	}
	fclose(fp1);
	printf("\n密码修改成功，请按任意键退出后，再重新进入!\n");
	getch();
	return;
}

void savedata()//保存数据
{
	FILE *fp;
	EMP *emp1;
	if(gsave==0)
		return;
	if((fp=fopen("employee.txt","w+"))==NULL)
	{
		printf("打开文件employee.txt失败,按任意键退出!\n");
		getch();
		return;
	}
	emp1=emp_first;
	while(emp1)
	{
		bound('_',40);
	    fprintf(fp,"工号: %d\n",emp1->num);
		fprintf(fp,"职务: %s\n",emp1->duty);
		fprintf(fp,"姓名: %s\n",emp1->name);
		fprintf(fp,"性别: %s\n",emp1->sex);
		fprintf(fp,"年龄: %d\n",emp1->age);
		fprintf(fp,"教育程度: %s\n",emp1->edu);
		fprintf(fp,"工资: %d\n",emp1->salary);
		fprintf(fp,"办公室电话: %s\n",emp1->tel_office);
		fprintf(fp,"家庭电话: %s\n",emp1->tel_home);
		fprintf(fp,"QQ号码: %s\n",emp1->qq);
		fprintf(fp,"家庭地址: %s\n\n",emp1->address);
		emp1=emp1->next;
	}
	gsave=0;
	fclose(fp);
}

void summaryemp()//员工信息概要
{
	EMP *emp1;
	int sum=0,num=0,man=0,woman=0;
	emp1=emp_first;
	while(emp1)
	{
		 char strw[2];
		 num++;
		 sum+=emp1->salary;
		 strncpy(strw,emp1->sex,2);
		 if((strcmp(strw,"ma")==0)||(strcmp(emp1->sex,"男")==0))
			 man++;
		 else 
			 woman++;
		 emp1=emp1->next;
	}
	printf("\n\t以下就是相关员工的统计信息: \n");
	bound('_',60);
	printf("员工总数    男员工数     女员工数    工资总数\n ");
	printf("\n%d\t\t%d\t%5d\t\t%d\n",num ,man,woman,sum);
	bound('_',60);
	printf("按任意键退出!\n");
	getch();
	return;
}

int main()//主函数
{
	emp_first=emp_end=NULL;
	gsave=gfirst=0;
	checkfirst();
	login();
	readdata();
	menu();
	system("PAUSE");
	return 0;
}

