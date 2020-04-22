/*双向循环链表的定义文件*/
#include "../../common.h"
#ifndef DU_CYCLE_LINK_LIST
#define DU_CYCLE_LINK_LIST

/*双向循环链表的结构定义 start*/

typedef struct DuCLNode
{
    ElemType data;
    //直接前驱指针
    struct DuCLNode *prior;
    //直接后继指针
    struct DuCLNode *next;
} DuCLNode, *DuCLinkList;

/*双向循环链表的结构定义 end*/

/*双向循环链表具有的操作声明 start*/

/*初始化一个带头结点的空双向循环链表*/
void InitDuCList(DuCLinkList *DCL);
/*正向打印双向循环链表的元素*/
void showByPS(DuCLinkList DCL);
/*逆向打印双向循环链表的元素*/
void showByNS(DuCLinkList DCL);
/*随机产生n个元素的值，建立带表头结点的线性双向循环链表DCL(尾插法)*/
void CreateDuCList(DuCLinkList *DCL, int n);
/*若双向循环链表为空，返回true；否则返回false*/
int DuCListEmpty(DuCLinkList DCL);
/*将双向循环链表清空*/
int ClearDuCLinkList(DuCLinkList *DCL);
/*将双向循环链表L中的第i个位置元素值返回给e*/
int GetElem(DuCLinkList DCL, int i, ElemType *e);
/*在双向循环链表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功，否则返回-1*/
int LocationElem(DuCLinkList DCL, ElemType e);
/*在L中第i个位置之前插入新的数据元DC素e，DCL的长度加1*/
int DuCListInsert(DuCLinkList *DCL, int i, ElemType e);
/*删除L的第i个数据元素，并用e返回其值，DCL的长度减1*/
int DuCListDelete(DuCLinkList *DCL, int i, ElemType *e);

/*双向循环链表具有的操作声明 end*/

#endif