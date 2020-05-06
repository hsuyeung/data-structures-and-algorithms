/* 链队列的定义文件 */
#include "../../common.h"
#ifndef LINK_QUEUE
#define LINK_QUEUE

/* 最大容量定义 start */
#define MAX_SIZE 20
/* 最大容量定义 end */

/* 循环队列的顺序结构定义 start */

/* 结点结构 */
typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

/* 队列的链表结构 */
typedef struct
{
    // 队头指针
    QueuePtr front;
    // 队尾指针
    QueuePtr rear;
} LinkQueue;

/* 循环队列的顺序结构定义 end */

/* 循环队列的顺序结构具有的操作声明 start */

/* 构造一个空队列 */
int InitLinkQueue(LinkQueue *LQ);

/* 销毁队列 */
int DestroyLinkQueue(LinkQueue *LQ);

/* 将LQ清为空队列  */
int ClearLinkQueue(LinkQueue *LQ);

/* 若LQ为空队列,则返回TRUE,否则返回FALSE */
int LinkQueueEmpty(LinkQueue LQ);

/* 求队列的长度 */
int LinkQueueLength(LinkQueue LQ);

/* 若队列不空,则用e返回LQ的队头元素,并返回OK,否则返回ERROR */
int GetHead(LinkQueue LQ, QElemType *e);

/* 插入元素e为LQ的新的队尾元素 */
int EnLinkQueue(LinkQueue *LQ, QElemType e);

/* 若队列不空,删除LQ的队头元素,用e返回其值,并返回OK,否则返回ERROR */
int DeLinkQueue(LinkQueue *LQ, QElemType *e);

/* 从队头到队尾依次对队列LQ中每个元素输出 */
int LinkQueueTraverse(LinkQueue LQ);

/* 循环队列的顺序结构具有的操作声明 end */

#endif