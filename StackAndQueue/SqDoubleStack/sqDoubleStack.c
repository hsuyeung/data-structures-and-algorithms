#include "sqDoubleStack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //初始化一个空栈
    SqDoubleStack sqDoubleStack = InitStack();
    //判断是否是空栈
    printf("两栈共享空间当前为空：%d\n", StackEmpty(sqDoubleStack));
    //向栈1和栈2内填充数据
    int i;
    for (i = 0; i < 10; i++)
    {
        if (!Push(&sqDoubleStack, i, 1))
        {
            printf("入栈1失败。\n");
        }
    }
    for (i = MAX_SIZE - 1; i >= MAX_SIZE - 10; i--)
    {
        if (!Push(&sqDoubleStack, i, 2))
        {
            printf("入栈2失败。\n");
        }
    }
    printf("向栈中填充数据成功。\n");
    printf("顺序栈当前为空栈：%d\n", StackEmpty(sqDoubleStack));
    showStack(sqDoubleStack);
    //统计栈的长度
    printf("当前栈的长度为：%d\n", StackLength(sqDoubleStack));
    //获取栈1顶的一个元素
    SElemType elem = -1;
    if (GetTop(sqDoubleStack, &elem, 1) == OK)
    {
        printf("栈1的顶部元素为：%d\n", elem);
    }
    //获取栈2顶的一个元素
    if (GetTop(sqDoubleStack, &elem, 2) == OK)
    {
        printf("栈2的顶部元素为：%d\n", elem);
    }
    //弹出一个栈1的元素
    if (Pop(&sqDoubleStack, &elem, 1) == OK)
    {
        printf("弹出成功，该元素的值为：%d\n", elem);
    }
    showStack(sqDoubleStack);
    printf("当前栈的长度为：%d\n", StackLength(sqDoubleStack));
    //弹出一个栈2的元素
    if (Pop(&sqDoubleStack, &elem, 2) == OK)
    {
        printf("弹出成功，该元素的值为：%d\n", elem);
    }
    showStack(sqDoubleStack);
    printf("当前栈的长度为：%d\n", StackLength(sqDoubleStack));
    //将栈清空
    ClearStack(&sqDoubleStack);
    printf("当前栈的长度为：%d\n", StackLength(sqDoubleStack));
    showStack(sqDoubleStack);

    return 0;
}

/*两栈共享空间结构操作定义 start*/

/*初始化操作，建立并返回一个空栈S*/
SqDoubleStack InitStack()
{
    SqDoubleStack S;
    S.top1 = -1;
    S.top2 = MAX_SIZE;
    return S;
}

/*将栈清空*/
void ClearStack(SqDoubleStack *S)
{
    S->top1 = -1;
    S->top2 = MAX_SIZE;
}

/*若栈为空，返回true，否则返回false*/
int StackEmpty(SqDoubleStack S)
{
    return (S.top1 == -1 && S.top2 == MAX_SIZE) ? TRUE : FALSE;
}

/*若栈存在且非空，用e返回S的栈顶元素*/
int GetTop(SqDoubleStack S, SElemType *e, int stackNumber)
{
    //获取栈1的栈顶元素值
    if (stackNumber == 1)
    {
        //栈1为空时，获取栈顶元素失败
        if (S.top1 == -1)
        {
            printf("栈1为空。\n");
            return ERROR;
        }
        //将栈1的栈顶元素的值赋值给e元素
        *e = S.data[S.top1];
    }
    else
    { //获取栈2的栈顶元素值
        //栈2为空，获取栈顶元素失败
        if (S.top2 == MAX_SIZE)
        {
            printf("栈2为空。\n");
            return ERROR;
        }
        //将栈2的栈顶元素的值赋值给e元素
        *e = S.data[S.top2];
    }
    return OK;
}

/*若栈S存在，插入新元素e到栈S中并成为栈顶元素*/
int Push(SqDoubleStack *S, SElemType e, int stackNumber)
{
    //如果栈已经满了
    if (S->top1 + 1 == S->top2)
    {
        printf("栈满了，共享空间已经用完了。\n");
        return ERROR;
    }
    //如果是栈1有元素进栈
    if (stackNumber == 1)
    {
        //先给top1+1再给数组元素赋值
        S->data[++S->top1] = e;
    }
    //如果是栈2有元素进栈
    else if (stackNumber == 2)
    {
        //先给top2-1再给数组元素赋值
        S->data[--S->top2] = e;
    }
    return OK;
}

/*删除栈S中栈顶元素，并用e返回其值*/
int Pop(SqDoubleStack *S, SElemType *e, int stackNumber)
{
    if (stackNumber == 1)
    {
        //如果栈1已经空了
        if (S->top1 == -1)
        {
            printf("栈1已经空了。\n");
            return ERROR;
        }
        //将栈1的栈顶元素出栈
        *e = S->data[S->top1--];
    }
    else if (stackNumber == 2)
    {
        //如果栈2已经空了
        if (S->top2 == MAX_SIZE)
        {
            printf("栈2已经空了。\n");
            return ERROR;
        }
        //将栈2的元素出栈
        *e = S->data[S->top2++];
    }
    return OK;
}

/*返回栈S中的元素个数*/
int StackLength(SqDoubleStack S)
{
    return (S.top1 + 1) + (MAX_SIZE - S.top2);
}

/*打印栈中的元素*/
void showStack(SqDoubleStack S)
{
    if (StackEmpty(S))
    {
        printf("栈是空的，没有数据了。\n");
        exit(0);
    }
    printf("共享栈的当前数据如下：\n");
    int i;
    //先打印栈1
    printf("栈1的元素如下：");
    for (i = 0; i <= S.top1; i++)
    {
        printf("->%d", S.data[i]);
    }
    printf("\n");
    //打印栈2
    printf("栈2的元素如下：");
    for (i = MAX_SIZE - 1; i >= S.top2; i--)
    {
        printf("->%d", S.data[i]);
    }
    printf("\n");
}

/*两栈共享空间结构操作定义 end*/