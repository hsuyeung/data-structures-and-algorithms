#include "sqStack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 初始化一个空栈
    SqStack sqStack = InitStack();
    // 判断是否是空栈
    printf("顺序栈当前为空栈：%d\n", StackEmpty(sqStack));
    // 向栈内填充数据
    int i;
    for (i = 0; i < 10; i++)
    {
        if (!Push(&sqStack, i))
        {
            printf("入栈失败。\n");
        }
    }
    printf("向栈中填充数据成功。\n");
    printf("顺序栈当前为空栈：%d\n", StackEmpty(sqStack));
    showStack(sqStack);
    // 获取栈顶的一个元素
    SElemType elem = -1;
    if (GetTop(sqStack, &elem) == OK)
    {
        printf("顺序栈的顶部元素为：%d\n", elem);
    }
    // 统计栈的长度
    printf("当前栈的长度为：%d\n", StackLength(sqStack));
    // 弹出一个顺序栈的元素
    if (Pop(&sqStack, &elem) == OK)
    {
        printf("弹出成功，该元素的值为：%d\n", elem);
    }
    showStack(sqStack);
    printf("当前栈的长度为：%d\n", StackLength(sqStack));
    // 将栈清空
    ClearStack(&sqStack);
    printf("当前栈的长度为：%d\n", StackLength(sqStack));
    showStack(sqStack);

    return 0;
}

/* 顺序栈具有的操作定义 start */

/* 初始化操作，建立并返回一个空栈S */
SqStack InitStack()
{
    SqStack S;
    S.top = -1;
    return S;
}

/* 将栈清空 */
void ClearStack(SqStack *S)
{
    S->top = -1;
}

/* 若栈为空，返回true，否则返回false */
int StackEmpty(SqStack S)
{
    return (S.top == -1) ? TRUE : FALSE;
}

/* 若栈存在且非空，用e返回S的栈顶元素 */
int GetTop(SqStack S, SElemType *e)
{
    if (StackEmpty(S))
    {
        printf("是空栈。\n");
        return ERROR;
    }
    *e = S.data[S.top];
    return OK;
}

/* 若栈S存在，插入新元素e到栈S中并成为栈顶元素 */
int Push(SqStack *S, SElemType e)
{
    if (S->top == MAX_SIZE - 1)
    {
        printf("栈已经满了。\n");
        return ERROR;
    }
    // 栈顶指针加1
    S->top++;
    // 将新元素赋值给栈顶空间
    S->data[S->top] = e;
    return OK;
}

/* 删除栈S中栈顶元素，并用e返回其值 */
int Pop(SqStack *S, SElemType *e)
{
    if (StackEmpty(*S))
    {
        printf("栈已经空了。\n");
        return ERROR;
    }
    // 将要删除的栈顶元素赋值给e
    *e = S->data[S->top];
    // 栈顶指针减1
    S->top--;
    return OK;
}

/* 返回栈S中的元素个数 */
int StackLength(SqStack S)
{
    return S.top + 1;
}

/* 打印栈中的元素 */
void showStack(SqStack S)
{
    if (StackEmpty(S))
    {
        printf("栈是空的，没有数据了。\n");
        exit(0);
    }
    
    printf("按照LIFO的顺序打印栈的数据如下：\n");
    int i;
    for (i = S.top; i > -1; i--)
    {
        printf("->%d", S.data[i]);
    }
    printf("\n");
}

/* 顺序栈具有的操作定义 end */