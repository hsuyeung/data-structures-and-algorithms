/* 线索二叉树实现文件 */
#include "../../common.h"
#ifndef THREAD_BINARY_TREE
#define THREAD_BINARY_TREE

// Status是函数的类型：其值是函数结果状态代码，如OK等
typedef int Status;

// 字符串的最大长度
#define MAX_STRING_SIZE (1 + 100)

// 设字符型以#代表二叉树结点为空
TLElemType Nil = '#';

/* 每个结点的状态枚举 start*/

typedef enum
{
    // Link：0，表示指向左右孩子指针
    Link,
    // Thread：1，表示指向前驱或后继的线索
    Thread
} PointerTag;

/* 每个结点的状态枚举 end*/

/* 二叉线索存储结点结构 start */

typedef struct BiThrNode
{
    // 结点数据
    TLElemType data;
    // 左右孩子指针
    struct BiThrNode *lchild, *rchild;
    // 左右标志
    PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

/* 二叉线索存储结点结构 end */

// 全局变量，始终指向刚刚访问过的结点，用于中序遍历进行线索化
BiThrTree pre;

/* 线索二叉树具有的操作声明 start */

/* 打印结点的值 */
Status visit(TElemType e);

/* 按前序输入二叉线索树中结点的值，构造二叉线索树T */
/* 0(整型)/空格(字符型)表示空结点 */
Status CreateBiThrTree(BiThrTree *T);

/* 中序遍历进行中序线索化 */
void InThreading(BiThrTree p);

/* 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点 */
Status InOrderThreading(BiThrTree *Thrt, BiThrTree T);

/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderTraverse_Thr(BiThrTree T);

/* 线索二叉树具有的操作声明 end */

#endif