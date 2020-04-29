#include "linkQueue.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    LinkQueue linkQueue;
    if (InitLinkQueue(&linkQueue) == OK)
    {
        printf("初始化成功。\n");
    }
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n", LinkQueueEmpty(linkQueue));
    //给队列赋值
    QElemType elem = -1;
    printf("请输入整型队列元素(不超过%d个),输入任意字母可结束输入：", MAX_SIZE - 1);
    while (scanf("%d", &elem) != 0)
    {
        EnLinkQueue(&linkQueue, elem);
    }
    printf("队列长度为：%d\n", LinkQueueLength(linkQueue));
    printf("现在队列空否？%u(1:空 0:否)\n", LinkQueueEmpty(linkQueue));
    LinkQueueTraverse(linkQueue);
    if (GetHead(linkQueue, &elem) == OK)
    {
        printf("当前的队头元素为：%d\n", elem);
    }
    if (DeLinkQueue(&linkQueue, &elem) == OK)
    {
        printf("删除了队头元素：%d\n", elem);
    }
    if (GetHead(linkQueue, &elem) == OK)
    {
        printf("当前的队头元素为：%d\n", elem);
    }
    LinkQueueTraverse(linkQueue);
    ClearLinkQueue(&linkQueue);
	printf("清空队列后,linkQueue.front=%p linkQueue.rear=%p linkQueue.front->next=%p\n", 
        linkQueue.front, linkQueue.rear, linkQueue.front->next);
	DestroyLinkQueue(&linkQueue);
	printf("销毁队列后,linkQueue.front=%p linkQueue.rear=%p\n", linkQueue.front, linkQueue.rear);

    return 0;
}

/*循环队列的顺序结构具有的操作定义 start*/

/*构造一个空队列*/
int InitLinkQueue(LinkQueue *LQ)
{
    LQ->front = LQ->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!(LQ->front))
    {
        printf("内存分配失败。\n");
        exit(0);
    }
    LQ->front->next = NULL;
    return OK;
}

/*销毁队列*/
int DestroyLinkQueue(LinkQueue *LQ)
{
    while (LQ->front)
    {
        LQ->rear = LQ->front->next;
        free(LQ->front);
        LQ->front = LQ->rear;
    }
    return OK;
}

/*将LQ清为空队列 */
int ClearLinkQueue(LinkQueue *LQ)
{
    QueuePtr p, q;
    LQ->rear = LQ->front;
    p = LQ->front->next;
    LQ->front->next = NULL;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }
    return OK;
}

/*若LQ为空队列,则返回TRUE,否则返回FALSE*/
int LinkQueueEmpty(LinkQueue LQ)
{
    return (LQ.front == LQ.rear) ? TRUE : FALSE;
}

/*求队列的长度*/
int LinkQueueLength(LinkQueue LQ)
{
    int i = 0;
    QueuePtr p;
    p = LQ.front;
    while (LQ.rear != p)
    {
        i++;
        p = p->next;
    }
    return i;
}

/*若队列不空,则用e返回LQ的队头元素,并返回OK,否则返回ERROR*/
int GetHead(LinkQueue LQ, QElemType *e)
{
    if (LQ.front == LQ.rear)
    {
        printf("队列为空。\n");
        return ERROR;
    }
    *e = LQ.front->next->data;
    return OK;
}

/*插入元素e为LQ的新的队尾元素*/
int EnLinkQueue(LinkQueue *LQ, QElemType e)
{
    QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
    if (!s)
    {
        printf("内存分配失败。\n");
        exit(0);
    }
    s->data = e;
    s->next = NULL;
    //把拥有元素e的新结点赋值给原队尾结点的后继
    LQ->rear->next = s;
    //把当前的s设置为队尾结点，rear指向s
    LQ->rear = s;
    return OK;
}

/*若队列不空,删除LQ的队头元素,用e返回其值,并返回OK,否则返回ERROR*/
int DeLinkQueue(LinkQueue *LQ, QElemType *e)
{
    QueuePtr p;
    if (LQ->front == LQ->rear)
    {
        printf("队列为空。\n");
        return ERROR;
    }
    //将欲删除的队头结点暂存给p
    p = LQ->front->next;
    //将欲删除的队头结点的值赋给e
    *e = p->data;
    //将原队头结点的后继p->next赋值给头结点后继
    LQ->front->next = p->next;
    //若队头就是队尾，则删除后将rear指向头结点
    if (LQ->rear == p)
    {
        LQ->rear = LQ->front;
    }
    free(p);
    return OK;
}

/*从队头到队尾依次对队列LQ中每个元素输出*/
int LinkQueueTraverse(LinkQueue LQ)
{
    QueuePtr p;
    p = LQ.front->next;
    printf("队列的当前数据为：\n");
    while (p)
    {
        printf("->%d", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}

/*循环队列的顺序结构具有的操作定义 end*/