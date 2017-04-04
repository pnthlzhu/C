/*
 * Test2.c
 *
 *  Created on: Apr 4, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

#define TOTAL 4	//人员总数

struct{
	char name[20];
	int num;
	char sex;
	char profession;
	union{
		float score;
		char course[20];
	} sc;
} bodys[TOTAL];

int main(int argc, char *argv[])
{
	int i;
	for(i = 0;i < TOTAL;i++)
	{
		printf("please input information:");
		scanf("%s %d %c %c", bodys[i].name, &(bodys[i].num), &(bodys[i].sex),
				&(bodys[i].profession));
		if(bodys[i].profession == 's')
		{
			scanf("%f", &(bodys[i].sc.score));
		}
		else
		{
			scanf("%s", bodys[i].sc.course);
		}

		fflush(stdin);
	}

	printf("\nName\tNum\tSex\tProfession\tScore/Course\n");
	for(i = 0;i < TOTAL;i++)
	{
		if(bodys[i].profession == 's')
		{
			printf("%s\t%d\t%c\t%c\t\t%f\n", bodys[i].name, bodys[i].num, bodys[i].sex,
					bodys[i].profession, bodys[i].sc.score);
		}
		else
		{
			printf("%s\t%d\t%c\t%c\t\t%s\n", bodys[i].name, bodys[i].num, bodys[i].sex,
					bodys[i].profession, bodys[i].sc.course);
		}

		fflush(stdout);
	}

	return 0;
}
