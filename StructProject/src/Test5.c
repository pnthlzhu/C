/*
 * Test5.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>
#include "Struct.h"

int main(int argc, char *argv[])
{
	struct stu szClass[] = {
			{"jerry", 100, 10, 'A', 99.99f},
			{"tom", 101, 11, 'B', 89.99f},
			{"bob", 102, 12, 'C', 79.99f}
	};

	//结构体数组指针
	struct stu *pStu;
	//获取数组的长度
	int iLength = sizeof(szClass)/sizeof(szClass[0]);
	printf("Name\tNum\tAge\tGroup\tScore\t\n");
	for(pStu = szClass;pStu < szClass + iLength;pStu++)
	{
		printf("%s\t%d\t%d\t%c\t%.1f\n", pStu->name, pStu->num, pStu->age,
					pStu->group, pStu->score);
	}

	return 0;
}
