#include "BiTreeArray.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    Position p;
    TElemType e;
    SqBiTree T;

    // 构建空二叉树
    InitBiTree(T);
    // 按照层序次序给二叉树赋值
    CreateBiTree(T);
    // 判断是否为空
    printf("建立二叉树后，树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    // 二叉树的根
    if (Root(T, &e))
    {
        printf("二叉树的根为：%d\n", e);
    }
    else
    {
        printf("树为空，没有根。\n");
    }
    // 二叉树的四种遍历方式
    printf("层序遍历二叉树:\n");
    LevelOrderTraverse(T);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    printf("中序遍历二叉树:\n");
    InOrderTraverse(T);
    printf("后序遍历二叉树:\n");
    PostOrderTraverse(T);
    printf("修改层号3本层序号2的结点值。");
    p.level = 3;
    p.order = 2;
    // 获取指定位置结点的值
    e = Value(T, p);
    printf("待修改结点的原值为%d请输入新值:", e);
    fflush(stdin);
    scanf("%d", &e);
    // 给指定位置结点赋值
    Assign(T, p, e);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    // 打印与给定值相等的结点的双亲、左右孩子、左右兄弟
    printf("结点值为%d的双亲为%d,左右孩子分别为", e, Parent(T, e));
	printf("%d,%d,左右兄弟分别为", LeftChild(T, e), RightChild(T, e));
	printf("%d,%d\n", LeftSibling(T, e), RightSibling(T, e));
    // 清空二叉树
    ClearBiTree(T);
	printf("清除二叉树后，树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    if (Root(T, &e))
    {
        printf("二叉树的根为：%d\n", e);
    }
    else
    {
        printf("树为空，没有根。\n");
    }
    return 0;
}

/* 二叉树顺序结构具有的操作声明 start */

/* 打印二叉树结点的数据 */
Status visit(TElemType c)
{
    printf("%d ", c);
    return OK;
}

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
Status InitBiTree(SqBiTree T)
{
    int i;
    for (i = 0; i < MAX_TREE_SIZE; i++)
    {
        // 初值为空
        T[i] = Nil;
    }
    return OK;
}

/* 按层序次序输入二叉树中结点的值(字符型或整型)：构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T)
{
    int i = 0;
    printf("请按层序输入结点的值(整型)，0表示空结点，输入任意非数字字符结束。结点数≤%d:\n", MAX_TREE_SIZE);
    TElemType elem = Nil;
    while ((scanf("%d", &elem) != 0) && (i < MAX_TREE_SIZE))
    {
        T[i] = elem;

        // 此结点不是根、无双亲且不为空
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil)
        {
            printf("出现无双亲的非根结点%d\n", T[i]);
            exit(0);
        }
        i++;
    }
    while (i < MAX_TREE_SIZE)
    {
        // 将空赋值给T的后面的结点
        T[i] = Nil;
        i++;
    }
    return OK;
}

/* 在顺序存储结构中，两函数的操作完全一样 */
#define ClearBiTree InitBiTree

/* 初始条件：二叉树T存在 */
/* 操作结果：若T为空二叉树：则返回TRUE：否则FALSE */
Status BiTreeEmpty(SqBiTree T)
{
    // 根结点为空,则树空
    return (T[0] == Nil) ? TRUE : FALSE;
}

/* 初始条件：二叉树T存在。操作结果：返回T的深度 */
int BiTreeDepth(SqBiTree T)
{
    int i, j = -1;
    // 找到最后一个结点
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--)
    {
        if (T[i] != Nil)
        {
            // 找到非空的结点就跳出
            break;
        }
    }
    i++;
    do
    {
        j++;
    } while (i >= powl(2, j)); //计算2的j次幂

    return j;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：当T不空：用e返回T的根：返回OK;否则返回ERROR：e无定义 */
Status Root(SqBiTree T, TElemType *e)
{
    // 树为空
    if (BiTreeEmpty(T))
    {
        return ERROR;
    }
    else
    {
        *e = T[0];
        return OK;
    }
}

/* 初始条件：二叉树T存在：e是T中某个结点(的位置) */
/* 操作结果：返回处于位置e(层：本层序号)的结点的值 */
TElemType Value(SqBiTree T, Position e)
{
    return T[(int)powl(2, e.level - 1) + e.order - 2];
}

/* 初始条件：二叉树T存在：e是T中某个结点(的位置) */
/* 操作结果：给处于位置e(层：本层序号)的结点赋新值value */
Status Assign(SqBiTree T, Position e, TElemType value)
{
    // 将层、本层序号转为矩阵的序号(数组下标)
    int i = (int)powl(2, e.level - 1) + e.order - 2;
    // 给该结点赋非空值但该结点的双亲为空
    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)
    {
        printf("该结点赋非空值但该结点的双亲为空\n");
        return ERROR;
    }
    // 给该结点赋空值该结点但有叶子(不空)
    else if (value == Nil && (T[i * 2 + 1] != Nil || T[i * 2 + 2] != Nil))
    {
        printf("该结点赋空值该结点但有叶子(不空)\n");
        return ERROR;
    }
    T[i] = value;
    return OK;
}

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：若e是T的非根结点：则返回它的双亲：否则返回＂空＂ */
TElemType Parent(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
    {
        return Nil;
    }
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        // 找到e
        if (T[i] == e)
        {
            // 返回e的双亲
            return T[(i + 1) / 2 - 1];
        }
    }
    // 没找到e
    return Nil;
}

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的左孩子。若e无左孩子：则返回＂空＂ */
TElemType LeftChild(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
    {
        return Nil;
    }
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        // 找到e
        if (T[i] == e)
        {
            // 返回e的左孩子
            return T[i * 2 + 1];
        }
    }
    // 没找到e
    return Nil;
}

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的右孩子。若e无右孩子：则返回＂空＂ */
TElemType RightChild(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
    {
        return Nil;
    }
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        // 找到e
        if (T[i] == e)
        {
            // 返回e的右孩子
            return T[i * 2 + 2];
        }
    }
    // 没找到e
    return Nil;
}

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟：则返回＂空＂ */
TElemType LeftSibling(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
    {
        return Nil;
    }
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        // 找到e且其序号为偶数(是右孩子)
        if ((T[i] == e) && (i % 2 == 0))
        {
            // 返回e的左兄弟
            return T[i - 1];
        }
    }
    // 没找到e
    return Nil;
}

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟：则返回＂空＂ */
TElemType RightSibling(SqBiTree T, TElemType e)
{
    int i;
    // 空树
    if (T[0] == Nil)
    {
        return Nil;
    }
    for (i = 1; i <= MAX_TREE_SIZE - 1; i++)
    {
        // 找到e且其序号为偶数(是右孩子)
        if ((T[i] == e) && (i % 2))
        {
            // 返回e的右兄弟
            return T[i + 1];
        }
    }
    // 没找到e
    return Nil;
}

