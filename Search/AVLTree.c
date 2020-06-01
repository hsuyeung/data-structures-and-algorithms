/* 平衡二叉树 */
#include "../common.h"
#include <stdio.h>
#include <stdlib.h>

/* 存储空间初始分配量 */
#define MAXSIZE 100

typedef int Status;

/* 二叉树的二叉链表结点结构定义 */
typedef struct BiTNode
{
    // 结点数据
    int data;
    // 结点的平衡因子
    int bf;
    // 左右孩子指针
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

/* 对以p为根的二叉排序树作右旋处理， */
/* 处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点 */
void R_Rotate(BiTree *P)
{
    BiTree L;
    // L指向P的左子树根结点
    L = (*P)->lchild;
    // L的右子树挂接为P的左子树
    (*P)->lchild = L->rchild;
    L->rchild = (*P);
    // P指向新的根节点
    *P = L;
}

/* 对以P为根的二叉排序树作左旋处理， */
/* 处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点0  */
void L_Rotate(BiTree *P)
{
    BiTree R;
    // R指向P的右子树根结点
    R = (*P)->rchild;
    // R的左子树挂接为P的右子树
    (*P)->rchild = R->lchild;
    R->lchild = (*P);
    // P指向新的根节点
    *P = R;
}

/* 左高 */
#define LH +1
/* 等高 */
#define EH 0
/* 右高 */
#define RH -1

/*  对以指针T所指结点为根的二叉树作左平衡旋转处理 */
/*  本算法结束时，指针T指向新的根结点 */
void LeftBalance(BiTree *T)
{
    BiTree L, Lr;
    // L指向T的左子树根节点
    L = (*T)->lchild;
    switch (L->bf)
    {
    // 检查T的左子树的平衡度，并作相应平衡处理
    // 新结点插入在T的左孩子的左子树上，要作单右旋处理
    case LH:
        (*T)->bf = L->bf = EH;
        R_Rotate(T);
        break;
    // 新结点插入在T的左孩子的右子树上，要作双旋处理
    case RH:
        // Lr指向T的左孩子的右子树根
        Lr = L->rchild;
        // 修改T及其左孩子的平衡因子
        switch (Lr->bf)
        {
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        Lr->bf = EH;
        // 对T的左子树作左旋平衡处理
        L_Rotate(&(*T)->lchild);
        // 对T作右旋平衡处理
        R_Rotate(T);
        break;
    }
}

/*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */
/*  本算法结束时，指针T指向新的根结点 */
void RightBalance(BiTree *T)
{
    BiTree R, Rl;
    // R指向T的右子树根结点
    R = (*T)->rchild;
    // 检查T的右子树的平衡度，并作相应平衡处理
    switch (R->bf)
    {
        // 新结点插入在T的右孩子的右子树上，要作单左旋处理
    case RH:
        (*T)->bf = R->bf = EH;
        L_Rotate(T);
        break;
        // 新结点插入在T的右孩子的左子树上，要作双旋处理
    case LH:
        // Rl指向T的右孩子的左子树根
        Rl = R->lchild;
        // 修改T及其右孩子的平衡因子
        switch (Rl->bf)
        {
        case RH:
            (*T)->bf = LH;
            R->bf = EH;
            break;
        case EH:
            (*T)->bf = R->bf = EH;
            break;
        case LH:
            (*T)->bf = EH;
            R->bf = RH;
            break;
        }
        Rl->bf = EH;
        // 对T的右子树作右旋平衡处理
        R_Rotate(&(*T)->rchild);
        // 对T作左旋平衡处理
        L_Rotate(T);
    }
}

/* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
/* 数据元素为e的新结点并返回1，否则返回0.若因插入而使二叉排序树 */
/* 失去平衡，则作平衡旋转处理，布尔变量taller反应T长高与否 */
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T)
    {
        // 插入新结点，树“长高”，置taller为TRUE
        *T = (BiTree)malloc(sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    }
    else
    {
        // 树中已经存在和e有相同关键字的结点则不再插入
        if (e == (*T)->data)
        {
            *taller = FALSE;
            return FALSE;
        }
        // 如果e小于当前关键字，则继续在T的左子树中进行搜索
        if (e < (*T)->data)
        {
            // 未插入
            if (!InsertAVL(&(*T)->lchild, e, taller))
            {
                return FALSE;
            }
            // 已插入到T的左子树中且左子树“长高”
            if (taller)
            {
                // 检查T的平衡度
                switch ((*T)->data)
                {
                // 原本左子树比右子树高，需要作左平衡处理
                case LH:
                    LeftBalance(T);
                    *taller = FALSE;
                    break;
                // 原本左右子树等高，现因左子树增高而树增高
                case EH:
                    (*T)->bf = LH;
                    *taller = TRUE;
                    break;
                // 原本右子树比左子树高，现在左右子树等高
                case RH:
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                }
            }
        }
        // 如果e大于当前关键字，应继续在T的右子树中进行搜索
        else
        {
            // 未插入
            if (!InsertAVL(&(*T)->rchild, e, taller))
            {
                return FALSE;
            }
            // 已插入到T的右子树且右子树“长高”
            if (*taller)
            {
                // 检查T的平衡度
                switch ((*T)->bf)
                {
                // 原本左子树比右子树高，现在左、右子树等高
                case LH:
                    (*T)->bf = EH;
                    *taller = FALSE;
                    break;
                // 原本左、右子树等高，现因右子树增高而树增高
                case EH:
                    (*T)->bf = RH;
                    *taller = TRUE;
                    break;
                // 原本右子树比左子树高，需要作右平衡处理
                case RH:
                    RightBalance(T);
                    *taller = FALSE;
                    break;
                }
            }
        }
    }
    return TRUE;
}

int main(void)
{
    int i;
    int a[10] = {3, 2, 1, 4, 5, 6, 7, 10, 9, 8};
    BiTree T = NULL;
    Status taller;
    for (i = 0; i < 10; i++)
    {
        InsertAVL(&T, a[i], &taller);
    }
    printf("本样例建议断点跟踪查看平衡二叉树结构");

    return 0;
}