#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM 10	//��10��ѡ��

struct Member_information	//ѡ����Ϣ
{
	int num;		//���
	char name[16];	//����
	float score_o[10];	//ԭʼ���� 10��
	float score;	//ƽ������
}member[MEM];

int i,j;

void input_information()	//����ÿһ��ѡ�ֵ���Ϣ
{
	int flag;
	for (i=0;i<MEM;i++)
	{
		flag=1;
		while(flag)
		{
			flag=0;
			printf("\n������ѡ�ֵı��: ");
			scanf("%d",&member[i].num);
			getchar();
			for (j=i-1;j>=0;j--)	//��������ͬ���,Ҫ����������
			{
				if (i != 0 && member[i].num == member[j].num)
				{
					printf("�˱���Ѵ���,����������\n");
					flag=1;
				}
			}
		}
		printf("������%d��ѡ�ֵ�����: ",member[i].num);
		gets(member[i].name);
		for (j=0;j<10;j++)
		{
			printf("��%2d�����еĴ��: ",j+1);
			scanf("%f",&member[i].score_o[j]);
		}
		getchar();
	}
	system("cls");
	printf("\n-------����¼�����-------\n");
}

void sort_num()	//�����д�ķ�����ѡ�� ��С��������
{
	int k;
	float temp;
	for (i=0;i<MEM;i++)
	{
		for (j=0;j<10;j++)
		{
			temp=member[i].score_o[j];
			for (k=j+1;k<10;k++)
			{
				if (member[i].score_o[j] > member[i].score_o[k])
				{
					temp=member[i].score_o[j];
					member[i].score_o[j]=member[i].score_o[k];
					member[i].score_o[k]=temp;
				}
			}
		}//�ڲ�ѭ�� ����
	}//���ѭ�� ѡ��
}

void average_score()	//�õ����յ÷�
//�Գ�һ����߷ֺ�һ����ͷ�֮��ķ��� ��ƽ��ֵ
{
	float sum;
	for (i=0;i<MEM;i++)
	{
		sum=0;
		for (j=1;j<9;j++)
			sum=sum+member[i].score_o[j];
		member[i].score=sum/8;
	}
}

void sort_grade()	//��ƽ���ɼ��ɴ�С����
{
	struct Member_information temp;
	for (i=0;i<MEM;i++)
	{
		temp=member[i];
		for (j=i+1;j<MEM;j++)
		{
			if (member[i].score < member[j].score)
			{
				temp=member[i];
				member[i]=member[j];
				member[j]=temp;
			}
		}//�ڲ�ѭ�� ����
	}//���ѭ�� ѡ��
}

void print_information(int num)	//���һ����Ա��Ϣ,numΪ��Ա�����±�,��:����-1
{
	printf("\t--��%d��--\n",num+1);
	printf("\t���:%2d\n",member[num].num);
	printf("\t����:%s\n",member[num].name);
	printf("\t�ɼ�:%4.2f\n",member[num].score);
}

void print_name(char name[20])	//����������ѯ���� ��� �ɼ�
{
	for (i=0;i<MEM;i++)
	{
		if (! strcmp(name,member[i].name))
		{
			print_information(i);
			return;
		}
	}
	printf("\aError! δ�ҵ���ѡ����Ϣ!\n");
}

void print_grade(int grade)	//��������������� ��� �ɼ�
{
	grade--;
	if (grade >= MEM)
	{
		printf("\aError! δ�ҵ���ѡ����Ϣ!\n");
		return;
	}
	print_information(grade);
}

int print_num(int num)	//���ݱ��������� ���� �ɼ�
{
	for (i=0;i<MEM;i++)
	{
		if (num == member[i].num)
		{
			print_information(i);
			return 0;
		}
	}
	printf("\aError! δ�ҵ���ѡ����Ϣ!\n");
	return 1;
}

void edit_menu()	//�޸���Ϣ�Ĳ˵�
{
	printf("\n=================\n");
	printf("|��1��.�޸�����\t|\n|��2��.�޸ĳɼ�\t|\n|��3��.�˳��޸�\t|");
	printf("\n=================\n");
}

