/* 顺序线性表的定义文件 */
#include "../../common.h"
#ifndef SQLIST
#define SQLIST

/* 最大容量定义 start */
#define MAX_SIZE 20
/* 最大容量定义 end */

/* 顺序存储线性表结构定义 start */

typedef struct
{
    /* 数组存储数据元素，最大容量为MAX_SIZE */
    ElemType data[MAX_SIZE];
    /* 线性表当前长度 */
    int length;
} SqList;

/* 顺序存储线性表结构定义 end */

/* 顺序线性表具有的操作声明 start */

/* 初始化线性表 */
SqList InitList();
/* 若线性表为空，返回true；否则返回false */
int ListEmpty(SqList L);
/* 将线性表清空 */
void ClearList(SqList *L);
/* 将线性表L中的第i个位置元素值返回给e */
int GetElem(SqList L, int i, ElemType *e);
/* 在线性表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功，否则返回-1 */
int LocationElem(SqList L, ElemType e);
/* 在L中第i个位置之前插入新的数据元素e，L的长度加1 */
int ListInsert(SqList *L, int i, ElemType e);
/* 删除L的第i个数据元素，并用e返回其值，L的长度减1 */
int ListDelete(SqList *L, int i, ElemType *e);

/* 顺序线性表具有的操作声明 end */

#endif