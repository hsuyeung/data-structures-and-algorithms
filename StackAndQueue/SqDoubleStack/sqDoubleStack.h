/*两个栈共享空间的定义文件*/
#include "../../common.h"
#ifndef SQ_DOUBLE_STACK
#define SQ_DOUBLE_STACK

/*最大容量定义 start*/
#define MAX_SIZE 30
/*最大容量定义 end*/

/*两栈共享空间结构定义 start*/
typedef struct
{
    SElemType data[MAX_SIZE];
    //栈1栈顶指针
    int top1;
    //栈2栈顶指针
    int top2;
} SqDoubleStack;
/*两栈共享空间结构定义 end*/

/*两栈共享空间结构操作声明 start*/

/*初始化操作，建立并返回一个空栈S*/
SqDoubleStack InitStack();

/*将栈清空*/
void ClearStack(SqDoubleStack *S);

/*若栈为空，返回true，否则返回false*/
int StackEmpty(SqDoubleStack S);

/*若栈存在且非空，用e返回S的栈顶元素*/
int GetTop(SqDoubleStack S, SElemType *e, int stackNumber);

/*若栈S存在，插入新元素e到栈S中并成为栈顶元素*/
int Push(SqDoubleStack *S, SElemType e, int stackNumber);

/*删除栈S中栈顶元素，并用e返回其值*/
int Pop(SqDoubleStack *S, SElemType *e, int stackNumber);

/*返回栈S中的元素个数*/
int StackLength(SqDoubleStack S);

/*打印栈中的元素*/
void showStack(SqDoubleStack S);

/*两栈共享空间结构操作声明 end*/


#endif