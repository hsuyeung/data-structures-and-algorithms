#include "sqList.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //创建一个空的顺序线性表
    SqList sqList = InitList();
    printf("线性表长度为：%d\n", sqList.length);
    //判断顺序线性表是否为空
    printf("线性表是否为空：%d\n", ListEmpty(sqList));
    //给顺序线性表添加元素
    ElemType elem;
    int i = 0;
    while ((scanf("%d", &elem)) != 0 && sqList.length < MAX_SIZE)
    {
        sqList.data[i++] = elem;
        sqList.length++;
    }
    printf("线性表数据为：\n");
    for (i = 0; i < sqList.length; i++)
    {
        printf("%d", sqList.data[i]);
        if (i != sqList.length - 1)
        {
            printf("->");
        }
    }
    printf("\n");
    printf("线性表长度为：%d\n", sqList.length);
    //将顺序线性表中第5个位置的数据获取出来
    if (GetElem(sqList, 5, &elem))
    {
        printf("第5个位置的数据为：%d。\n", elem);
    }
    //在顺序线性表中查找值为5的元素是否存在
    int index;
    if ((index = LocationElem(sqList, 5)) == -1)
    {
        printf("值为5的元素不存在。\n");
    }
    else
    {
        printf("值为5的元素的下标为%d，是第%d个元素。\n", index, index + 1);
    }
    //在顺序线性表第五个元素之前插入值为250的元素
    if (ListInsert(&sqList, 5, 250) == OK)
    {
        printf("插入元素成功。现在顺序线性表的数据为：\n");
        for (i = 0; i < sqList.length; i++)
        {
            printf("%d", sqList.data[i]);
            if (i != sqList.length - 1)
            {
                printf("->");
            }
        }
        printf("\n");
        printf("线性表长度为：%d\n", sqList.length);
    }
    //在顺序线性表中删除第五个元素
    if (ListDelete(&sqList, 5, &elem) == OK)
    {
        printf("删除第五个元素成功。删除的元素值为：%d，现在顺序线性表的数据为：\n", elem);
        for (i = 0; i < sqList.length; i++)
        {
            printf("%d", sqList.data[i]);
            if (i != sqList.length - 1)
            {
                printf("->");
            }
        }
        printf("\n");
        printf("线性表长度为：%d\n", sqList.length);
    }
    

    return 0;
}

/*顺序线性表具有的操作定义 start*/

/*初始化操作，建立一个空的线性表*/
SqList InitList()
{
    SqList sqList;
    sqList.length = 0;
    return sqList;
}
/*若线性表为空，返回true；否则返回false*/
int ListEmpty(SqList L)
{
    return L.length == 0 ? TRUE : FALSE;
}
/*将线性表清空*/
void ClearList(SqList *L)
{
    L->length = 0;
}
/*将线性表L中的第i个位置元素值返回给e*/
int GetElem(SqList L, int i, ElemType *e)
{
    if (ListEmpty(L))
    {
        printf("线性表为空表。\n");
        return ERROR;
    }
    else if (i < 1 || i > L.length)
    {
        printf("查找位置不合理。\n");
        return ERROR;
    }
    *e = L.data[i - 1];
    return OK;
}
/*在线性表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功*/
int LocationElem(SqList L, ElemType e)
{
    int i;
    for (i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
        {
            return i;
        }
    }
    return -1;
}
/*在L中第i个位置之前插入新的数据元素e，L的长度加1*/
int ListInsert(SqList *L, int i, ElemType e)
{
    int k;
    if (L->length == MAX_SIZE)
    {
        printf("线性表已满。\n");
        return ERROR;
    }
    else if (i < 1 || i > L->length + 1)
    {
        printf("插入位置不合理。\n");
        return ERROR;
    }
    /*若插入的数据在表中间*/
    if (i <= L->length)
    {
        /*将要插入位置后数据元素向后移动一位*/
        for (k = L->length - 1; k >= i - 1; k--)
        {
            L->data[k + 1] = L->data[k];
        }
    }
    /*插入元素*/
    L->data[i - 1] = e;
    L->length++;
    return OK;
}

/*删除L的第i个数据元素，并用e返回其值，L的长度减1*/
int ListDelete(SqList *L, int i, ElemType *e)
{
    int k;
    if (ListEmpty(*L))
    {
        printf("线性表为空表。\n");
        return ERROR;
    }
    if (i < 1 || i > L->length)
    {
        printf("删除位置不合理。\n");
        return ERROR;
    }
    *e = L->data[i - 1];
    /*如果删除的不是最后一个位置*/
    if (i < L->length)
    {
        /*将删除位置后继元素前移*/
        for (k = i; k < L->length; k++)
        {
            L->data[k - 1] = L->data[k];
        }
    }
    L->length--;
    return OK;
}

/*顺序线性表具有的操作定义 end*/