/*
 * Test2.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	//枚举类型的定义
	enum week{
		Mon = 100, //枚举值从100开始
		Tues, Wed, Thurs, Fri, Sat, Sun
	} day = Tues;//定义枚举变量并赋值

	printf("day value is %d\n", day);
	printf("sizeof(enum week) is %ld\n", sizeof(enum week));
	printf("sizeof(day) is %ld\n", sizeof(day));
	printf("sizeof(Wed) is %ld\n", sizeof(Wed));
	printf("sizeof(int) is %ld\n", sizeof(int));

	return 0;
}
