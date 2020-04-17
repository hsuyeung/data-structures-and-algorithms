/*顺序线性表的定义文件*/
#ifndef SQLIST
#define SQLIST

/*最大容量定义 start*/
#define MAX_SIZE 20
/*最大容量定义 end*/

/*状态常量定义 start*/
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
/*状态常量定义 end*/

/*数据元素类型定义 start*/
typedef int ElemType;
/*数据元素类型定义 end*/

/*顺序存储线性表结构定义 start*/
typedef struct
{
    /*数组存储数据元素，最大容量为MAXSIZE*/
    ElemType data[MAX_SIZE];
    /*线性表当前长度*/
    int length;
} SqList;
/*顺序存储线性表结构定义 end*/

/*顺序线性表具有的操作声明 start*/
/*初始化线性表*/
void InitList(SqList *L);
/*若线性表为空，返回true；否则返回false*/
int ListEmpty(SqList L);
/*将线性表清空*/
void ClearList(SqList *L);
/*将线性表L中的第i个位置元素值返回给e*/
void GetElem(SqList L, int i, ElemType *e);
/*在线性表L中查找与给定元素值e相等的元素，如果查找成功，返回该元素在表中序号表示成功*/
int LocationElem(SqList L, ElemType e);
/*顺序线性表具有的操作声明 end*/

#endif