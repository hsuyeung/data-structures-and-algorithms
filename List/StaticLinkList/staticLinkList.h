/* 静态链表的定义文件 */
/* 
 * 注意：这些代码都是在假设静态链表足够长的情况，
 * 所以不考虑静态链表满了的情况
  */
#include "../../common.h"
#ifndef STATIC_LINK_LIST
#define STATIC_LINK_LIST

/* 静态链表结构定义 start */

#define MAX_SIZE 20
typedef struct
{
    ElemType data;
    // 游标，为0时表示无指向
    int cur;
} Component, StaticLinkList[MAX_SIZE];

/* 静态链表结构定义 end */

/* 静态链表具有的操作声明 start */

/* 初始化，将一维数组space中各分量链成一个备用链表 */
int InitList(StaticLinkList space);
/* 从备用链表中分配一个结点用于插入数据 */
int Malloc_SLL(StaticLinkList space);
/* 在静态链表在L中第i个元素之前插入新的数据元素e */
int ListInsert(StaticLinkList L, int i, ElemType e);
/* 将下标为k的空闲结点回收到备用链表 */
void Free_SLL(StaticLinkList space, int k);
/* 删除在静态链表L中第i个数据元素e */
int ListDelete(StaticLinkList L, int i);
/* 求静态链表的长度 */
int ListLength(StaticLinkList L);
/* 在静态链表中查找与元素e值相等的元素的下标(位置)，找不到就返回-1 */
int LocElem(StaticLinkList L, ElemType e);

/* 静态链表具有的操作声明 end */


#endif