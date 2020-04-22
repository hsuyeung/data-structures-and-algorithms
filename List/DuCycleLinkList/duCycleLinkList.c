/* 双向循环链表很多操作和单向循环链表是相同的，
 * 所以这里只实现一部分双向循环链表与单向循环链表不同的操作
 * */
#include "duCycleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    //初始化一个空的双向循环链表
    DuCLinkList duCLinkList = NULL;
    InitDuCList(&duCLinkList);
    //判断双向循环链表是否为空
    printf("双向循环链表是否为空：%d\n", DuCListEmpty(duCLinkList));
    //使用尾插法创建一个n个随机元素的双向循环链表
    DuCLinkList duCLinkListTail = NULL;
    CreateDuCList(&duCLinkListTail, 10);
    //正序和逆序打印双向循环链表
    showByPS(duCLinkListTail);
    showByNS(duCLinkListTail);
    //在尾插法创建的链表中第五个位置之前插入一个值为250的结点
    if (DuCListInsert(&duCLinkListTail, 5, 250) == OK)
    {
        printf("插入元素成功。\n");
        showByPS(duCLinkListTail);
        showByNS(duCLinkListTail);
    }
    //删除尾插法创建的链表中第五个结点的元素
    ElemType elem = 0;
    if (DuCListDelete(&duCLinkListTail, 5, &elem) == OK)
    {
        printf("删除第5个结点的元素成功，该结点的值为：%d\n", elem);
        showByPS(duCLinkListTail);
        showByNS(duCLinkListTail);
    }

    return 0;
}

/*双向循环链表具有的操作定义 start*/

/*初始化一个带头结点的空双向循环链表*/
void InitDuCList(DuCLinkList *DCL)
{
    *DCL = (DuCLinkList)malloc(sizeof(DuCLNode));
    if (*DCL == NULL)
    {
        printf("申请内存空间失败。\n");
        exit(0);
    }
    (*DCL)->prior = *DCL;
    (*DCL)->next = *DCL;
}

/*正向打印双向循环链表的元素*/
void showByPS(DuCLinkList DCL)
{
    if (DuCListEmpty(DCL))
    {
        printf("双向循环链表为空。\n");
        exit(0);
    }
    printf("双向循环链表当前的数据为(正序)：\n");
    DuCLinkList curr = DCL->next;
    while (curr != DCL)
    {
        printf("->%d", curr->data);
        // printf("->%d(前驱为：%d)\n", curr->data, curr->prior->data);
        curr = curr->next;
    }
    printf("\n");
}

/*逆向打印双向循环链表的元素*/
void showByNS(DuCLinkList DCL)
{
    if (DuCListEmpty(DCL))
    {
        printf("双向循环链表为空。\n");
        exit(0);
    }
    printf("双向循环链表当前的数据为(逆序)：\n");
    DuCLinkList curr = DCL->prior;
    while (curr != DCL)
    {
        printf("->%d", curr->data);
        // printf("->%d(后继为：%d)\n", curr->data, curr->prior->data);
        curr = curr->prior;
    }
    printf("\n");
}

/*随机产生n个元素的值，建立带表头结点的线性双向循环链表DCL(尾插法)*/
void CreateDuCList(DuCLinkList *DCL, int n)
{
    DuCLinkList p, r;
    int i;
    //初始化随机数种子
    srand(time(0));
    //初始化一个带头结点的双向循环链表
    InitDuCList(DCL);
    //r为指向尾部的结点
    r = *DCL;
    for (i = 0; i < n; i++)
    {
        //生成新结点
        p = (DuCLinkList)malloc(sizeof(DuCLNode));
        //随机生成100以内的正整数
        p->data = rand() % 100 + 1;
        printf("当前生成的数据为：%d\n", p->data);
        //将表尾终端结点的指针指向新结点
        r->next = p;
        p->next = r;
        p->prior = r;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    //创建结束
    //尾结点的next指针域指向头结点
    r->next = *DCL;
    //头结点的prior指针域指向尾结点
    (*DCL)->prior = r;
}

/*若双向循环链表为空，返回true；否则返回false*/
int DuCListEmpty(DuCLinkList DCL)
{
    return (DCL->next == DCL) ? TRUE : FALSE;
}

/*将双向循环链表清空*/
int ClearDuCLinkList(DuCLinkList *DCL);

/*在L中第i个位置之前插入新的数据元DC素e，DCL的长度加1*/
int DuCListInsert(DuCLinkList *DCL, int i, ElemType e)
{
    int j = 1;
    DuCLinkList p = *DCL, s;
    //正向寻找第i-1个结点
    while (p->next != *DCL && j < i)
    {
        p = p->next;
        j++;
    }
    //若第i个结点不存在
    if (p->next == *DCL || j > i)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    //生成新的结点
    s = (DuCLinkList)malloc(sizeof(DuCLNode));
    s->data = e;
    s->prior = p;
    s->next = p->next;
    p->next->prior = s;
    p->next = s;
    return OK;
}

/*删除L的第i个数据元素，并用e返回其值，DCL的长度减1*/
int DuCListDelete(DuCLinkList *DCL, int i, ElemType *e)
{
    int j = 1;
    DuCLinkList p = *DCL, q;
    //遍历寻找第i-1个结点
    while (p->next != *DCL && j < i)
    {
        p = p->next;
        j++;
    }
    //若第i个结点不存在
    if (p->next == *DCL || j > i)
    {
        printf("第%d个结点不存在。\n", i);
        return ERROR;
    }
    //删除第i个结点
    q = p->next;
    //如果删除的是最后一个结点
    if (q->next == *DCL)
    {
        q->prior->next = *DCL;
        (*DCL)->prior = q->prior;
        *e = q->data;
        free(q);
        return OK;
    }
    q->prior->next = q->next;
    q->next->prior = q->prior;
    *e = q->data;
    free(q);
    return OK;
}

/*双向循环链表具有的操作定义 end*/