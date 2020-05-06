/* 单向循环链表的定义文件 */
#include "../../common.h"
#ifndef CYCLT_LINK_LIST
#define CYCLE_LINK_LIST

/* 单向循环链表的结构定义 start */

typedef struct CLNode
{
    ElemType data;
    struct CLNode *next;
} CLNode;
typedef CLNode *CycleLinkList;

/* 单向循环链表的结构定义 end */

/* 单向循环链表的操作声明 start */

/* 初始化，创建一个带头结点的空的单向循环链表 */
void InitCycleList(CycleLinkList *CL);

/* 随机产生n个元素的值，建立一个n个节点的单向循环链表 */
void CreateCycleList(CycleLinkList *CL, int n);

/* 遍历链表中的所有元素 */
void show(CycleLinkList CL);

/* 判断单向循环链表是否为空 */
int CycleListEmpty(CycleLinkList CL);

/* 将单向循环链表清空 */
int ClearCycleList(CycleLinkList *CL);

/* 获取单向循环链表中第i个元素的值 */
int GetElem(CycleLinkList CL, int i, ElemType *e);

/*  在单向循环链表中查找与给定元素值e相等的元素，如果查找成功，返回
 * 该元素在表中序号，否则返回-1
  */
int LocationElem(CycleLinkList CL, ElemType e);

/* 在单向循环链表的第i个位置之前插入新的数据元素e，链表长度加1 */
int CycyleListInsert(CycleLinkList *CL, int i, ElemType e);

/* 删除单向循环链表的第i个数据，并用e返回其值，链表长度-1 */
int CycleListDelete(CycleLinkList *CL, int i, ElemType *e);

/* 单向循环链表的操作声明 end */

#endif