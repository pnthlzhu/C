/*
 * Test3.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>
#include "Struct.h"

int main(int argc, char *argv[])
{
	//结构体数组
	struct stu szClass[] = {
			{"jerry", 100, 10, 'A', 99.99f},
			{"tom", 101, 11, 'B', 89.99f},
			{"bob", 102, 12, 'C', 79.99f}
	};

	printf("sizeof(struct stu) is %ld\n", sizeof(struct stu));
	printf("sizeof(szClass) is %ld\n", sizeof(szClass));

	//获取数组大小
	int iLength = sizeof(szClass)/sizeof(szClass[0]);
	int i = 0;
	for(i = 0;i < iLength;i++)
	{
		fprintf(stdout, "%s's num is %d, age is %d, group is %c, score is %.1f\n",
							szClass[i].name, szClass[i].num, szClass[i].age,
							szClass[i].group, szClass[i].score);
	}

	return 0;
}
