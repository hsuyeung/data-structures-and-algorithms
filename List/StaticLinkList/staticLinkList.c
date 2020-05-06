#include "staticLinkList.h"
#include <stdio.h>

int main(void)
{
    // 这两个语句是一样的效果，都是创建一个MAX_SIZE个元素的静态链表
    StaticLinkList staticLinkList;
    //  Component staticLinkList[MAX_SIZE];
    if (InitList(staticLinkList) == OK)
    {
        printf("当前备用链表的游标分别为：\n");
        int i;
        for (i = 0; i < MAX_SIZE; i++)
        {
            printf("->%d", staticLinkList[i].cur);
        }
        printf("\n");
    }
    printf("静态链表当前长度为：%d。\n", ListLength(staticLinkList));
    // 给静态链表插入元素
    ElemType elem = 0;
    int i = 1;
    while (scanf("%d", &elem) != 0)
    {
        ListInsert(staticLinkList, i++, elem);
    }
    printf("当前静态链表的元素分别为：\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("->%d(%d)", staticLinkList[i].data, staticLinkList[i].cur);
    }
    printf("\n");
    printf("静态链表当前长度为：%d。\n", ListLength(staticLinkList));
    // 删除第五个数据元素
    if (ListDelete(staticLinkList, 5) == OK)
    {
        printf("删除第5个元素成功。\n");
        printf("当前静态链表的元素分别为：\n");
        for (i = 0; i < MAX_SIZE; i++)
        {
            printf("->%d(%d)", staticLinkList[i].data, staticLinkList[i].cur);
        }
        printf("\n");
        printf("静态链表当前长度为：%d。\n", ListLength(staticLinkList));
    }
    // 再次在第一个位置插入数据
    fflush(stdin);
    while (scanf("%d", &elem) != 0)
    {
        ListInsert(staticLinkList, 1, elem);
    }
    printf("当前静态链表的元素分别为：\n");
    for (i = 0; i < MAX_SIZE; i++)
    {
        printf("->%d(%d)", staticLinkList[i].data, staticLinkList[i].cur);
    }
    printf("\n");
    printf("静态链表当前长度为：%d。\n", ListLength(staticLinkList));
    // 查找值为555的元素所在位置
    int index = -1;
    if ((index = LocElem(staticLinkList, 555)) != -1)
    {
        printf("值为555的元素的下标为：%d\n", index);
    }
    else
    {
        printf("对不起，没有找到值为555的元素。\n");
    }
    
    

    return 0;
}

/* 静态链表具有的操作定义 start */

/* 初始化，创建一个备用链表 */
int InitList(StaticLinkList space)
{
    int i;
    for (i = 0; i < MAX_SIZE - 1; i++)
    {
        space[i].cur = i + 1;
    }
    // 因为目前静态链表为空，所以最后一个元素的cur为0
    space[MAX_SIZE - 1].cur = 0;
    return OK;
}

/*  从备用链表中分配一个结点用于插入数据,
 * 若备用空间链表非空，则返回分配的结点下标，否则返回0
  */
int Malloc_SLL(StaticLinkList space)
{
    // 当前数组第一个元素的cur存的值就是要返回的第一个备用空闲的下标
    int i = space[0].cur;
    if (space[0].cur)
    {
        // 由于要拿出一个分量来使用了，所以就得把它的下一个分量用来做备用
        space[0].cur = space[i].cur;
    }
    return i;
}

/* 在静态链表在L中第i个元素之前插入新的数据元素e */
int ListInsert(StaticLinkList L, int i, ElemType e)
{
    int j, k, l;
    // 注意k首先是最后一个元素的下标
    k = MAX_SIZE - 1;
    if (i < 1 || i > ListLength(L) + 1)
    {
        printf("插入位置不合法。\n");
        return ERROR;
    }
    // 获取空闲分量的下标
    j = Malloc_SLL(L);
    if (j)
    {
        // 将数据赋值给此分量的data
        L[j].data = e;
        // 找到第i个元素的位置
        for (l = 1; l <= i - 1; l++)
        {
            k = L[k].cur;
        }
        // 把第i个元素之前的cur赋值给新元素的cur
        L[j].cur = L[k].cur;
        // 把新元素的下标赋值给第i个元素之前元素的cur
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

/* 将下标为k的空闲结点回收到备用链表 */
void Free_SLL(StaticLinkList space, int k)
{
    // 把第一个元素的cur值赋给要删除的分量的cur
    space[k].cur = space[0].cur;
    // 把要删除的分量下标赋值给第一个元素的cur
    space[0].cur = k;
}

/* 删除在静态链表L中第i个数据元素e(即下标为i-1的) */
int ListDelete(StaticLinkList L, int i)
{
    int j, k;
    if (i < 1 || i > ListLength(L))
    {
        printf("删除位置不合理。\n");
        return ERROR;
    }
    k = MAX_SIZE - 1;
    for (j = 1; j < i - 1; j++)
    {
        k = L[k].cur;
    }
    j = L[k].cur;
    L[k].cur = L[j].cur;
    Free_SLL(L, j);
    return OK;
}

/* 求静态链表的长度,返回L中数据元素个数 */
int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAX_SIZE - 1].cur;
    while (i)
    {
        i = L[i].cur;
        j++;
    }
    return j;
}

/* 在静态链表中查找与元素e值相等的元素的下标(位置)，找不到就返回-1 */
int LocElem(StaticLinkList L, ElemType e)
{
    int i = L[MAX_SIZE - 1].cur;
    // 这个算法有问题，当要查找的元素在最后一个位置时就会查不到
    //  while (L[i].cur)
    //  {
    //      printf("当前比较的元素值为：%d\n", L[i].data);
    //      if (e == L[i].data)
    //      {
    //          return i;
    //      }
    //      i = L[i].cur;
    //  }
    int j = 0;
    while (j < ListLength(L))
    {
        printf("当前比较的元素值为：%d\n", L[i].data);
        if (e == L[i].data)
        {
            return i;
        }
        j++;
        i = L[i].cur;
    }
    return -1;
}

/* 静态链表具有的操作定义 end */