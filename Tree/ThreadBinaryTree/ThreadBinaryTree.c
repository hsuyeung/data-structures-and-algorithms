#include "ThreadBinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // H表示头结点，T表示二叉树
    BiThrTree H, T;
    printf("请按前序输入二叉树(如:'ABD#E###C#FG#I###')\n");
    // 按前序产生二叉树
 	CreateBiThrTree(&T);
    // 中序遍历,并中序线索化二叉树
	InOrderThreading(&H, T);
	printf("中序遍历(输出)二叉线索树:\n");
    // 中序遍历(输出)二叉线索树
	InOrderTraverse_Thr(H);
	printf("\n");

    return 0;
}

/* 线索二叉树具有的操作定义 start */

/* 打印结点的值 */
Status visit(TElemType e)
{
    printf("%c ", e);
    return OK;
}

/* 按前序输入二叉线索树中结点的值，构造二叉线索树T */
/* #表示空结点 */
Status CreateBiThrTree(BiThrTree *T)
{
    TLElemType h;
    scanf("%c", &h);
    if (h == Nil)
    {
        *T = NULL;
    }
    else
    {
        // 生成根节点
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (!*T)
        {
            printf("内存分配失败。\n");
            exit(0);
        }
        // 给根结点赋值
        (*T)->data = h;
        // 递归构造左子树
        CreateBiThrTree(&(*T)->lchild);
        // 如果有左孩子
        if ((*T)->lchild)
        {
            // 则将左标志设置为孩子指针
            (*T)->LTag = Link;
        }
        // 递归构造右子树
        CreateBiThrTree(&(*T)->rchild);
        // 如果有右孩子
        if ((*T)->rchild)
        {
            // 则将右标志设置为孩子指针
            (*T)->RTag = Link;
        }
    }
    return OK;
}

/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p)
{
    // 树非空
    if (p)
    {
        // 先递归左子树线索化
        InThreading(p->lchild);
        // 如果没有左孩子
        if (!p->lchild)
        {
            // 则将该结点的左标志设置为指向前驱的线索
            p->LTag = Thread;
            // 左孩子指向前驱
            p->lchild = pre;
        }
        // 如果前驱没有右孩子
        if (!pre->rchild)
        {
            // 则将前驱的右标志设置为针指向当前结点的后继的线索
            pre->RTag = Thread;
            // 前驱的右孩子指针指向后继(当前结点p)
            pre->rchild = p;
        }
        // 保持pre指向p的前驱
        pre = p;
        // 递归右子树线索化
        InThreading(p->rchild);
    }
}

/* 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点 */
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T)
{
    // 建立一个头结点
    *Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
    if (!*Thrt)
    {
        printf("内存分配失败。\n");
        exit(0);
    }
    // 头结点的左标志设置为指向左右孩子指针
    (*Thrt)->LTag = Link;
    // 头结点的右标志设置为指向前驱或后继的线索
    (*Thrt)->RTag = Thread;
    // 头结点的右指针指向自己
    (*Thrt)->rchild = (*Thrt);
    // 如果二叉树为空，则头结点的左指针指向自己
    if (!T)
    {
        (*Thrt)->lchild = *Thrt;
    }
    // 二叉树不为空
    else
    {
        // 头结点的左指针指向二叉树的根结点
        (*Thrt)->lchild = T;
        // 初始化pre指针指向头结点
        pre = *Thrt;
        /*
         * 这里说明一下，遍历线索化的过程描述：
         * 在二叉树线索链表上添加一个头结点，并令其lchild域的指针指向二叉树的根节点，
         * 其rchild域的指针指向中序遍历时访问的最后一个结点。令二叉树的中序序列中的第
         * 一个结点的lchild域指针和最后一个结点的rchild域指针均指向头结点。这样既可以
         * 从第一个结点其顺后继进行遍历，也可以从最后一个结点起顺前驱进行遍历。
         * 这下面的代码看似少了一步：“使二叉树的中序序列中的第一个结点的lchild域指针指
         * 向头结点”，实际上并没有少，这一步的操作放在了InThreading()函数中完成。可以
         * 自行推导一下。上面的pre = *Thrt;是关键。
         */
        // 中序遍历进行中序线索化
        InThreading(T);
        // 令二叉树的中序序列中的最后一个结点的rchild域指针指向头结点
        pre->rchild = *Thrt;
        // 线索化完了之后单独对二叉树的中序序列中的最后一个结点线索化
        pre->RTag = Thread;
        // 使头结点的右指针指向中序遍历时访问的最后一个结点
        (*Thrt)->rchild = pre;
    }
    return OK;
}

/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    // p指向根结点
    p = T->lchild;
    // 空树或遍历结束时，p==T
    while (p != T)
    {
        // 当LTag表示指针域指向左右孩子的指针时
        // 循环到中序序列的第一个结点
        while (p->LTag == Link)
        {
            p = p->lchild;
        }
        // 显示结点数据，可以更改为其他对结点的操作
        visit(p->data);
        // 当当前结点的右标志为线索并且不是最后一个结点时
        while (p->RTag == Thread && p->rchild != T)
        {
            // 访问后继结点
            p = p->rchild;
            visit(p->data);
        }
        // p进至其右子树根
        p = p->rchild;
    }
    return OK;
}

/* 线索二叉树具有的操作定义 end */