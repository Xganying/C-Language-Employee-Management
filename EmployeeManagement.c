//��ҵԱ������ϵͳ
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee//����ṹ��
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

char password[9];//����ȫ�ֱ���
EMP *emp_first,*emp_end;
char gsave,gfirst;

void addemp();//�����Ӻ���
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


void addemp()//���Ա����Ϣ
{
	FILE *fp;
	EMP *emp1;
	int i=0;
	char choice='y';
	if((fp=fopen("employee.txt","ab"))==NULL)
	{
		printf("���ļ�employee.txt����!\n");
		getch();
		return;
	}
	do
	{
		i++;
		emp1=(EMP*)malloc(sizeof(EMP));
		if(emp1==NULL)
		{
			printf("�ڴ����ʧ��,�밴������˳�!\n");
			getch();
			return;
		}
		printf("\n\t�������%d��Ա������Ϣ\n",i);
		bound('_',40);
		printf("����:  ");
		scanf("%d",&emp1->num);
		printf("ְ��:  ");
		scanf("%s",&emp1->duty);
		printf("����:  ");
		scanf("%s",&emp1->name);
		printf("�Ա�:  ");
		scanf("%s",&emp1->sex);
		printf("����:  ");
		scanf("%d",&emp1->age);
		printf("�Ļ��̶�:  ");
		scanf("%s",&emp1->edu);
		printf("����:  ");
		scanf("%d",&emp1->salary);
		printf("�칫�绰:  ");
		scanf("%s",&emp1->tel_office);
		printf("��ͥ�绰:  ");
		scanf("%s",&emp1->tel_home);
		printf("�ֻ�����:  ");
		scanf("%s",&emp1->mobile);
		printf("QQ����:  ");
		scanf("%s",&emp1->qq);
		printf("��ͥ��ַ:  ");
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
		printf("\n�Ƿ��������?(y/n)  ");
		fflush(stdin);
		choice=getchar();
		if(toupper(choice)!='Y')
		{
			fclose(fp);
			printf("\n������ϣ��밴���������!\n");
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

void checkfirst()//�״�ʹ�ã������û���Ϣ��ʼ��
{
	FILE *fp,*fp1;
	char pwd[9],pwd1[9],pwd2[9];
	int i;
	char strt='8';
	if((fp=fopen("employee.txt","rb"))==NULL)
	{
		printf("\n\t��ϵͳ���������Ӧ�ĳ�ʼ������!\n");  
		bound('_',50);
		getch();
		do
		{
			printf("\n�������룬�벻Ҫ����8λ:  ");
			for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
				putch('*');
			printf("\n����ȷ��һ������:  ");
			for(i=0;i<8&&(pwd1[i]=getch())!=13;i++)
				putch('*');
			pwd[i]='\0';
			pwd1[i]='\0';
			if(strcmp(pwd,pwd1)!=0)
				printf("\n\n�����������벻һ�£�����������: \n");
			else 
				break;
		}while(1);
		if((fp1=fopen("employee.txt","wb"))==NULL)
		{
			printf("\nϵͳ����ʧ�ܣ��밴������˳�!\n");
			getch();
			exit(1);
		}
		i=0;
		while(pwd[i])
		{
			pwd2[i]=(pwd[i]^strt);
			putw(pwd2[i],fp1);//������Ԫ�������ļ�����
			i++;
		}
		fclose(fp1);//�ر��ļ���
		printf("\nϵͳ��ʼ���ɹ����밴������˳��������½���!\n");
		getch();
		exit(1);
	}
	else 
	{
		i=0;
		while(!feof(fp)&&i<8)//�ж��Ƿ���������ļ�
			pwd[i++]=getw(fp)^strt;//���ļ����ж����ַ���������
		pwd[i]='\0';
		if(i>=8)
			i--;
		while(pwd[i]!=-1&&i>=0)
			i--;
		pwd[i]='\0';
		strcpy(password,pwd);
	}
}

void delemp()//ɾ��Ա����Ϣ
{
	int findok=0;
    EMP *emp1,*emp2;
	char name[10],choice;
	system("cls");
	printf("\n������Ҫɾ����Ա��������:  ");
	scanf("%s",name);
	emp1=emp_first;
	emp2=emp1;
	while(emp1)
	{
		if(strcmp(emp1->name,name)==0)
		{
			findok=1;
			system("cls");
			printf("\nԱ�� %s ����Ϣ����: \n  ",emp1->name);
			bound('_',40);
			printf("����: %d \n",emp1->num);
		    printf("ְ��: %s \n",emp1->duty);
		    printf("����: %s \n",emp1->name);
		    printf("�Ա�: %s \n",emp1->sex);
		    printf("����: %d \n",emp1->age);
	     	printf("�Ļ��̶�: %s \n",emp1->edu);
		    printf("����: %d\n",emp1->salary);
		    printf("�칫�绰: %s \n",emp1->tel_office);
		    printf("��ͥ�绰: %s \n",emp1->tel_home);
		    printf("�ֻ�����: %s \n",emp1->mobile);
		    printf("QQ����: %s \n",emp1->qq);
		    printf("��ͥ��ַ: %s \n",emp1->address);
			bound('_',40);
			printf("\nȷ��Ҫɾ����Ա����Ϣ?(y/n)  ");
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
			printf("\nû���ҵ�������: %s ����Ϣ!\n",name);
			getch();
		}
		return;
}

void displayemp(EMP *emp,char *filed,char *name)//��ʾԱ����Ϣ
{
	if(emp)
	{
		bound('_',40);
		printf("\n  %s : %s    ��Ϣ����: \n",filed,name);
		bound('_',40);
		printf("����: %d \n",emp->num);
		printf("ְ��: %s \n",emp->duty);
		printf("����: %s \n",emp->name);
		printf("�Ա�: %s \n",emp->sex);
		printf("����: %d \n",emp->age);
		printf("�Ļ��̶�: %s \n",emp->edu);
		printf("����: %d \n",emp->salary);
		printf("�칫�绰: %s \n",emp->tel_office);
		printf("��ͥ�绰: %s \n",emp->tel_home);
		printf("�ֻ�����: %s \n",emp->mobile);
		printf("QQ����: %s \n",emp->qq);
		printf("��ͥ��ַ: %s \n",emp->address);
		bound('_',40);
	}
	else
	{
	   bound('_',40);
	   printf("\n���Ͽ���û��%sΪ: %s��Ա��,������ȷ��!\n",filed,name);
	}
	return;
}
 
EMP *findname(char *name)//����������Ա����Ϣ
{
	EMP *emp1;
	emp1=emp_first;
	while(emp1)
	{
		if(strcmp(name,emp1->name)==0)//�Ƚ���������ֺ������м��ص������Ƿ���ͬ
			return emp1;
		emp1=emp1->next;
	}
	return NULL;
}

EMP *findnum(int num)//�����Ų�ѯ
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

EMP *findtelephone(char *name)//���绰�����ѯԱ����Ϣ
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

EMP *findqq(char *name)//��QQ�����ѯԱ����Ϣ
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

void findemp()//����Ա����Ϣ
{
	int choice,ret=0,num;
	char str[13];
	EMP *emp1;
	system("cls");
	do{
		printf("\n\t��ѯԱ����Ϣ:\n");
	    bound('_',30);
	    printf("\t1.��������ѯ\n");
	    printf("\t2.�����Ų�ѯ\n");
	    printf("\t3.���绰��ѯ\n");
	    printf("\t4.��QQ�Ų�ѯ\n");
	    printf("\t0.�������˵�\n");
	    bound('_',30);
	    printf("\n��ѡ��(0-4):  ");
 	    do
		{
		    fflush(stdin);
		    choice=getchar();
		    system("cls");
		    switch(choice)
			{
		        case '1':
			       printf("\n������Ҫ��ѯԱ��������:  ");
			       scanf("%s",str);
			       emp1=findname(str);
			       displayemp(emp1,"����",str);
			       getch();
			       break;
		        case '2':
			       printf("\n������Ҫ��ѯԱ���Ĺ���:  ");
			       scanf("%d",&num);
			       emp1=findnum(num);//�����Ӻ���
			       itoa(num,str,10);
			       displayemp(emp1,"����",str);
				   getch();
			       break;
		        case '3':
		        	printf("\n������Ҫ��ѯԱ���ĵ绰:  ");
			        scanf("%s",str);
			        emp1=findtelephone(str);
			        displayemp(emp1,"�绰",str);
		        	getch();
		        	break;
		        case '4':
			        printf("\n������Ҫ��ѯԱ����QQ��:  ");
			        scanf("%s",str);
		         	emp1=findqq(str);
			        displayemp(emp1,"QQ����",str);
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
	printf("\n\t���Ͽ��е�Ա����Ϣ�б�\n");
	bound('_',40);
	emp1=emp_first;
	while(emp1)
	{
		bound('_',40);
		printf("����: %d\n",emp1->num);
		printf("ְ��: %s\n",emp1->duty);
		printf("����: %s\n",emp1->name);
		printf("�Ա�: %s\n",emp1->sex);
		printf("����: %d\n",emp1->age);
		printf("�Ļ��̶�: %s\n",emp1->edu);
		printf("����: %d\n",emp1->salary);
		printf("�칫�绰: %s\n",emp1->tel_office);
		printf("��ͥ�绰: %s\n",emp1->tel_home);
		printf("�ֻ�����: %s\n",emp1->mobile);
		printf("QQ����: %s\n",emp1->qq);
		printf("��ͥ��ַ: %s\n",emp1->address);
		bound('_',40);
		emp1=emp1->next;
	}
	printf("\nԱ����Ϣ��ʾ���,��������˳�!\n");
	return;
}

void login()//����½����
{
	int i,n=3;
	char pwd[9];
	do
	{
		printf("�������½����:  ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		pwd[i]='\0';
	    if(strcmp(pwd,password))
		{
	    	printf("\n�������,����������!\n");
		    system("cls");//������������
		    n--;
		}
	    else 
		   break;
	}while(n>0);
	if(!n)
	{
		printf("��������3�δ������˳�!\n");
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
        printf("   *                 ��ӭ������ҵԱ������ϵͳ                  *\n"); 
	    printf("   *************************************************************\n");
	    printf("   *\t                 1.����Ա����Ϣ                        *\n");
    	printf("   *\t                 2.��ѯԱ����Ϣ                        *\n"); 
		printf("   *\t                 3.��ʾԱ����Ϣ                        *\n");
		printf("   *\t                 4.�޸�Ա����Ϣ                        *\n"); 
		printf("   *\t                 5.ɾ��Ա����Ϣ                        *\n");
		printf("   *\t                 6.ͳ��Ա����Ϣ                        *\n");
		printf("   *\t                 7.����ϵͳ����                        *\n");
		printf("   *\t                 0.�˳�ϵͳ                            *\n");
		printf("   *************************************************************\n");
		printf("\n  ��ѡ������Ҫ�Ĳ���(0-7):   ");
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
						 printf("\nϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ!\n");
						 getch();
                         break;
					 }
                   findemp();
				   getch();
				   break;
				case '3':
					if(gfirst)
					{
						printf("\nϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ!\n");
						getch();
						break;
					}
					listemp();
					getch();
					break; 
				case '4':
					if(gfirst)
					{
						printf("\nϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
						getch();
						break;
					}
					modifyemp();
					getch();
					break;
				case '5':
					if(gfirst)
					{
						printf("\nϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
						getch();
						break;
					}
					delemp();
					getch();
					break;
				case '6':
					if(gfirst)
					{
						printf("\nϵͳ��Ϣ����Ա����Ϣ���������Ա����Ϣ��\n");
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


int modi_salary(int salary)//�޸Ĺ���
{
	int newsalary;
	printf("ԭ���Ĺ�����Ϊ:  %d\n",salary);
	printf("�µĹ�����:  ");
	scanf("%d",&newsalary);
	return newsalary;
}

int modi_age(int age)//�޸�����
{
	int newage;
	printf("ԭ��������Ϊ: %d\n",age);
	printf("��������:  ");
	scanf("%d",&newage);
	return newage;
}

char *modi_field(char *field,char *content,int len)
{
	char *str;
	str=malloc(sizeof(char)*len);
	if(str==NULL)
	{
		printf("\n�ڴ����ʧ�ܣ���������˳�!\n");
		getch();
		return 0;
	}
	printf("ԭ��%sΪ:%s\n",field,content);
	printf("�޸�Ϊ(���ݲ�����%d���ַ�):  ",len);
	scanf("%s",str);
	return str;
}

void modifyemp()//�޸�Ա����Ϣ
{
	EMP *emp1;
	char name[10],*newcontent;
	int choice;
	printf("\n������Ҫ�޸���ϢԱ��������:  ");
    scanf("%s",&name);
	emp1=findname(name);
	displayemp(emp1,"����",name);
	if(emp1)
	{
		printf("\t1.�޸�ְ��          2.�޸�����\n");
		printf("\t3.�޸��Ļ��̶�      4.�޸Ĺ���\n");
		printf("\t5.�޸İ칫�ҵ绰    6.�޸ļ�ͥ�绰\n");
		printf("\t7.�޸��ֻ�����      8.�޸�QQ����\n");
		printf("\t9.�޸ļ�ͥסַ      0.����\n");
		bound('_',40);
		printf("��������Ҫ�޸ĵ���Ϣѡ��:  \n");
		do
		{			
			fflush(stdin);
			choice=getchar();
			switch(choice)
			{
			case '1':
				newcontent=modi_field("ְ��",emp1->duty,10);
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
				newcontent=modi_field("�Ļ��̶�",emp1->edu,10);
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
				newcontent=modi_field("�칫�ҵ绰",emp1->tel_office,13);
				if(newcontent!=NULL)
				{
					strcpy(emp1->tel_office,newcontent);
					free(newcontent);
				}
				break;
			case '6':
				newcontent=modi_field("��ͥ�绰",emp1->tel_home,13);
				if(newcontent!=NULL)
				{
					strcpy(emp1->tel_home,newcontent);
					free(newcontent);
				}
				break;
			case '7':
				newcontent=modi_field("�ֻ�����",emp1->mobile,12);
				if(newcontent!=NULL)
				{
					strcpy(emp1->mobile,newcontent);
					free(newcontent);
				}
				break;
			case '8':
				newcontent=modi_field("QQ����",emp1->qq,10);
				if(newcontent!=NULL)
				{
					strcpy(emp1->qq,newcontent);
					free(newcontent);
				}
				break;
			case '9':
				newcontent=modi_field("��ͥסַ",emp1->address,30);
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
		printf("\n��Ϣ�޸����,��������˳�!\n");
		}
    	return;
}

void readdata()//��ȡ����
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
			printf("�ڴ����ʧ��,��������˳�!\n");
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

void resetpwd()//������������
{
	char pwd[9],pwd1[9];
	int i;
	FILE *fp1;
	system("cls");
	printf("\n�����������: \n");
	for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
		putch('*');
	pwd[i]='\0';
	if(strcmp(password,pwd)!=0)
	{
		printf("\n��������밴������˳�!\n");
		getch();
		return;
	}
	do
	{
		printf("\n�������룬�벻Ҫ����8λ:  ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		printf("\n����ȷ��һ������:   ");
		for(i=0;i<8&&((pwd[i]=getch())!=13);i++)
			putch('*');
		pwd[i]='\0';
		pwd1[i]='\0';
		if(strcmp(pwd,pwd1)!=0)
			printf("\n�����������벻һ�£�����������!  \n\n");
		else 
			break;
	}while(1);
	if((fp1=fopen("employee.txt","wb"))==NULL)
	{
		printf("\nϵͳ����ʧ�ܣ��밴������˳�!\n");
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
	printf("\n�����޸ĳɹ����밴������˳��������½���!\n");
	getch();
	return;
}

void savedata()//��������
{
	FILE *fp;
	EMP *emp1;
	if(gsave==0)
		return;
	if((fp=fopen("employee.txt","w+"))==NULL)
	{
		printf("���ļ�employee.txtʧ��,��������˳�!\n");
		getch();
		return;
	}
	emp1=emp_first;
	while(emp1)
	{
		bound('_',40);
	    fprintf(fp,"����: %d\n",emp1->num);
		fprintf(fp,"ְ��: %s\n",emp1->duty);
		fprintf(fp,"����: %s\n",emp1->name);
		fprintf(fp,"�Ա�: %s\n",emp1->sex);
		fprintf(fp,"����: %d\n",emp1->age);
		fprintf(fp,"�����̶�: %s\n",emp1->edu);
		fprintf(fp,"����: %d\n",emp1->salary);
		fprintf(fp,"�칫�ҵ绰: %s\n",emp1->tel_office);
		fprintf(fp,"��ͥ�绰: %s\n",emp1->tel_home);
		fprintf(fp,"QQ����: %s\n",emp1->qq);
		fprintf(fp,"��ͥ��ַ: %s\n\n",emp1->address);
		emp1=emp1->next;
	}
	gsave=0;
	fclose(fp);
}

void summaryemp()//Ա����Ϣ��Ҫ
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
		 if((strcmp(strw,"ma")==0)||(strcmp(emp1->sex,"��")==0))
			 man++;
		 else 
			 woman++;
		 emp1=emp1->next;
	}
	printf("\n\t���¾������Ա����ͳ����Ϣ: \n");
	bound('_',60);
	printf("Ա������    ��Ա����     ŮԱ����    ��������\n ");
	printf("\n%d\t\t%d\t%5d\t\t%d\n",num ,man,woman,sum);
	bound('_',60);
	printf("��������˳�!\n");
	getch();
	return;
}

int main()//������
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

