#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*全局结构体数组*/
struct NameListStruct
{
	char Name[100];	
}List[100];

/*函数申明*/
void Show(void);//显示一些特定信息
int ReadFileList(void);//读取exe文件所在目录的文件列表，并筛选出txt文档，放入全局的结构体数组中
void PrintFileList(int row);//txt文档列表
int ReScanf(int min,int max);//输入选择，错误后循环提示，直至输入正确

/**************************************************************************************************
函数用途：main函数，程序入口；读取txt列表，并分割选中的文件
输入参数：无
返回参数：无
*/
void main(void)
{
	FILE *fpSrc,*fpDec;
	unsigned char* buff;
	int i,j,select,FileNum = 0,singleFileSize;
	long size;
	char fileName_Suffix[100],fileName[100],fileNameTmp[100];

	Show();//显示一些无关紧要的信息
	FileNum = ReadFileList();//读取txt文件列表
	PrintFileList(FileNum);//打印txt文件列表

	printf("\n如果列表显示无误，请输入需要分割的文本文档（txt文件）前的序号: ");  //菜单显示
	select = ReScanf(1,FileNum);//输入序号

	/* 下面五行内容，用于分别去除字符串中最后一个回车和后缀名 */
	strcpy(fileName_Suffix,List[select].Name);
	j = strlen(fileName_Suffix)-1;
	fileName_Suffix[j] = '\0';//字符用单引号，去掉最后一个回车
	strcpy(fileName,fileName_Suffix);
	fileName[j-4] = '\0';//将文件名去除后缀

	printf("\n你选择的是:“%s”，",fileName_Suffix);
	if( ( fpSrc = fopen(fileName_Suffix,"r" ) ) == 0 )//判断是否有文件
	{
		printf("\n\n对不起，文件木有找到或打不开啊！程序退出！\n");
		system("pause");//任意键继续
		exit(1);
	}

	fseek(fpSrc, 0L,SEEK_END);//将指针移动到末位
	size = ftell(fpSrc);//计算文件长度，目前指针的位置既是文件的长度
	if( size < 10000)
	{
		printf("这个文件长度为：“%ld”字节。\n连10000字节都不到，分个毛线啊，自己手动分割去。程序退出！\n",size);
		system("pause");//任意键继续
		exit(0);
	}
	printf("这个文件长度为：%ld字节。\n期望平均分割成几个文件？请输入小于99的数值：",size);
	select = ReScanf(2,99);//输入分割成几段的数值

	singleFileSize = size/select;//计算每个小文件大小
	printf("\n下面将会把“%s”分割成%d个大小为：%d字节（%dKB）的文件。\n\n",fileName_Suffix,select,singleFileSize,singleFileSize/1024);
	system("pause");//任意键继续

	fseek(fpSrc, 0L,SEEK_SET);//将指针移动到首位
	for(i = 1 ; i<=select ; i++ )
	{
		buff = (unsigned char*)malloc(singleFileSize);//动态申请单个小文件大小所需的内存
		sprintf(fileNameTmp,"%s - 第%02d段.txt",fileName,i);//文件名拼接
		fread(buff,singleFileSize,1,fpSrc);//从fpSrc中读取数据到buff
		fpDec = fopen(fileNameTmp,"w");//新建小文件
		fwrite(buff,singleFileSize,1,fpDec);//将buff数据写入到fpDec
		free(buff);//释放内存
		fclose(fpDec);//关闭目标文件
		printf("\n“%s”已成功生成！",fileNameTmp);
	}
	fclose(fpSrc);//关闭源文件

	printf("\n分割完毕！程序退出！");
	system("pause");//任意键继续
	exit(0);
}

/**************************************************************************************************
函数用途：显示一些特定信息
输入参数：无
返回参数：无
*/
void Show(void)
{
	system("color f0");//将dos界面以白底黑字的形式来显示
	system("title 文本文档（txt文件）分割软件 V1.0 Beta    mvp_xuan（QQ小说群110684061群主）");//使dos界面的上框显示这条信息

	printf("——————————————— 软 件 信 息 ———————————————");
	printf("\n    主要功能：平均分割txt文档（10000字节，既9.7KB以上）。");
	printf("\n    使用方法：\n        1.在txt存放目录下运行本程序，程序会读出当前目录下所有txt文档并显示；");
	printf("\n        2.根据提示选择需要分割的文档前的序号；\n        3.根据提示输入分割成几段。\n");
	printf("\n    其他：如第一次运行报错，再运行一次即可。杀毒软件认为它是木马时，选择信任即可。如有其他问题，请加入到QQ群：110684061。\n");
	printf("—————————————————————————————————————\n\n");
}

/**************************************************************************************************
函数用途：读取exe文件所在目录的文件列表，并筛选出txt文档，放入全局的结构体数组中
输入参数：无
返回参数：txt文件的数量值
*/
int ReadFileList(void)
{
	FILE *fp;
	int i = 0 ,row = 0;
	char fileList[100][100];

	system("DIR /B > TmpDirList.log");//将文件列表读入到log文件中

	fp = fopen("TmpDirList.log","r");//读到fp0
	for( ; i < 100 ;i++)
	{
		if(fgets(fileList[i], 100, fp) == NULL) //读取一行到fileList[i]
			break;
		if(strstr(fileList[i],".txt")!=NULL)//判断是否是txt文件
		{
			if(row == 0)//第一行显示的内容
				printf("当前目录下有以下文本文档：\n");
			row++;
			strcpy(List[row].Name,fileList[i]);//将txt文件列表复制到List结构体中去
		}
	}
	fclose(fp);
	remove("TmpDirList.log");//删除这个存储文件列表的临时文件

	return row;
}

/**************************************************************************************************
函数用途：打印txt文档列表
输入参数：txt文件的数量值
返回参数：无
*/
void PrintFileList(int row)
{
	int i = 1;

	if(row <= 0)
	{
		printf("(#‵′)靠，本目录一个文本文档（txt文件）都木有，分割个毛线啊。程序退出！\n");
		system("pause");//任意键继续
		exit(0);//结束程序
	}
	else
		for(; i <= row ; i++)//打印txt文件列表
			if(List[i].Name != "")
				printf("%2d. %s",i,List[i].Name);
}

/**************************************************************************************************
函数用途：输入选择，错误后循环提示，直至输入正确
输入参数：min:允许的最小输入值，max:允许的最大输入值
返回参数：输入的值
*/
int ReScanf(int min,int max)
{
	int select;

	fflush(stdin);
	scanf("%d",&select);    //输入选择
	while( select > max || select < min )
	{
		printf("\n输入有误,请输入%d-%d之间的数字: ",min,max);
		fflush(stdin);
		scanf("%d",&select);    //输入选择
	}

	return select;
}