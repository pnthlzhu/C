/*
 * Test4.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>
#include "Struct.h"

int main(int argc, char *argv[])
{
	struct stu stu1 = {"hlzhu", 106, 28, 'A', 100.0f};

	//结构体变量名和数组名不同，数组名在表达式中会被转换为数组指针，
	//而结构体变量名不会，无论在任何表达式中它表示的都是整个集合本身
	struct stu *pStu1 = &stu1;

	fprintf(stdout, "%s's num is %d, age is %d, group is %c, score is %.1f\n",
								pStu1->name, pStu1->num, pStu1->age,
								pStu1->group, pStu1->score);

	return 0;
}
