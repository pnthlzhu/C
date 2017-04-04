/*
 * Test.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

//共用体类型定义
union data{
	int n;
	char ch;
	short m;
};

int main(int argc, char *argv[])
{
	//定义共用体变量
	union data a;

	printf("%ld, %ld\n", sizeof(a), sizeof(union data));

	a.n = 0x40;
	printf("%x, %c, %hx\n", a.n, a.ch, a.m);

	a.ch ='9';
	printf("%x, %c, %hx\n", a.n, a.ch, a.m);

	a.m = 0x2059;
	printf("%x, %c, %hx\n", a.n, a.ch, a.m);

	a.n = 0x3E25AD54;
	printf("%x, %c, %hx\n", a.n, a.ch, a.m);

	return 0;
}
