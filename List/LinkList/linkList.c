#include "linkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    //初始化一个空的单链表
    LinkList linkList = NULL;
    InitList(&linkList);
    //判断单链表是否为空
    printf("单链表是否为空：%d\n", ListEmpty(linkList));
    //使用头插法创建一个单链表
    LinkList linkListHead = NULL;
    CreateListHead(&linkListHead, 10);
    printf("头插法创建的单链表是否为空：%d\n", ListEmpty(linkListHead));
    LinkList p = linkListHead->next;
    printf("头插法创建的单链表数据为：\n");
    while (p)
    {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");
    //使用尾插法创建一个单链表
    LinkList linkListTail = NULL;
    CreateListTail(&linkListTail, 10);
    printf("尾插法创建的单链表是否为空：%d\n", ListEmpty(linkListTail));
    p = linkListTail->next;
    printf("尾插法创建的单链表数据为：\n");
    while (p)
    {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");
    //查找第五个位置的元素
    ElemType elem = -1;
    if (GetElem(linkListHead, 5, &elem) == OK)
    {
        printf("头插法链表的第五个元素为：%d\n", elem);
    }
    else
    {
        printf("头插法链表中不存在第五个元素。\n");
    }
    //查找elem是否在链表中存在
    int index = LocationElem(linkListHead, elem);
    if (index != -1)
    {
        printf("元素%d在头插法创建的链表中存在。它是第%d个元素\n", elem, index);
    }
    else
    {
        printf("元素%d在头插法创建的链表中不存在。\n", elem);
    }
    //在头插法创建的链表中第五个位置之前插入一个值为250的结点
    if (ListInsert(&linkListHead, 5, 250) == OK)
    {
        printf("插入元素成功，现在头插法创建的链表的数据为：\n");
        p = linkListHead->next;
        while (p)
        {
            printf("->%d", p->data);
            p = p->next;
        }
        printf("\n");
    }
    //删除头插法创建的链表中第五个结点的元素
    if (ListDelete(&linkListHead, 5, &elem) == OK)
    {
        printf("删除第5个结点的元素成功，该结点的值为：%d\n", elem);
        printf("现在头插法创建的链表的数据为：\n");
        p = linkListHead->next;
        while (p)
        {
            printf("->%d", p->data);
            p = p->next;
        }
        printf("\n");
    }

    //将尾插法和头插法创建的单链表清空
    if (ClearList(&linkListHead))
    {
        printf("清空头插法创建的链表成功：%d\n", ListEmpty(linkListHead));
    }
    if (ClearList(&linkListTail))
    {
        printf("清空尾插法创建的链表成功：%d\n", ListEmpty(linkListTail));
    }

    return 0;
}

/*单链表具有的操作定义 start*/

/*初始化一个带头结点的空单链表*/
void InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(LNode));
    if (*L == NULL)
    {
        printf("申请内存空间失败。\n");
        exit(0);
    }
    (*L)->next = NULL;
}

/*随机产生n个元素的值，建立带表头结点的线性单链表L(头插法)*/
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    //初始化随机数种子
    srand(time(0));
    *L = (LinkList)malloc(sizeof(LNode));
    //先建立一个带头结点的单链表
    InitList(L);
    for (i = 0; i < n; i++)
    {
        //生成新的结点
        p = (LinkList)malloc(sizeof(LNode));
        //随机生成100以内的正整数
        p->data = rand() % 100 + 1;
        p->next = (*L)->next;
        //插入到表头
        (*L)->next = p;
    }
}

/*随机产生n个元素的值，建立带表头结点的线性单链表L(尾插法)*/
void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    //初始化随机数种子
    srand(time(0));
    //L为整个链表
    InitList(L);
    //r为指向尾部的结点
    r = *L;
    for (i = 0; i < n; i++)
    {
        //生成新结点
        p = (LinkList)malloc(sizeof(LNode));
        //随机生成100以内的正整数
        p->data = rand() % 100 + 1;
        //将表尾终端结点的指针指向新结点
        r->next = p;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    //创建结束
    r->next = NULL;
}

/*若单链表为空，返回true；否则返回false*/
int ListEmpty(LinkList L)
{
    return NULL == L->next ? TRUE : FALSE;
}

/*将单链表清空*/
int ClearList(LinkList *L)
{
    if (ListEmpty(*L))
    {
        printf("单链表已经是空表了，不能再空了。\n");
        return ERROR;
    }
    LinkList p, q;
    //p指向第一个结点
    p = (*L)->next;
    //没到表尾
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    //将头结点的指针域设置为空
    (*L)->next = NULL;
    return OK;
}

/*将单链表L中的第i个元素值返回给e*/
int GetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;
    //让p指向链表L的第一个结点
    p = L->next;
    //j为计数器
    j = 1;
    //当p不为空并且j小于i时，循环继续，为了找到第i个元素
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    //第i个结点不存在
    if (!p || j > i)
    {
        return ERROR;
    }
    //获取第i个结点的数据
    *e = p->data;
    return OK;
}

/*在单链表L中查找与给定元素值e相等的第一个元素的位置，如果查找成功，返回该元素在表中序号表示成功，否则返回-1*/
int LocationElem(LinkList L, ElemType e)
{
    LinkList p = L->next;
    //i用于计数当前元素的位置
    int i = 1;
    while (p)
    {
        if (p->data == e)
        {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;
}

/*在L中第i个位置之前插入新的数据元素e，L的长度加1*/
int ListInsert(LinkList *L, int i, ElemType e)
{
    int j = 1;
    LinkList p = *L, s;
    //寻找第i-1个结点
    while (p && j < i)
    {
        p = p->next;
        ++j;
    }
    //若第i个结点不存在
    if (!p || j > i)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    //生成新的结点
    s = (LinkList)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/*删除L的第i个数据元素，并用e返回其值，L的长度减1*/
int ListDelete(LinkList *L, int i, ElemType *e)
{
    int j = 1;
    LinkList p = *L, q;
    //遍历寻找第i-1个结点
    while (p->next && j < i)
    {
        p = p->next;
        ++j;
    }
    //若第i个结点不存在
    if (!(p->next) || j > i)
    {
        printf("第%d个结点不存在。\n", i);
        return ERROR;
    }
    //删除第i个结点
    q = p->next;
    //将q的后继赋值给p的后继
    p->next = q->next;
    //将q结点中的数据给e
    *e = q->data;
    //释放内存
    free(q);
    return OK;
}

/*顺序单链表具有的操作定义 end*/
