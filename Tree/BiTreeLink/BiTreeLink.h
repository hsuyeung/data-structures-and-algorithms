/* 二叉树链式存储结构实现文件 */
#include "../../common.h"
#ifndef BI_TREE_LINK
#define BI_TREE_LINK

// Status是函数的类型：其值是函数结果状态代码，如OK等
typedef int Status;

// 字符串的最大长度
#define MAX_STRING_SIZE (1 + 100)

// 设字符型以#代表二叉树结点为空
TLElemType Nil = '#';

// 字符串定义，0号单元存放串的长度
typedef char String[MAX_STRING_SIZE];

// 用于遍历字符串
int index = 1;
String str;

/* 二叉树链式结构定义 start */

/* 结点结构 */
typedef struct BiTNode
{
    // 结点数据
    TLElemType data;
    // 左孩子指针
    struct BiTNode *lchild;
    // 右孩子指针
    struct BiTNode *rchild;
} BiTNode, *BiTree;

/* 二叉树链式结构具有的操作声明 start */

/* 打印结点的值 */
Status visit(TLElemType e);

/* 给字符串T赋值为chars */
Status StrAssign(String T, char *chars);

/* 构造空二叉树T */
Status InitBiTree(BiTree *T);

/* 初始条件：二叉树T存在。操作结果：销毁二叉树T */
void DestroyBiTree(BiTree *T);

/* 按前序输入二叉树中结点的值（一个字符） */
/* #表示空树，构造二叉链表表示二叉树T。 */
void CreateBiTree(BiTree *T);

/* 初始条件：二叉树T存在 */
/* 操作结果：若T为空二叉树，则返回TRUE，否则FALSE */
Status BiTreeEmpty(BiTree T);

#define ClearBiTree DestroyBiTree

/* 初始条件：二叉树T存在。操作结果：返回T的深度 */
int BiTreeDepth(BiTree T);

/* 初始条件：二叉树T存在。操作结果：返回T的根 */
TLElemType Root(BiTree T);

/* 初始条件：二叉树T存在，p指向T中某个结点 */
/* 操作结果：返回p所指结点的值 */
TLElemType Value(BiTree p);

/* 给p所指结点赋值为value */
void Assign(BiTree p, TLElemType value);

/* 初始条件：二叉树T存在 */
/* 操作结果：前序递归遍历T */
void PreOrderTraverse(BiTree T);

/* 初始条件:二叉树T存在 */
/* 操作结果:中序递归遍历T */
void InOrderTraverse(BiTree T);

/* 初始条件：二叉树T存在 */
/* 操作结果：后序递归遍历T */
void PostOrderTraverse(BiTree T);

/* 二叉树链式结构具有的操作声明 end */

/* 二叉树链式结构定义 end */

#endif