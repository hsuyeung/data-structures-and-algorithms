#include "cycleLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    //初始化一个空的单向循环链表
    CycleLinkList cycleLinkList = NULL;
    InitCycleList(&cycleLinkList);
    //判断单向循环链表是否为空
    printf("单向循环链表是否为空：%d\n", CycleListEmpty(cycleLinkList));
    //使用尾插法创建一个单链表
    CycleLinkList cycleLinkListTail = NULL;
    CreateCycleList(&cycleLinkListTail, 10);
    printf("尾插法创建的单向循环链表是否为空：%d\n", CycleListEmpty(cycleLinkListTail));
    show(cycleLinkListTail);
    //获取单向循环链表中的第5个元素的值
    ElemType elem = 0;
    if (GetElem(cycleLinkListTail, 5, &elem) == OK)
    {
        printf("单向循环链表中的第5个元素的值为：%d\n", elem);
    }
    else
    {
        printf("第5个结点不存在。\n");
    }
    //查找elem是否在单向循环链表中存在
    int index = LocationElem(cycleLinkListTail, elem);
    if (index != -1)
    {
        printf("元素%d在尾插法创建的链表中存在。它是第%d个元素\n", elem, index);
    }
    else
    {
        printf("元素%d在尾插法创建的链表中不存在。\n", elem);
    }
    //在头插法创建的链表中第五个位置之前插入一个值为250的结点
    if (CycyleListInsert(&cycleLinkListTail, 5, 250) == OK)
    {
        printf("插入元素成功,");
        show(cycleLinkListTail);
    }
    //删除尾插法创建的链表中第五个结点的元素
    if (CycleListDelete(&cycleLinkListTail, 5, &elem) == OK)
    {
        printf("删除第5个结点的元素成功，该结点的值为：%d\n", elem);
        show(cycleLinkListTail);
    }
    //将尾插法创建的单向循环链表清空
    if (ClearCycleList(&cycleLinkListTail))
    {
        printf("清空尾插法创建的单向循环链表成功：%d\n", CycleListEmpty(cycleLinkListTail));
    }
    ClearCycleList(&cycleLinkListTail);
    show(cycleLinkListTail);

    return 0;
}

/*单向循环链表具有的操作定义 start*/

/*初始化，创建一个带头结点的空的单向循环链表*/
void InitCycleList(CycleLinkList *CL)
{
    *CL = (CycleLinkList)malloc(sizeof(CLNode));
    if (*CL == NULL)
    {
        printf("申请内存空间失败。\n");
        exit(0);
    }
    (*CL)->next = *CL;
}

/*随机产生n个元素的值，建立一个n个节点的单向循环链表，这里默认实现尾插法*/
void CreateCycleList(CycleLinkList *CL, int n)
{
    CycleLinkList p, r;
    int i;
    //初始化随机数种子
    srand(time(0));
    //先创建一个空的单向循环链表
    InitCycleList(CL);
    //r为指向尾部的结点
    r = *CL;
    for (i = 0; i < n; i++)
    {
        //生成新结点
        p = (CycleLinkList)malloc(sizeof(CLNode));
        //随机生成100以内的正整数
        p->data = rand() % 100 + 1;

        printf("现在插入的数据为：%d\n", p->data);

        //将表尾终端结点的指针指向新结点
        r->next = p;
        //将当前的新结点定义为表尾终端结点
        r = p;
    }
    //创建结束(最后一个结点的指针域指向头结点)
    r->next = *CL;
}

/*遍历链表中的所有元素*/
void show(CycleLinkList CL)
{
    if (CycleListEmpty(CL))
    {
        printf("单向循环链表为空。\n");
        exit(0);
    }
    printf("单向循环链表当前的数据为：\n");
    CycleLinkList curr = CL->next;
    while (curr != CL)
    {
        printf("->%d", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

/*判断单向循环链表是否为空*/
int CycleListEmpty(CycleLinkList CL)
{
    return CL->next == CL ? TRUE : FALSE;
}

/*将单向循环链表清空*/
int ClearCycleList(CycleLinkList *CL)
{
    if (CycleListEmpty(*CL))
    {
        printf("单向循环链表已经是空表了，不能再空了。\n");
        return ERROR;
    }
    CycleLinkList p, q;
    //p指向第一个结点
    p = (*CL)->next;
    //一直循环到表尾
    while (p != *CL)
    {
        q = p->next;
        free(p);
        p = q;
    }
    //将头结点的指针域指向自己
    (*CL)->next = *CL;
    return OK;
}

/*获取单向循环链表中第i个元素的值*/
int GetElem(CycleLinkList CL, int i, ElemType *e)
{
    //j为计数器
    int j = 1;
    //p指向单向循环链表的第一个结点
    CycleLinkList p = CL->next;
    //当p没有到尾部并且j小于i时才循环，为了找到第i个元素
    while (p != CL && j < i)
    {
        p = p->next;
        j++;
    }
    //若第i个结点不存在
    if (p == CL || j > i)
    {
        return ERROR;
    }
    //获取第i个结点的数据
    *e = p->data;
    return OK;
}

/* 在单向循环链表中查找与给定元素值e相等的元素，如果查找成功，返回
 * 该元素在表中序号，否则返回-1
 */
int LocationElem(CycleLinkList CL, ElemType e)
{
    CycleLinkList p = CL->next;
    //i用于技术当前元素的位置
    int i = 1;
    while (p != CL)
    {
        printf("当前比较的元素为：%d\n", p->data);
        if (p->data == e)
        {
            return i;
        }
        p = p->next;
        i++;
    }
    return -1;
}

/*在单向循环链表的第i个位置之前插入新的数据元素e，链表长度加1*/
int CycyleListInsert(CycleLinkList *CL, int i, ElemType e)
{
    int j = 1;
    CycleLinkList p = *CL, s;
    //寻找第i-1个结点
    while (p->next != *CL && j < i)
    {
        p = p->next;
        j++;
    }
    //若第i个结点不存在
    if (p->next == *CL || j > i)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    //生成新的结点
    s = (CycleLinkList)malloc(sizeof(CLNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

/*删除单向循环链表的第i个数据，并用e返回其值，链表长度-1*/
int CycleListDelete(CycleLinkList *CL, int i, ElemType *e)
{
    int j = 1;
    CycleLinkList p = *CL, q;
    //遍历循环找第i-1个结点
    while (p->next != *CL && j < i)
    {
        p = p->next;
        j++;
    }
    //若第i个结点不存在
    if (p->next == *CL || j > i)
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

/*单向循环链表具有的操作定义 end*/