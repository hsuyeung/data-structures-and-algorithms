/*单链表的定义文件*/
#include "../../common.h"
#ifndef LINK_LIST
#define LINK_LIST

/*单链表的结构定义 start*/

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode;
typedef LNode *LinkList;

/*单链表的结构定义 end*/

/*单链表具有的操作声明 start*/

/*初始化一个带头结点的空单链表*/
void InitList(LinkList *L);
/*随机产生n个元素的值，建立带表头结点的线性单链表L(头插法)*/
void CreateListHead(LinkList *L, int n);
/*随机产生n个元素的值，建立带表头结点的线性单链表L(尾插法)*/
void CreateListTail(LinkList *L, int n);
/*若单链表为空，返回true；否则返回false*/
int ListEmpty(LinkList L);
/*将单链表清空*/
int ClearList(LinkList *L);
/*将单链表L中的第i个位置元素值返回给e*/
int GetElem(LinkList L, int i, ElemType *e);
/*在单链表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功，否则返回-1*/
int LocationElem(LinkList L, ElemType e);
/*在L中第i个位置之前插入新的数据元素e，L的长度加1*/
int ListInsert(LinkList *L, int i, ElemType e);
/*删除L的第i个数据元素，并用e返回其值，L的长度减1*/
int ListDelete(LinkList *L, int i, ElemType *e);

/*单链表具有的操作声明 end*/

#endif