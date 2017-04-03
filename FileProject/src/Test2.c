/*
 * Test2.c
 *
 *  Created on: Apr 3, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char ch;

	fp = fopen("/home/zhuhuiling/1.txt", "r");
	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}

	while((ch = fgetc(fp)) != EOF)
	{
		putchar(ch);
	}

	putchar('\n');
	fclose(fp);

	return 0;
}
