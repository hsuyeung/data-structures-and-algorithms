/* B树 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAXSIZE 100

// B树的阶，暂设为3
#define m 3
// 数据元素个数
#define N 17
// 字符串最大长度
#define MAX 5

typedef int Status;

// B树结点和B树的类型
typedef struct BTNode
{
    // 结点中关键字个数，即结点的大小
    int keynum;
    // 指向双亲结点
    struct BTNode *parent;
    // 结点向量类型
    struct Node
    {
        // 关键字向量
        int key;
        // 子树指针向量
        struct BTNode *ptr;
        // 记录指针向量
        int recptr;
        // key,recptr的0号单元未用
    } node[m + 1];
} BTNode, *BTree;

// B树的查找结果类型
typedef struct
{
    // 指向找到的结点
    BTNode *pt;
    // 1..m，在结点中的关键字序号
    int i;
    // 1:查找成功，O:查找失败
    int tag;
} Result;

/* 在p->node[1..keynum].key中查找i,使得p->node[i].key≤K＜p->node[i+1].key */
int Search(BTree p, int K)
{
    int i = 0, j;
    for (j = 1; j <= p->keynum; j++)
    {
        if (p->node[j].key <= K)
        {
            i = j;
        }
    }
    return i;
}

/* 在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值 */
/* tag=1，指针pt所指结点中第i个关键字等于K；否则特征值tag=0，等于K的  */
/* 关键字应插入在指针Pt所指结点中第i和第i+1个关键字之间。 */
Result SearchBTree(BTree T, int K)
{
    // 初始化，p指向待查结点，q指向p的双亲
    BTree p = T, q = NULL; /*    */
    Status found = FALSE;
    int i = 0;
    Result r;
    while (p && !found)
    {
        // p->node[i].key≤K<p->node[i+1].key
        i = Search(p, K);
        // 找到待查关键字
        if (i > 0 && p->node[i].key == K)
        {
            found = TRUE;
        }
        else
        {
            q = p;
            p = p->node[i].ptr;
        }
    }
    r.i = i;
    // 查找成功
    if (found)
    {
        r.pt = p;
        r.tag = 1;
    }
    // 查找不成功，返回K的插入位置信息
    else
    {
        r.pt = q;
        r.tag = 0;
    }
    return r;
}

/* 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中 */
void Insert(BTree *q, int i, int key, BTree ap)
{
    int j;
    // 空出(*q)->node[i+1]
    for (j = (*q)->keynum; j > i; j--)
    {
        (*q)->node[j + 1] = (*q)->node[j];
    }
    (*q)->node[i + 1].key = key;
    (*q)->node[i + 1].ptr = ap;
    (*q)->node[i + 1].recptr = key;
    (*q)->keynum++;
}

/* 将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap */
void split(BTree *q, BTree *ap)
{
    int i, s = (m + 1) / 2;
    // 生成新结点ap
    *ap = (BTree)malloc(sizeof(BTNode));
    // 后一半移入ap
    (*ap)->node[0].ptr = (*q)->node[s].ptr;
    for (i = s + 1; i <= m; i++)
    {
        (*ap)->node[i - s] = (*q)->node[i];
        if ((*ap)->node[i - s].ptr)
        {
            (*ap)->node[i - s].ptr->parent = *ap;
        }
        }
    (*ap)->keynum = m - s;
    (*ap)->parent = (*q)->parent;
    // q的前一半保留，修改keynum
    (*q)->keynum = s - 1;
}

/* 生成含信息(T,r,ap)的新的根结点&T，原T和ap为子树指针 */
void NewRoot(BTree *T, int key, BTree ap)
{
    BTree p;
    p = (BTree)malloc(sizeof(BTNode));
    p->node[0].ptr = *T;
    *T = p;
    if ((*T)->node[0].ptr)
    {
        (*T)->node[0].ptr->parent = *T;
    }
    (*T)->parent = NULL;
    (*T)->keynum = 1;
    (*T)->node[1].key = key;
    (*T)->node[1].recptr = key;
    (*T)->node[1].ptr = ap;
    if ((*T)->node[1].ptr)
    {
        (*T)->node[1].ptr->parent = *T;
    }
}

/* 在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。若引起 */
/* 结点过大,则沿双亲链进行必要的结点分裂调整,使T仍是m阶B树。 */
void InsertBTree(BTree *T, int key, BTree q, int i)
{
    BTree ap = NULL;
    Status finished = FALSE;
    int s;
    int rx;
    rx = key;
    while (q && !finished)
    {
        // 将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
        Insert(&q, i, rx, ap);
        if (q->keynum < m)
        {
            // 插入完成
            finished = TRUE;
        }
        else
        {
            // 分裂结点*q
            s = (m + 1) / 2;
            rx = q->node[s].recptr;
            // 将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap
            split(&q, &ap);
            q = q->parent;
            if (q)
            {
                // 在双亲结点*q中查找rx->key的插入位置
                i = Search(q, key);
            }
        }
    }
    // T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap
    if (!finished)
    {
        //生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针
        NewRoot(T, rx, ap);
    }
}

// TraverseDSTable()调用的函数
void print(BTNode c, int i)
{
    printf("(%d)", c.node[i].key);
}

int main()
{
    int r[N] = {22, 16, 41, 58, 8, 11, 12, 16, 17, 22, 23, 31, 41, 52, 58, 59, 61};
    BTree T = NULL;
    Result s;
    int i;
    for (i = 0; i < N; i++)
    {
        s = SearchBTree(T, r[i]);
        if (!s.tag)
            InsertBTree(&T, r[i], s.pt, s.i);
    }
    printf("\n请输入待查找记录的关键字: ");
    scanf("%d", &i);
    s = SearchBTree(T, i);
    if (s.tag)
    {
        print(*(s.pt), s.i);
    }
    else
    {
        printf("没找到");
    }

    printf("\n");

    return 0;
}
