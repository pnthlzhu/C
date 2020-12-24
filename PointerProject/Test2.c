#include <stdio.h>

//typedef定义新的函数指针类型
typedef int (*MaxFun)(int, int);

int maxFun(int x, int y)
{
    return x > y ? x : y;
}

int main()
{
    MaxFun fpMax;

    fpMax = maxFun;

    fprintf(stderr, "max value is %d\n", (*fpMax)(4, 6));

    return 0;
}
