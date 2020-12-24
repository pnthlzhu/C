#include <stdio.h>

//函数指针变量pMaxFun
int (*pMaxFun)(int, int);

int maxFun(int x, int y)
{
    return x > y ? x : y;
}

int main()
{
    pMaxFun = maxFun;

    fprintf(stderr, "max value is %d\n", (*pMaxFun)(4, 6));

    return 0;
}
