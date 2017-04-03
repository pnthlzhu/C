/*
 * Test5.c
 *
 *  Created on: Apr 3, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char str[102] = {0}, strTemp[100];

	fp = fopen("/home/zhuhuiling/2.txt", "at+");
	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}

	printf("please input a string:\n");
	gets(strTemp);
	strcat(str, "\n");
	strcat(str, strTemp);
	fputs(str, fp);

	fclose(fp);

	return 0;
}
