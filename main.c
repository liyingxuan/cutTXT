#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*ȫ�ֽṹ������*/
struct NameListStruct
{
	char Name[100];	
}List[100];

/*��������*/
void Show(void);//��ʾһЩ�ض���Ϣ
int ReadFileList(void);//��ȡexe�ļ�����Ŀ¼���ļ��б���ɸѡ��txt�ĵ�������ȫ�ֵĽṹ��������
void PrintFileList(int row);//txt�ĵ��б�
int ReScanf(int min,int max);//����ѡ�񣬴����ѭ����ʾ��ֱ��������ȷ

/**************************************************************************************************
������;��main������������ڣ���ȡtxt�б����ָ�ѡ�е��ļ�
�����������
���ز�������
*/
void main(void)
{
	FILE *fpSrc,*fpDec;
	unsigned char* buff;
	int i,j,select,FileNum = 0,singleFileSize;
	long size;
	char fileName_Suffix[100],fileName[100],fileNameTmp[100];

	Show();//��ʾһЩ�޹ؽ�Ҫ����Ϣ
	FileNum = ReadFileList();//��ȡtxt�ļ��б�
	PrintFileList(FileNum);//��ӡtxt�ļ��б�

	printf("\n����б���ʾ������������Ҫ�ָ���ı��ĵ���txt�ļ���ǰ�����: ");  //�˵���ʾ
	select = ReScanf(1,FileNum);//�������

	/* �����������ݣ����ڷֱ�ȥ���ַ��������һ���س��ͺ�׺�� */
	strcpy(fileName_Suffix,List[select].Name);
	j = strlen(fileName_Suffix)-1;
	fileName_Suffix[j] = '\0';//�ַ��õ����ţ�ȥ�����һ���س�
	strcpy(fileName,fileName_Suffix);
	fileName[j-4] = '\0';//���ļ���ȥ����׺

	printf("\n��ѡ�����:��%s����",fileName_Suffix);
	if( ( fpSrc = fopen(fileName_Suffix,"r" ) ) == 0 )//�ж��Ƿ����ļ�
	{
		printf("\n\n�Բ����ļ�ľ���ҵ���򲻿����������˳���\n");
		system("pause");//���������
		exit(1);
	}

	fseek(fpSrc, 0L,SEEK_END);//��ָ���ƶ���ĩλ
	size = ftell(fpSrc);//�����ļ����ȣ�Ŀǰָ���λ�ü����ļ��ĳ���
	if( size < 10000)
	{
		printf("����ļ�����Ϊ����%ld���ֽڡ�\n��10000�ֽڶ��������ָ�ë�߰����Լ��ֶ��ָ�ȥ�������˳���\n",size);
		system("pause");//���������
		exit(0);
	}
	printf("����ļ�����Ϊ��%ld�ֽڡ�\n����ƽ���ָ�ɼ����ļ���������С��99����ֵ��",size);
	select = ReScanf(2,99);//����ָ�ɼ��ε���ֵ

	singleFileSize = size/select;//����ÿ��С�ļ���С
	printf("\n���潫��ѡ�%s���ָ��%d����СΪ��%d�ֽڣ�%dKB�����ļ���\n\n",fileName_Suffix,select,singleFileSize,singleFileSize/1024);
	system("pause");//���������

	fseek(fpSrc, 0L,SEEK_SET);//��ָ���ƶ�����λ
	for(i = 1 ; i<=select ; i++ )
	{
		buff = (unsigned char*)malloc(singleFileSize);//��̬���뵥��С�ļ���С������ڴ�
		sprintf(fileNameTmp,"%s - ��%02d��.txt",fileName,i);//�ļ���ƴ��
		fread(buff,singleFileSize,1,fpSrc);//��fpSrc�ж�ȡ���ݵ�buff
		fpDec = fopen(fileNameTmp,"w");//�½�С�ļ�
		fwrite(buff,singleFileSize,1,fpDec);//��buff����д�뵽fpDec
		free(buff);//�ͷ��ڴ�
		fclose(fpDec);//�ر�Ŀ���ļ�
		printf("\n��%s���ѳɹ����ɣ�",fileNameTmp);
	}
	fclose(fpSrc);//�ر�Դ�ļ�

	printf("\n�ָ���ϣ������˳���");
	system("pause");//���������
	exit(0);
}

