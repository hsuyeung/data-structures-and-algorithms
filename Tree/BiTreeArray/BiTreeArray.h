/* 二叉树顺序存储结构的实现文件 */
#include "../../common.h"
#ifndef BI_TREE_ARRAY
#define BI_TREE_ARRAY

// Status是函数的类型：其值是函数结果状态代码，如OK等
typedef int Status;

// 设整型0代表二叉树结点为空
TElemType Nil = 0;

// 二叉树的最大结点数
#define MAX_TREE_SIZE 100

/* 二叉树顺序结构定义 start */

// 0号单元存储根节点
typedef TElemType SqBiTree[MAX_TREE_SIZE];

//结点的位置结构
typedef struct
{
    // 结点所在的层
    int level;
    // 结点在本层的序号(按满二叉树计算)
    int order;
} Position;

/* 二叉树顺序结构定义 end */

/* 二叉树顺序结构具有的操作声明 start */

Status visit(TElemType c);

/* 构造空二叉树T。因为T是固定数组，不会改变，故不需要& */
Status InitBiTree(SqBiTree T);

/* 按层序次序输入二叉树中结点的值(字符型或整型)：构造顺序存储的二叉树T */
Status CreateBiTree(SqBiTree T);

/* 在顺序存储结构中，两函数的操作完全一样 */
#define ClearBiTree InitBiTree

/* 初始条件：二叉树T存在 */
/* 操作结果：若T为空二叉树：则返回TRUE：否则FALSE */
Status BiTreeEmpty(SqBiTree T);

/* 初始条件：二叉树T存在。操作结果：返回T的深度 */
int BiTreeDepth(SqBiTree T);

/* 初始条件：二叉树T存在 */
/* 操作结果：当T不空：用e返回T的根：返回OK;否则返回ERROR：e无定义 */
Status Root(SqBiTree T, TElemType *e);

/* 初始条件：二叉树T存在：e是T中某个结点(的位置) */
/* 操作结果：返回处于位置e(层：本层序号)的结点的值 */
TElemType Value(SqBiTree T, Position e);

/* 初始条件：二叉树T存在：e是T中某个结点(的位置) */
/* 操作结果：给处于位置e(层：本层序号)的结点赋新值value */
Status Assign(SqBiTree T, Position e, TElemType value);

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：若e是T的非根结点：则返回它的双亲：否则返回＂空＂ */
TElemType Parent(SqBiTree T, TElemType e);

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的左孩子。若e无左孩子：则返回＂空＂ */
TElemType LeftChild(SqBiTree T, TElemType e);

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的右孩子。若e无右孩子：则返回＂空＂ */
TElemType RightChild(SqBiTree T, TElemType e);

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的左兄弟。若e是T的左孩子或无左兄弟：则返回＂空＂ */
TElemType LeftSibling(SqBiTree T, TElemType e);

/* 初始条件：二叉树T存在：e是T中某个结点 */
/* 操作结果：返回e的右兄弟。若e是T的右孩子或无右兄弟：则返回＂空＂ */
TElemType RightSibling(SqBiTree T, TElemType e);

/* PreOrderTraverse()调用 */
void PreTraverse(SqBiTree T, int e);

/* 初始条件：二叉树存在 */
/* 操作结果：先序遍历T。 */
Status PreOrderTraverse(SqBiTree T);

/* InOrderTraverse()调用 */
void InTraverse(SqBiTree T, int e);

/* 初始条件：二叉树存在 */
/* 操作结果：中序遍历T。 */
Status InOrderTraverse(SqBiTree T);

/* PostOrderTraverse()调用 */
void PostTraverse(SqBiTree T, int e);

/* 初始条件：二叉树T存在 */
/* 操作结果：后序遍历T。 */
Status PostOrderTraverse(SqBiTree T);

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T);

/* 逐层、按本层序号输出二叉树 */
void Print(SqBiTree T);

/* 二叉树顺序结构具有的操作声明 end */

#endif