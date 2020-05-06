#include "sqQueue.h"
#include <stdio.h>

int main(void)
{
    // 初始化一个空队列
    SqQueue sqQueue;
    if (InitQueue(&sqQueue) == OK)
    {
        printf("初始化成功。\n");
    }
    printf("初始化队列后，队列空否？%u(1:空 0:否)\n", QueueEmpty(sqQueue));
    // 给队列赋值
    QElemType elem = -1;
    printf("请输入整型队列元素(不超过%d个),输入任意字母可结束输入：", MAX_SIZE - 1);
    while (scanf("%d", &elem) != 0)
    {
        EnQueue(&sqQueue, elem);
    }
    printf("队列长度为：%d\n", QueueLength(sqQueue));
    printf("现在队列空否？%u(1:空 0:否)\n", QueueEmpty(sqQueue));
    QueueTraverse(sqQueue);
    printf("连续5次由队头删除元素,队尾插入元素:\n");
    int i;
    for (i = 0; i < 5; i++)
    {
        DeQueue(&sqQueue, &elem);
		printf("删除的元素是%d,插入的元素:%d \n", elem, elem+1000);
        EnQueue(&sqQueue, elem + 1000);
    }
    printf("队列长度为：%d\n", QueueLength(sqQueue));
    QueueTraverse(sqQueue);
    // 获取队头元素
    if (GetHead(sqQueue, &elem) == OK)
    {
		printf("现在队头元素为：%d\n", elem);
    }
    // 清空队列
	ClearQueue(&sqQueue);
	printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(sqQueue));

    return 0;
}

/* 循环队列的顺序结构具有的操作定义 start */

/* 初始化一个空队列Q */
int InitQueue(SqQueue *Q)
{
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 将Q清为空队列 */
int ClearQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
    return OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
int QueueEmpty(SqQueue Q)
{
    return (Q.front == Q.rear) ? TRUE : FALSE;
}

/* 返回Q的元素个数，也就是队列的当前长度 */
int QueueLength(SqQueue Q)
{
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}

/* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
int GetHead(SqQueue Q, QElemType *e)
{
    if (Q.front == Q.rear)
    {
        printf("队列为空。\n");
        return ERROR;
    }
    *e = Q.data[Q.front];
    return OK;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
int EnQueue(SqQueue *Q, QElemType e)
{
    // 队列满的判断
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        printf("队列满了。\n");
        return ERROR;
    }
    // 将元素e赋值给队尾
    Q->data[Q->rear] = e;
    // rear指针向后移一位，若到最后则转到数组头部
    Q->rear = (Q->rear + 1) % MAX_SIZE;
    return OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
int DeQueue(SqQueue *Q, QElemType *e)
{
    // 队列空的判断
    if (Q->front == Q->rear)
    {
        printf("队列为空。\n");
        return ERROR;
    }
    // 将队头元素赋值给e
    *e = Q->data[Q->front];
    // front指针向后移一位置，若到最后则转到数组头部
    Q->front = (Q->front + 1) % MAX_SIZE;
    return OK;
}

/* 从队头到队尾依次对队列Q中每个元素输出 */
int QueueTraverse(SqQueue Q)
{
    printf("当前队列的元素为：\n");
    int i;
    i = Q.front;
    while (i != Q.rear)
    {
        printf("->%d", Q.data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
    return OK;
}

/* 循环队列的顺序结构具有的操作定义 end */