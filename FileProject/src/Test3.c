/*
 * Test3.c
 *
 *  Created on: Apr 3, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char ch;

	fp = fopen("/home/zhuhuiling/2.txt", "a+");
	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}

	printf("please input a string:\n");
	while((ch = getchar()) != '\n')
	{
		fputc(ch, fp);
	}

	fclose(fp);

	return 0;
}