void edit()	//�޸����������Ϣ
{
	int temp,number;
	printf("������Ҫ�޸ĵı��: ");
	scanf("%d",&number);
	if (print_num(number))	//�ж�Ҫ�޸ĵı���Ƿ����
		return;
	edit_menu();
	for (i=0;i<MEM;i++)
	{
		if (number == member[i].num)
			break;
	}
	printf("����������ѡ��");
	scanf("%d",&temp);
	getchar();
	switch(temp)
	{
		case 1:
			printf("�������޸ĺ������:");
			gets(member[i].name);
			break;
		case 2:
			for (j=0;j<10;j++)
			{
				printf("��%2d�����еĴ��: ",j+1);
				scanf("%f",&member[i].score_o[j]);
			}
			getchar();
			sort_num();
			average_score();
			sort_grade();
			break;
		case 3:
			break;
		default:
			printf("\a��������ȷ�ı��!\n");
	}
	system("cls");
	printf("\n-------��Ϣ�޸����-------\n");
}

void print_result()	//���ȫ��ѡ�ֵ����� ��� ���� ����
{
	printf("=========================================================================================");
	printf("\n|����\t");
	for (i=0;i<MEM;i++)
	{
		printf("%d\t",i+1);
	}
	printf("|\n|���\t");
	for (i=0;i<MEM;i++)
	{
		printf("%d\t",member[i].num);
	}
	printf("|\n|����\t");
	for (i=0;i<MEM;i++)
	{
		printf("%s\t",member[i].name);
	}
	printf("|\n|����\t");
	for (i=0;i<MEM;i++)
	{
		printf("%4.2f\t",member[i].score);
	}
	printf("|\n=========================================================================================");
}

void print_menu()
{
	printf("\n=========================\n");
	printf("|   -=�質��������=-    |\n");
	printf("|��0��.������ʾ�˵�\t|\n|��1��.����������ѯ\t|\n|��2��.���ݱ�Ų�ѯ\t|\n|��3��.�������β�ѯ\t|\n");
	printf("|��4��.�鿴����ȫ�����\t|\n|��5��.������������\t|\n|��6��.�༭�����������\t|\n|��7��.�˳��ó���\t|");
	printf("\n=========================\n");
}

void input_all()	//�������
{
	void menu(void);
	printf("����ÿ��ѡ�ֵ������Ϣ:\n�����Լ�ʮ�����д���ķ���\n");
	input_information();
	sort_num();
	average_score();
	sort_grade();	//���ݴ������
}

void menu()	//�����˵�
{
	int choice,temp,flag=1;
	char name[20];
	while(flag)
	{
		print_menu();
		printf("\n����������ѡ��:[   ]\b\b\b");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
			case 0:
				system("cls");
				break;
			case 1:
				system("cls");
				printf("����������:\n");
				gets(name);
				print_name(name);
				break;
			case 2:
				system("cls");
				printf("��������:\n");
				scanf("%d",&temp);
				print_num(temp);
				break;
			case 3:
				system("cls");
				printf("����������:\n");
				scanf("%d",&temp);
				print_grade(temp);
				break;
			case 4:
				system("cls");
				print_result();
				break;
			case 5:
				system("cls");
				input_all();
				break;
			case 6:
				system("cls");
				edit();
				break;
			case 7:
				flag=0;
				break;
			default:
				printf("\aError! ��������ȷ������!");
				continue;
		}
	}//ѭ������
}

int file_read()	//��ȡ�ļ�
{
	FILE *fp;
	if ((fp = fopen("data.txt","rb")) == NULL)
	{
		if ((fp = fopen("data.txt","wb")) == NULL)
		{	//���ļ�������,�����ļ�
			printf("���ļ�ʧ��!\n");
			exit(EXIT_FAILURE);
		}
		fclose(fp);
		return 1;
	}
	fread(member,sizeof(struct Member_information),10,fp);	//���ļ������ݶ�ȡ���ṹ����
	fclose(fp);
	return 0;
}

void file_write()	//д�����ļ�
{
	FILE *fp;
	if ((fp = fopen("data.txt","wb")) == NULL)
	{
		printf("���ļ�ʧ��!\n");
		exit(EXIT_FAILURE);
	}
	fwrite(member,sizeof(struct Member_information),10,fp);	//���ṹ���е�����д���ļ�
	fclose(fp);
}

int main()
{	
	printf("   -=�質��������=-    \n");
	printf("���ڶ�ȡ�ļ�...\n");
	if (file_read())	//���ļ�������,�����ļ�
	{
		printf("�ļ������ɹ�,����������\n\n");
		input_all();
	}
	else	//���ļ�����,��������,ֱ����ʾ�˵�
	{
		printf("�ļ��Ѵ���,��ֱ�Ӳ�ѯ����\n");
	}
	menu();
	file_write();	//��������ǰ�����ݱ��浽�ļ�
	return 0;
}