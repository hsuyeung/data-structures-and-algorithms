/*顺序栈的定义文件*/
#include "../../common.h"
#ifndef SQ_STACK
#define SQ_STACK

/*最大容量定义 start*/
#define MAX_SIZE 20
/*最大容量定义 end*/

/*顺序栈的结构定义 start*/

typedef struct
{
    SElemType data[MAX_SIZE];
    //用于栈顶指针
    int top;
} SqStack;

/*顺序栈的结构定义 end*/

/*顺序栈具有的操作声明 start*/

/*初始化操作，建立并返回一个空栈S*/
SqStack InitStack();

/*将栈清空*/
void ClearStack(SqStack *S);

/*若栈为空，返回true，否则返回false*/
int StackEmpty(SqStack S);

/*若栈存在且非空，用e返回S的栈顶元素*/
int GetTop(SqStack S, SElemType *e);

/*若栈S存在，插入新元素e到栈S中并成为栈顶元素*/
int Push(SqStack *S, SElemType e);

/*删除栈S中栈顶元素，并用e返回其值*/
int Pop(SqStack *S, SElemType *e);

/*返回栈S中的元素个数*/
int StackLength(SqStack S);

/*打印栈中的元素*/
void showStack(SqStack S);

/*顺序栈具有的操作声明 end*/

#endif