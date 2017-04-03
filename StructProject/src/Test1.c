/*
 * Test1.c
 *
 *  Created on: Apr 3, 2017
 *      Author: zhuhuiling
 */

#include <stdio.h>

//定义结构体
struct stu{
	char *name;	//姓名
	int num;	//学号
	int age;	//年龄
	char group;	//所在学习小组
	float score;//成绩
};

int main(int argc, char *argv[])
{
	//定义结构体变量
	struct stu stu1;
	stu1.name = "hlzhu";
	stu1.num = 106;
	stu1.age = 28;
	stu1.group = 'A';
	stu1.score = 100.0f;

	struct stu stu2 = {"ghy", 107, 28, 'B', 99.87f};

	fprintf(stdout, "%s's num is %d, age is %d, group is %c, score is %.1f\n",
			stu1.name, stu1.num, stu1.age, stu1.group, stu1.score);

	fprintf(stdout, "%s's num is %d, age is %d, group is %c, score is %.1f\n",
						stu2.name, stu2.num, stu2.age, stu2.group, stu2.score);

	//内存对齐
	fprintf(stdout, "sizeof(struct stu) is %ld\n", sizeof(struct stu));

	return 0;
}