/**************************************************************************************************
������;����ʾһЩ�ض���Ϣ
�����������
���ز�������
*/
void Show(void)
{
	system("color f0");//��dos�����԰׵׺��ֵ���ʽ����ʾ
	system("title �ı��ĵ���txt�ļ����ָ���� V1.0 Beta    mvp_xuan��QQС˵Ⱥ110684061Ⱥ����");//ʹdos������Ͽ���ʾ������Ϣ

	printf("������������������������������ �� �� �� Ϣ ������������������������������");
	printf("\n    ��Ҫ���ܣ�ƽ���ָ�txt�ĵ���10000�ֽڣ���9.7KB���ϣ���");
	printf("\n    ʹ�÷�����\n        1.��txt���Ŀ¼�����б����򣬳���������ǰĿ¼������txt�ĵ�����ʾ��");
	printf("\n        2.������ʾѡ����Ҫ�ָ���ĵ�ǰ����ţ�\n        3.������ʾ����ָ�ɼ��Ρ�\n");
	printf("\n    ���������һ�����б���������һ�μ��ɡ�ɱ�������Ϊ����ľ��ʱ��ѡ�����μ��ɡ������������⣬����뵽QQȺ��110684061��\n");
	printf("��������������������������������������������������������������������������\n\n");
}

/**************************************************************************************************
������;����ȡexe�ļ�����Ŀ¼���ļ��б���ɸѡ��txt�ĵ�������ȫ�ֵĽṹ��������
�����������
���ز�����txt�ļ�������ֵ
*/
int ReadFileList(void)
{
	FILE *fp;
	int i = 0 ,row = 0;
	char fileList[100][100];

	system("DIR /B > TmpDirList.log");//���ļ��б���뵽log�ļ���

	fp = fopen("TmpDirList.log","r");//����fp0
	for( ; i < 100 ;i++)
	{
		if(fgets(fileList[i], 100, fp) == NULL) //��ȡһ�е�fileList[i]
			break;
		if(strstr(fileList[i],".txt")!=NULL)//�ж��Ƿ���txt�ļ�
		{
			if(row == 0)//��һ����ʾ������
				printf("��ǰĿ¼���������ı��ĵ���\n");
			row++;
			strcpy(List[row].Name,fileList[i]);//��txt�ļ��б��Ƶ�List�ṹ����ȥ
		}
	}
	fclose(fp);
	remove("TmpDirList.log");//ɾ������洢�ļ��б����ʱ�ļ�

	return row;
}

/**************************************************************************************************
������;����ӡtxt�ĵ��б�
���������txt�ļ�������ֵ
���ز�������
*/
void PrintFileList(int row)
{
	int i = 1;

	if(row <= 0)
	{
		printf("(#�F��)������Ŀ¼һ���ı��ĵ���txt�ļ�����ľ�У��ָ��ë�߰��������˳���\n");
		system("pause");//���������
		exit(0);//��������
	}
	else
		for(; i <= row ; i++)//��ӡtxt�ļ��б�
			if(List[i].Name != "")
				printf("%2d. %s",i,List[i].Name);
}

/**************************************************************************************************
������;������ѡ�񣬴����ѭ����ʾ��ֱ��������ȷ
���������min:�������С����ֵ��max:������������ֵ
���ز����������ֵ
*/
int ReScanf(int min,int max)
{
	int select;

	fflush(stdin);
	scanf("%d",&select);    //����ѡ��
	while( select > max || select < min )
	{
		printf("\n��������,������%d-%d֮�������: ",min,max);
		fflush(stdin);
		scanf("%d",&select);    //����ѡ��
	}

	return select;
}