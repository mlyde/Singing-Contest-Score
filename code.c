#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEM 10	//有10名选手

struct Member_information	//选手信息
{
	int num;		//编号
	char name[16];	//姓名
	float score_o[10];	//原始分数 10个
	float score;	//平均分数
}member[MEM];

int i,j;

void input_information()	//输入每一个选手的信息
{
	int flag;
	for (i=0;i<MEM;i++)
	{
		flag=1;
		while(flag)
		{
			flag=0;
			printf("\n请输入选手的编号: ");
			scanf("%d",&member[i].num);
			getchar();
			for (j=i-1;j>=0;j--)	//若存在相同编号,要求重新输入
			{
				if (i != 0 && member[i].num == member[j].num)
				{
					printf("此编号已存在,请重新输入\n");
					flag=1;
				}
			}
		}
		printf("请输入%d号选手的姓名: ",member[i].num);
		gets(member[i].name);
		for (j=0;j<10;j++)
		{
			printf("第%2d个裁判的打分: ",j+1);
			scanf("%f",&member[i].score_o[j]);
		}
		getchar();
	}
	system("cls");
	printf("\n-------数据录入完毕-------\n");
}

void sort_num()	//将裁判打的分数用选择法 由小到大排序
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
		}//内层循环 分数
	}//外层循环 选手
}

void average_score()	//得到最终得分
//对除一个最高分和一个最低分之外的分数 求平均值
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

void sort_grade()	//将平均成绩由大到小排序
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
		}//内层循环 分数
	}//外层循环 选手
}

void print_information(int num)	//输出一个成员信息,num为成员数组下标,即:名次-1
{
	printf("\t--第%d名--\n",num+1);
	printf("\t编号:%2d\n",member[num].num);
	printf("\t姓名:%s\n",member[num].name);
	printf("\t成绩:%4.2f\n",member[num].score);
}

void print_name(char name[20])	//根据姓名查询名次 编号 成绩
{
	for (i=0;i<MEM;i++)
	{
		if (! strcmp(name,member[i].name))
		{
			print_information(i);
			return;
		}
	}
	printf("\aError! 未找到该选手信息!\n");
}

void print_grade(int grade)	//根据名次输出姓名 编号 成绩
{
	grade--;
	if (grade >= MEM)
	{
		printf("\aError! 未找到该选手信息!\n");
		return;
	}
	print_information(grade);
}

int print_num(int num)	//根据编号输出姓名 名次 成绩
{
	for (i=0;i<MEM;i++)
	{
		if (num == member[i].num)
		{
			print_information(i);
			return 0;
		}
	}
	printf("\aError! 未找到该选手信息!\n");
	return 1;
}

void edit_menu()	//修改信息的菜单
{
	printf("\n=================\n");
	printf("|【1】.修改姓名\t|\n|【2】.修改成绩\t|\n|【3】.退出修改\t|");
	printf("\n=================\n");
}

void edit()	//修改已输入的信息
{
	int temp,number;
	printf("请输入要修改的编号: ");
	scanf("%d",&number);
	if (print_num(number))	//判断要修改的编号是否存在
		return;
	edit_menu();
	for (i=0;i<MEM;i++)
	{
		if (number == member[i].num)
			break;
	}
	printf("请输入数字选择：");
	scanf("%d",&temp);
	getchar();
	switch(temp)
	{
		case 1:
			printf("请输入修改后的姓名:");
			gets(member[i].name);
			break;
		case 2:
			for (j=0;j<10;j++)
			{
				printf("第%2d个裁判的打分: ",j+1);
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
			printf("\a请输入正确的编号!\n");
	}
	system("cls");
	printf("\n-------信息修改完毕-------\n");
}

void print_result()	//输出全部选手的名次 编号 姓名 分数
{
	printf("=========================================================================================");
	printf("\n|名次\t");
	for (i=0;i<MEM;i++)
	{
		printf("%d\t",i+1);
	}
	printf("|\n|编号\t");
	for (i=0;i<MEM;i++)
	{
		printf("%d\t",member[i].num);
	}
	printf("|\n|姓名\t");
	for (i=0;i<MEM;i++)
	{
		printf("%s\t",member[i].name);
	}
	printf("|\n|分数\t");
	for (i=0;i<MEM;i++)
	{
		printf("%4.2f\t",member[i].score);
	}
	printf("|\n=========================================================================================");
}

void print_menu()
{
	printf("\n=========================\n");
	printf("|   -=歌唱比赛评分=-    |\n");
	printf("|【0】.重新显示菜单\t|\n|【1】.根据姓名查询\t|\n|【2】.根据编号查询\t|\n|【3】.根据名次查询\t|\n");
	printf("|【4】.查看比赛全部结果\t|\n|【5】.重新输入数据\t|\n|【6】.编辑已输入的数据\t|\n|【7】.退出该程序\t|");
	printf("\n=========================\n");
}

void input_all()	//输入操作
{
	void menu(void);
	printf("输入每个选手的相关信息:\n姓名以及十个裁判打出的分数\n");
	input_information();
	sort_num();
	average_score();
	sort_grade();	//数据处理完成
}

void menu()	//操作菜单
{
	int choice,temp,flag=1;
	char name[20];
	while(flag)
	{
		print_menu();
		printf("\n请输入数字选择:[   ]\b\b\b");
		scanf("%d",&choice);
		getchar();
		switch(choice)
		{
			case 0:
				system("cls");
				break;
			case 1:
				system("cls");
				printf("请输入姓名:\n");
				gets(name);
				print_name(name);
				break;
			case 2:
				system("cls");
				printf("请输入编号:\n");
				scanf("%d",&temp);
				print_num(temp);
				break;
			case 3:
				system("cls");
				printf("请输入名次:\n");
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
				printf("\aError! 请输入正确的数字!");
				continue;
		}
	}//循环操作
}

int file_read()	//读取文件
{
	FILE *fp;
	if ((fp = fopen("data.txt","rb")) == NULL)
	{
		if ((fp = fopen("data.txt","wb")) == NULL)
		{	//若文件不存在,创建文件
			printf("打开文件失败!\n");
			exit(EXIT_FAILURE);
		}
		fclose(fp);
		return 1;
	}
	fread(member,sizeof(struct Member_information),10,fp);	//将文件的内容读取到结构体中
	fclose(fp);
	return 0;
}

void file_write()	//写出到文件
{
	FILE *fp;
	if ((fp = fopen("data.txt","wb")) == NULL)
	{
		printf("打开文件失败!\n");
		exit(EXIT_FAILURE);
	}
	fwrite(member,sizeof(struct Member_information),10,fp);	//将结构体中的数据写到文件
	fclose(fp);
}

int main()
{	
	printf("   -=歌唱比赛评分=-    \n");
	printf("正在读取文件...\n");
	if (file_read())	//若文件不存在,创建文件
	{
		printf("文件创建成功,请输入数据\n\n");
		input_all();
	}
	else	//若文件存在,跳过输入,直接显示菜单
	{
		printf("文件已存在,可直接查询内容\n");
	}
	menu();
	file_write();	//结束程序前把数据保存到文件
	return 0;
}