#include "linkStack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //初始化一个空的链栈
    LinkStack linkStack;
    InitLinkStack(&linkStack);
    //判断是否为空栈
    printf("链栈是否为空：%d\n", LinkStackEmpty(linkStack));
    //向栈内填充数据
    int i;
    for (i = 0; i < 10; i++)
    {
        if (!Push(&linkStack, i))
        {
            printf("入栈失败。\n");
        }
    }
    printf("向栈中填充数据成功。\n");
    printf("顺序栈当前为空栈：%d\n", LinkStackEmpty(linkStack));
    showLinkStack(linkStack);
    //获取栈顶的一个元素
    SElemType elem = -1;
    if (GetTop(linkStack, &elem) == OK)
    {
        printf("顺序栈的顶部元素为：%d\n", elem);
    }
    //统计栈的长度
    printf("当前栈的长度为：%d\n", LinkStackLength(linkStack));
    //弹出一个顺序栈的元素
    if (Pop(&linkStack, &elem) == OK)
    {
        printf("弹出成功，该元素的值为：%d\n", elem);
    }
    showLinkStack(linkStack);
    printf("当前栈的长度为：%d\n", LinkStackLength(linkStack));
    //将栈清空
    ClearLinkStack(&linkStack);
    printf("当前栈的长度为：%d\n", LinkStackLength(linkStack));
    return 0;
}

/*链栈具有的操作定义 start*/

/*初始化一个空的链栈*/
void InitLinkStack(LinkStack *LS)
{
    LS->top = (LinkStackPtr)malloc(sizeof(StackNode));
    if (!(LS->top))
    {
        printf("内存分配失败。\n");
        exit(0);
    }
    LS->top = NULL;
    LS->count = 0;
}

/*将栈清空*/
void ClearLinkStack(LinkStack *LS)
{
    if (LinkStackEmpty(*LS))
    {
        printf("已经是空栈，没有数据了。\n");
        exit(0);
    }
    LinkStackPtr p, q;
    p = LS->top;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    LS->top = NULL;
    LS->count = 0;
}

/*若栈为空，返回true，否则返回false*/
int LinkStackEmpty(LinkStack LS)
{
    return LS.count == 0 ? TRUE : FALSE;
}

/*若栈存在且非空，用e返回栈顶元素*/
int GetTop(LinkStack LS, SElemType *e)
{
    if (LinkStackEmpty(LS))
    {
        printf("已经是空栈，没有数据了。\n");
        return ERROR;
    }
    *e = LS.top->data;
    return OK;
}

/*若栈存在，插入新元素e到栈中并成为栈顶元素*/
int Push(LinkStack *LS, SElemType e)
{
    LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
    s->data = e;
    //把当前的栈顶元素赋值给新结点的直接后继
    s->next = LS->top;
    //将新结点s赋值给栈顶指针
    LS->top = s;
    LS->count++;
    return OK;
}

/*删除栈中栈顶元素，并用e返回其值*/
int Pop(LinkStack *LS, SElemType *e)
{
    LinkStackPtr p;
    if (LinkStackEmpty(*LS))
    {
        printf("已经是空栈，没有数据了。\n");
        return ERROR;
    }
    *e = LS->top->data;
    //将栈顶结点赋值给p
    p = LS->top;
    //使栈顶指针下移一位，指向后一结点
    LS->top = LS->top->next;
    //释放结点p
    free(p);
    LS->count--;
    return OK;
}

/*返回栈中的元素个数*/
int LinkStackLength(LinkStack LS)
{
    return LS.count;
}

/*打印栈中的元素*/
void showLinkStack(LinkStack LS)
{
    if (LinkStackEmpty(LS))
    {
        printf("已经是空栈，没有数据了。\n");
        exit(0);
    }
    LinkStackPtr p;
    p = LS.top;
    while (p)
    {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");
}

/*链栈具有的操作定义 end*/