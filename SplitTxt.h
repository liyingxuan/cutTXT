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

void Show(void);
int ReadFileList(void);
void PrintFileList(int row);
int ReScanf(int min,int max);

#endif /* MAIN_H_ */
