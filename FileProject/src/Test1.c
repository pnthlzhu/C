/*
 * Test1.c
 *
 *  Created on: Apr 2, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp = fopen("/home/zhuhuiling/1.txt", "r");

	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}
	else
	{
		printf("open file success!\n");
		fclose(fp);
	}

	return 0;
}
