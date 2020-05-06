/*  双向链表很多操作和单链表是相同的，
 * 所以这里只实现一部分双向链表与单链表不同的操作
 *  */
#include "duLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    // 初始化一个空的双向链表
    DuLinkList duLinkList = NULL;
    InitDuList(&duLinkList);
    // 判断双向链表是否为空
    printf("双向链表是否为空：%d\n", DuListEmpty(duLinkList));
    // 使用尾插法创建一个n个元素的双向链表
    DuLinkList duLinkListTail = NULL;
    CreateDuList(&duLinkListTail, 10);
    show(duLinkListTail);
    // 在尾插法创建的链表中第五个位置之前插入一个值为250的结点
    if (DuListInsert(&duLinkListTail, 5, 250) == OK)
    {
        printf("插入元素成功，现在尾插法创建的链表的数据为：\n");
        show(duLinkListTail);
    }
    ElemType elem = 0;
    // 删除尾插法创建的链表中第五个位置的元素
    if (DuListDelete(&duLinkListTail, 5, &elem) == OK)
    {
        printf("删除第五个结点的元素成功，该结点的值为：%d\n", elem);
        show(duLinkListTail);
    }

    // 将双向链表清空
    if (ClearDuLinkList(&duLinkListTail))
    {
        printf("清空尾插法创建的双向链表成功：%d\n", DuListEmpty(duLinkListTail));
    }
    ClearDuLinkList(&duLinkListTail);

    return 0;
}

/* 双向链表具有的操作定义 start */

/* 初始化一个带头结点的空双向链表 */
void InitDuList(DuLinkList *DL)
{
    *DL = (DuLinkList)malloc(sizeof(DuLNode));
    if (*DL == NULL)
    {
        printf("申请内存空间失败。\n");
        exit(0);
    }
    (*DL)->prior = NULL;
    (*DL)->next = NULL;
}

/* 打印双向链表的元素 */
void show(DuLinkList DL)
{
    DuLinkList p = DL->next;
    int i = 1;
    while (p != NULL)
    {
        printf("第%d个元素的值是：%d,前驱是：%d\n", i, p->data, p->prior->data);
        p = p->next;
        i++;
    }
}

/* 随机产生n个元素的值，建立带表头结点的线性双向链表DL(尾插法) */
void CreateDuList(DuLinkList *DL, int n)
{
    DuLinkList p, r;
    int i;
    // 初始化随机数种子
    srand(time(0));
    // DL为整个链表
    InitDuList(DL);
    // r为指向尾部的结点
    r = *DL;
    for (i = 0; i < n; i++)
    {
        // 生成新结点
        p = (DuLinkList)malloc(sizeof(DuLNode));
        // 随机生成100以内的正整数
        p->data = rand() % 100 + 1;
        printf("当前生成的数据为：%d\n", p->data);
        // 将表尾终端结点的指针指向新结点
        r->next = p;
        p->prior = r;
        // 将当前的新结点定义为表尾终端结点
        r = p;
    }
    // 创建结束
    r->next = NULL;
}

/* 若双向链表为空，返回true；否则返回false */
int DuListEmpty(DuLinkList DL)
{
    return (DL->prior == NULL && NULL == DL->next) ? TRUE : FALSE;
}
/* 将双向链表清空 */
int ClearDuLinkList(DuLinkList *DL)
{
    if (DuListEmpty(*DL))
    {
        printf("双向链表已经是空表了，不能再空了。\n");
        return ERROR;
    }
    DuLinkList p, q;
    // p指向第一个结点
    p = (*DL)->next;
    // 没到表尾
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
    // 将头结点的指针域设置为空
    (*DL)->next = NULL;
    (*DL)->prior = NULL;
    return OK;
}

/* 在L中第i个位置之前插入新的数据元素e，DL的长度加1 */
int DuListInsert(DuLinkList *DL, int i, ElemType e)
{
    int j = 1;
    DuLinkList p = *DL, s;
    // 寻找第i-1个结点
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    // 若第i个结点不存在
    if (!p || j > i)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    // 生成新的结点
    s = (DuLinkList)malloc(sizeof(DuLNode));
    s->data = e;
    // 以下的顺序不能变
    /* 把p赋值给s的前驱 */
    s->prior = p;
    /* 把p->next赋值给s的后继 */
    s->next = p->next;
    /* 把s赋值给p->next的前驱 */
    p->next->prior = s;
    /* 把s赋值给p的后继 */
    p->next = s;
    /* 总结顺序就是：先搞定s的前驱和后继，再搞定后结点的前驱，最后解决前结点的后继 */
    return OK;
}

/* 删除L的第i个数据元素，并用e返回其值，DL的长度减1 */
int DuListDelete(DuLinkList *DL, int i, ElemType *e)
{
    int j = 1;
    DuLinkList p = *DL, q;
    // 遍历寻找第i-1个结点
    while (p->next && j < i)
    {
        p = p->next;
        j++;
    }
    // 若第i个结点不存在
    if (!(p->next) || j > i)
    {
        printf("第%d个结点不存在。\n", i);
        return ERROR;
    }
    // 删除第i个结点
    q = p->next;
    // 如果删除的是最后一个结点
    if (!(q->next))
    {
        q->prior->next = NULL;
        *e = q->data;
        free(q);
        return OK;
    }
    *e = q->data;
    /* 把p->next赋值给p->prior的后继 */
    q->prior->next = q->next;
    /* 把p->prior赋值给p->next的前驱 */
    q->next->prior = q->prior;
    /* 释放结点 */
    free(q);
    return OK;
}

/* 双向链表具有的操作定义 end */