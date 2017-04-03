/*
 * Test4.c
 *
 *  Created on: Apr 3, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

#define N 100

int main(int argc, char *argv[])
{
	FILE *fp;
	char str[N+1];

	fp = fopen("/home/zhuhuiling/1.txt", "rt");
	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}

	while(fgets(str, N, fp) != NULL)
	{
		puts(str);
	}
	fclose(fp);

	return 0;
}
