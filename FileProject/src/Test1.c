/*
 * Test1.c
 *
 *  Created on: Apr 2, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp = fopen("", "r");

	if(fp == NULL)
	{
		printf("open file failed!\n");
		return 0;
	}

	return 0;
}
