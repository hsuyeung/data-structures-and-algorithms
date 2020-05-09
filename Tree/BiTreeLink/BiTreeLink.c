#include "BiTreeLink.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i;
    BiTree T;
    TLElemType e1 = '#';

    // 初始化构造一棵空二叉树
    InitBiTree(&T);
    // 给字符串赋值
    //StrAssign(str, "ABDH#K###E##CFI###G#J##");
    StrAssign(str, "ABD#E###C#FG#I###");

    // 给二叉树赋值
    CreateBiTree(&T);
    // 判断二叉树是否为空
	printf("构造空二叉树后，树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    // 获取二叉树根节点值
    e1 = Root(T);
    printf("二叉树的根为：%c", e1);
    // 二叉链表的三种遍历方式
    printf("\n前序遍历二叉树：");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树：");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树：");
	PostOrderTraverse(T);
    ClearBiTree(&T);
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
    i = Root(T);
    if(i == '#')
	{
        printf("树空，无根\n");
    }
    
    return 0;
}

/* 二叉树链式结构具有的操作定义 start */

/* 打印结点的值 */
Status visit(TLElemType e)
{
    printf("%c ", e);
    return OK;
}

/* 给字符串T赋值为chars */
Status StrAssign(String T, char *chars)
{
    int i;
    if (strlen(chars) >= MAX_STRING_SIZE)
    {
        printf("超过字符串的中最大限制长度了。\n");
        return ERROR;
    }
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
        {
            T[i] = *(chars + i - 1);
        }
        return OK;
    }
}

/* 构造空二叉树T */
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return OK;
}

/* 初始条件：二叉树T存在。操作结果：销毁二叉树T */
void DestroyBiTree(BiTree *T)
{
    // 树T存在
    if (*T)
    {   
        // 有左孩子
        if ((*T)->lchild)
        {
            // 销毁左孩子树
            DestroyBiTree(&(*T)->lchild);
        }
        // 有右孩子
        if ((*T)->rchild)
        {
            // 销毁右孩子树
            DestroyBiTree(&(*T)->rchild);
        }
        // 释放根节点
        free(*T);
        // 空指针赋0
        *T = NULL;
    }
    
}

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T)
{
    TLElemType ch;
    ch = str[index++];
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        // 生成根结点
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T)
        {
            printf("内存分配失败。\n");
            exit(0);
        }
        // 给结点赋值
        (*T)->data = ch;
        // 构造左子树
        CreateBiTree(&(*T)->lchild);
        // 构造右子树
        CreateBiTree(&(*T)->rchild);
    }
}

/* 初始条件：二叉树T存在 */
/* 操作结果：若T为空二叉树，则返回TRUE，否则FALSE */
Status BiTreeEmpty(BiTree T)
{
    return T ? FALSE : TRUE;
}

/* 清空二叉树和销毁操作一样 */
#define ClearBiTree DestroyBiTree

/* 初始条件：二叉树T存在。操作结果：返回T的深度 */
int BiTreeDepth(BiTree T)
{
    int i, j;
    // 如果为空树
    if (!T)
    {
        return 0;
    }
    // 有左孩子
    if (T->lchild)
    {
        // 继续遍历其左孩子
        i = BiTreeDepth(T->lchild);
    }
    // 没有左孩子
    else
    {
        i = 0;
    }
    //有右孩子
    if (T->rchild)
    {
        // 继续遍历右孩子
        j = BiTreeDepth(T->rchild);
    }
    // 没有右孩子
    else
    {
        j = 0;
    }
    return (i > j) ? (i + 1) : (j + 1);
}

/* 初始条件：二叉树T存在。操作结果：返回T的根 */
TLElemType Root(BiTree T)
{
    return BiTreeEmpty(T) ? Nil : T->data;
}

/* 初始条件：二叉树T存在，p指向T中某个结点 */
/* 操作结果：返回p所指结点的值 */
TLElemType Value(BiTree p)
{
    return p->data;
}

/* 给p所指结点赋值为value */
void Assign(BiTree p, TLElemType value)
{
    p->data = value;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：前序递归遍历T */
void PreOrderTraverse(BiTree T)
{
    // 如果为空树
    if (T == NULL)
    {
        return;
    }
    // 显示结点数据，可以更改为其它对结点的操作
    visit(T->data);
    // 再前序遍历左子树
    PreOrderTraverse(T->lchild);
    // 最后前序遍历右子树
    PreOrderTraverse(T->rchild);
}

/* 初始条件:二叉树T存在 */
/* 操作结果:中序递归遍历T */
void InOrderTraverse(BiTree T)
{
    // 如果为空树
    if (T == NULL)
    {
        return;
    }
    // 先中序遍历左子树
    InOrderTraverse(T->lchild);
    // 再显示结点数据，可以更改为其它对结点的操作
    visit(T->data);
    // 最后中序遍历右子树
    InOrderTraverse(T->rchild);
}

/* 初始条件：二叉树T存在 */
/* 操作结果：后序递归遍历T */
void PostOrderTraverse(BiTree T)
{
    // 如果为空树
    if (T == NULL)
    {
        return;
    }
    // 先后序遍历左子树
    PostOrderTraverse(T->lchild);
    // 再后序遍历右子树
    PostOrderTraverse(T->rchild);
    // 最后显示结点数据，可以更改为其它对结点的操作
    visit(T->data);
}

/* 二叉树链式结构具有的操作定义 end */