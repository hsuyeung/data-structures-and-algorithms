/*链栈的定义文件*/
#include "../../common.h"
#ifndef LINK_STACK
#define LINK_STACK

/*最大容量定义 start*/
#define MAX_SIZE 20
/*最大容量定义 end*/

/*链栈的结构定义 start*/

typedef struct StackNode
{
    SElemType data;
    struct StackNode *next;
} StackNode, *LinkStackPtr;

typedef struct LinkStack
{
    //栈顶指针
    LinkStackPtr top;
    //计数器
    int count;
} LinkStack;

/*链栈的结构定义 end*/

/*链栈具有的操作声明 start*/

/*初始化一个空的链栈*/
void InitLinkStack(LinkStack *LS);

/*将栈清空*/
void ClearLinkStack(LinkStack *LS);

/*若栈为空，返回true，否则返回false*/
int LinkStackEmpty(LinkStack LS);

/*若栈存在且非空，用e返回栈顶元素*/
int GetTop(LinkStack LS, SElemType *e);

/*若栈存在，插入新元素e到栈中并成为栈顶元素*/
int Push(LinkStack *LS, SElemType e);

/*删除栈中栈顶元素，并用e返回其值*/
int Pop(LinkStack *LS, SElemType *e);

/*返回栈中的元素个数*/
int LinkStackLength(LinkStack LS);

/*打印栈中的元素*/
void showLinkStack(LinkStack LS);

/*链栈具有的操作声明 end*/

#endif