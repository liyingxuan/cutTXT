/*
 * main.h
 *
 *  Created on: Jan 16, 2012
 *      Author: dracher
 */

#ifndef MAIN_H_
#define MAIN_H_

struct NameListStruct
{
	char Name[100];
}List[100];  //Global Strut Array

void Show(void);//显示一些特定信息
int ReadFileList(void);//读取exe文件所在目录的文件列表，并筛选出txt文档，放入全局的结构体数组中
void PrintFileList(int row);//txt文档列表
int ReScanf(int min,int max);//输入选择，错误后循环提示，直至输入正确

#endif /* MAIN_H_ */
