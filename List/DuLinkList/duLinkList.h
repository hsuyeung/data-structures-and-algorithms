/*双向链表的定义文件*/
#include "../../common.h"
#ifndef DU_LINK_LIST
#define DU_LINK_LIST

/*双向链表的结构定义 start*/

typedef struct DuLNode
{
    ElemType data;
    //直接前驱指针
    struct DuLNode *prior;
    //直接后继指针
    struct DuLNode *next;
} DuLNode, *DuLinkList;

/*双向链表的结构定义 end*/

/*双向链表具有的操作声明 start*/

/*初始化一个带头结点的空双向链表*/
void InitDuList(DuLinkList *DL);
/*打印双向链表的元素*/
void show(DuLinkList DL);
/*随机产生n个元素的值，建立带表头结点的线性双向链表DL(尾插法)*/
void CreateDuList(DuLinkList *DL, int n);
/*若双向链表为空，返回true；否则返回false*/
int DuListEmpty(DuLinkList DL);
/*将双向链表清空*/
int ClearDuLinkList(DuLinkList *DL);
/*将双向链表L中的第i个位置元素值返回给e*/
int GetElem(DuLinkList DL, int i, ElemType *e);
/*在双向链表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功，否则返回-1*/
int LocationElem(DuLinkList DL, ElemType e);
/*在L中第i个位置之前插入新的数据元素e，DL的长度加1*/
int DuListInsert(DuLinkList *DL, int i, ElemType e);
/*删除L的第i个数据元素，并用e返回其值，DL的长度减1*/
int DuListDelete(DuLinkList *DL, int i, ElemType *e);

/*双向链表具有的操作声明 end*/

#endif