/* PreOrderTraverse()调用 */
void PreTraverse(SqBiTree T, int e)
{
    // 访问根节点
    visit(T[e]);
    // 左子树不空，前序遍历左子树
    if (T[2 * e + 1] != Nil)
    {
        PreTraverse(T, 2 * e + 1);
    }
    // 右子树不空，前序遍历右子树
    if (T[2 * e + 2] != Nil)
    {
        PreTraverse(T, 2 * e + 2);
    }
}

/* 初始条件：二叉树存在 */
/* 操作结果：前序遍历T。 */
Status PreOrderTraverse(SqBiTree T)
{
    // 树不空
    if (!BiTreeEmpty(T))
    {
        PreTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

/* InOrderTraverse()调用 */
void InTraverse(SqBiTree T, int e)
{
    // 左子树不空，中序遍历左子树
    if (T[2 * e + 1] != Nil)
    {
        InTraverse(T, 2 * e + 1);
    }
    // 访问根节点
    visit(T[e]);
    // 右子树不空，中序遍历右子树
    if (T[2 * e + 2] != Nil)
    {
        InTraverse(T, 2 * e + 2);
    }
}

/* 初始条件：二叉树存在 */
/* 操作结果：中序遍历T。 */
Status InOrderTraverse(SqBiTree T)
{
    // 树不空
    if (!BiTreeEmpty(T))
    {
        InTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

/* PostOrderTraverse()调用 */
void PostTraverse(SqBiTree T, int e)
{
    // 左子树不空，后序遍历左子树
    if (T[2 * e + 1] != Nil)
    {
        PostTraverse(T, 2 * e + 1);
    }
    // 右子树不空，后序遍历右子树
    if (T[2 * e + 2] != Nil)
    {
        PostTraverse(T, 2 * e + 2);
    }
    // 访问根节点
    visit(T[e]);
}

/* 初始条件：二叉树T存在 */
/* 操作结果：后序遍历T。 */
Status PostOrderTraverse(SqBiTree T)
{
    // 树不空
    if (!BiTreeEmpty(T))
    {
        PostTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T)
{
    int i = MAX_TREE_SIZE - 1, j;
    while (T[i] == Nil)
    {
        // 找到最后一个非空结点的序号
        i--;
    }
    // 从根结点起,按层序遍历二叉树
    for (j = 0; j <= i; j++)
    {
        if (T[j] != Nil)
        {
            // 只遍历非空的结点
            visit(T[j]);
        }
    }
    printf("\n");
}

/* 逐层、按本层序号输出二叉树 */
void Print(SqBiTree T)
{
    int j, k;
    Position p;
    TElemType e;
    for (j = 1; j <= BiTreeDepth(T); j++)
    {
        printf("第%d层: ", j);
        for (k = 1; k <= powl(2, j - 1); k++)
        {
            p.level = j;
            p.order = k;
            e = Value(T, p);
            if (e != Nil)
                printf("%d:%d ", k, e);
        }
        printf("\n");
    }
}

/* 二叉树顺序结构具有的操作声明 end */